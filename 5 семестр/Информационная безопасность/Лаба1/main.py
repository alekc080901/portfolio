import numpy as np
import random


ALPHABET = ['а', 'б', 'в', 'г', 'д', 'е', 'ё', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п', 'р', 'с', 'т',
            'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ', 'ы', 'ь', 'э', 'ю', 'я', '.', ',', ' ']


def create_cipher_table(key=None):
    random.seed(key)
    alphabet = ALPHABET.copy()
    random.shuffle(alphabet)

    table = np.array(alphabet).reshape(6, 6)
    return table


def encrypt(message: str, key=None, decrypt=False, print_random_info=False) -> str:
    message = message.lower()
    cipher_table = create_cipher_table(key)
    rows_num, cols_num = cipher_table.shape

    random.seed(key)
    step = random.randint(1, rows_num - 1)

    if print_random_info:
        print(cipher_table)
        print('Шаг:', step)

    if decrypt:
        step *= -1

    encrypted_message = ''
    for char in message:
        if len(np.where(cipher_table == char)[0]) == 0:
            encrypted_message += char
            continue

        y_coord = np.where(cipher_table == char)[0][0]
        x_coord = np.where(cipher_table == char)[1][0]

        encrypted_message += cipher_table[(y_coord + step) % rows_num][x_coord]

    return encrypted_message


def main():
    message = input("Введите сообщение:\n")
    key = input("Введите ключ:\n")
    encrypted_message = encrypt(message, key=key, print_random_info=True)
    decrypted_message = encrypt(encrypted_message, key=key, decrypt=True)

    print('Исходное сообщение:', message)
    print('Зашифрованное сообщение:', encrypted_message)
    print('Расшифрованное сообщение:', decrypted_message)


if __name__ == '__main__':
    main()
