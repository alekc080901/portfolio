import re
import pandas as pd
from functools import reduce
from collections import Counter
from const import SOURCE_MESSAGE, ENCRYPTED_MESSAGE, RUSSIAN_SYMBOLS_FREQUENCY, RUSSIAN_SYMBOLS, VIGENERE_TABLE,\
    AFFINITY_INDEXES


def sort_dict_by_values(x: dict, reverse=False) -> dict:
    """Сортирует словарь по значениям"""
    return {k: v for k, v in sorted(x.items(), key=lambda item: item[1], reverse=reverse)}


def find_repetitions_pos(message: str, length=3) -> dict:
    """Ищет повторения заданной длинны в массиве текста и возвращает словарь с их позициями"""
    repetition_dict = {}
    for pos in range(len(message) - 2):
        section = message[pos: pos + length]

        if section not in repetition_dict:
            repetition_dict[section] = [m.start() for m in re.finditer(section, message)]

    return dict((k, v) for k, v in repetition_dict.items() if len(v) > 1)


def compute_gcd(*args):
    """Находит НОД нескольких чисел"""
    x = args[0]

    for y in args[1:]:
        while y:
            x, y = y, x % y

    return x


def get_intervals_list(repetitions: dict) -> list:
    """Получает список интервалов из списка позиций повторений"""
    intervals = []
    for rep_list in repetitions.values():
        intervals.extend([rep_list[i + 1] - rep_list[i] for i in range(len(rep_list) - 1)])
    return intervals


def calculate_intervals_gcd(repetitions: dict) -> dict:
    """Считает НОД для всех пар растояний и возвращает словарь {пара: НОД}"""
    intervals = get_intervals_list(repetitions)

    print('Список с интервалами повторениями:\n')
    print(intervals, '\n')

    gcd_list = []
    for i in range(len(intervals)):
        for j in range(i + 1, len(intervals)):

            if (gcd := compute_gcd(intervals[i], intervals[j])) != 1:
                gcd_list.append(gcd)

    gcd_frequencies = Counter(gcd_list)
    return sort_dict_by_values(dict((k, v) for k, v in gcd_frequencies.items() if v > 1), reverse=True)


def kasiski_test(cipher: str) -> int:
    """Находит длину ключа при помощи теста Касиски"""
    repetitions = find_repetitions_pos(cipher)
    print('Словарь с повторениями последовательности символов длиной больше 3:\n')
    print(repetitions, '\n')

    gcd_freq = calculate_intervals_gcd(repetitions)
    print('Словарь с количеством повторений НОД между каждыми интервалами интервала:\n')
    print(gcd_freq, '\n')

    return max(gcd_freq, key=gcd_freq.get)


def validate_cipher_period(cipher: str, period: int):
    """Проверяет, действительно ли длина ключа такая или нет"""
    n = len(cipher)
    freq = Counter(cipher)
    affinity_index = reduce(lambda prev, cur: prev + cur * (cur - 1), freq.values(), 0) / (n * (n - 1))

    borders = AFFINITY_INDEXES.loc[[period]]
    return float(borders['min']) <= affinity_index <= float(borders['max'])


def form_frequency_dict(text: str):
    """Создает словарь, который хранит частоту употребления каждой буквы в тексте относительно всех букв"""
    total = len(text)
    absolute = Counter(text)
    relative = dict([(k, v/total) for k, v in absolute.items()])
    return relative


def calculate_deviation(freq1: dict, freq2: dict):
    """Считает, насколько частота употребления букв одного текста расходится с другим"""
    deviation = 0
    for letter in RUSSIAN_SYMBOLS:
        deviation += abs(freq1.get(letter, 0.035) - freq2.get(letter, 0.035))
    return deviation


def _decrypt_1(cipher: str, caesar_key: pd.Series):
    """Дешифрует часть текста у одной из буквы ключа по данному шифру Цезаря"""
    decrypted_message = ''
    for symbol in cipher:
        decrypted_message += caesar_key[symbol]
    return decrypted_message


def guess_key(cipher: str, period: int, stringency=0.6) -> list:
    """Угадывает ключ для шифротекста, анализируя частотность букв. Текст разбивается на period частей для каждой буквы
    ключа, затем угадывается каждая буква по отдельности. Возвращает список подходящих под условие ключей"""
    key_letter_variations = ['']
    for pos in range(period):
        pos_letter_message = cipher[pos::period]
        pos_key_letters = []

        for letter, caesar_cipher in VIGENERE_TABLE.iterrows():
            decrypted_cipher_part = _decrypt_1(pos_letter_message, caesar_cipher)
            frequency = form_frequency_dict(decrypted_cipher_part)
            deviation = calculate_deviation(frequency, RUSSIAN_SYMBOLS_FREQUENCY)

            if deviation < stringency:
                pos_key_letters.append(letter)

        new_keys = key_letter_variations.copy()
        for i, key in enumerate(key_letter_variations):
            for letter in pos_key_letters:
                new_keys.append(key + str(letter))
            del new_keys[0]

        key_letter_variations = new_keys.copy()

    return key_letter_variations


def input_int(text='', low_border=float('-inf'), high_border=float('inf')):
    """Ввод целого числа"""
    while 2 < 3:
        try:
            number = int(input(text))
            if low_border <= number <= high_border:
                return number
            print('Введите корректное число!\n')
        except ValueError:
            print('Введите число!\n')


def choose_key(keys: list):
    """Позволяет выбрать пользователю один ключ из списка"""
    print('Список возможных ключей:')
    for i, key in enumerate(keys):
        print(f'{i + 1}. {key}')
    pos = input_int('Введите номер ключа:\n', low_border=1, high_border=len(keys))
    return keys[pos - 1]


def repeat_key(message: str, key: str) -> str:
    """Дублирует ключ до размера сообщения"""
    return (key * (int(len(message) / len(key)) + 1))[:len(message)]


def decrypt_cipher(cipher: str, key: str) -> str:
    """Дешифрует текст по ключу"""
    key = repeat_key(cipher, key)
    source_message = ''
    for pos, cipher_letter, key_letter in zip(range(len(cipher)), cipher, key):
        source_message += VIGENERE_TABLE.at[cipher_letter, key_letter]
    return source_message


def restore_signs(source, decrypted):
    """Восстанавливает исходные символы, которые были удалены"""
    decrypted_list = list(decrypted)
    for m in re.finditer('[^А-Я]', source):
        pos = m.start()
        decrypted_list.insert(pos, source[pos])
    return ''.join(decrypted_list)


def main():
    period = kasiski_test(ENCRYPTED_MESSAGE)
    print('Период ключа:', period, '\n')

    input('Нажмите Enter для продолжения...')
    print()

    print('Период ключа валиден.\n' if validate_cipher_period(ENCRYPTED_MESSAGE, period)
          else 'Период ключа не валиден.\n')

    input('Нажмите Enter для продолжения...')
    print()

    possible_keys = guess_key(ENCRYPTED_MESSAGE, period, stringency=0.6)
    key = choose_key(possible_keys)

    decrypted_message_raw = decrypt_cipher(ENCRYPTED_MESSAGE, key)
    print('Расшифрованное сообщение:\n')
    print(restore_signs(SOURCE_MESSAGE, decrypted_message_raw))


if __name__ == '__main__':
    main()
