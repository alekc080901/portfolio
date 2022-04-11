"""Сортировка простым слиянием"""

import json
import math
import sys


def read(fp):
    with open(fp, 'r') as read_data:
        return json.load(read_data)


def write(content, fp):
    with open(fp, 'w') as read_data:
        return json.dump(content, read_data)


def simple_merge_sort():
    file1 = 'file1.json'
    file2 = 'file2.json'
    file3 = 'file3.json'

    read(file1)
    global_result = [[i] for i in read(file1)]  # Как разделители последовательности будут использоваться
    write(global_result, file1)                 # вложенные листы
    while len(read(file1)) != 1:

        # "Расфасовка" последовательностей по файлам
        write(read(file1)[::2], file2)
        if len(read(file1)[1::2]) == len(read(file1)[::2]):
            write(read(file1)[1::2], file3)
        else:  # Создание пустой последовательности, если число последовательностей нечетно
            write(read(file1)[1::2] + [[]], file3)

        print('a: ', read(file1))
        print('b: ', read(file2))
        print('c: ', read(file3), '\n')

        # Слияние
        global_result = []
        for i in range(math.ceil(len(read(file1)) / 2)):
            seq1 = read(file2)[i]
            seq2 = read(file3)[i]
            temp_result = []
            while len(seq1) != 0 and len(seq2) != 0:
                if seq1[0] < seq2[0]:
                    temp_result.append(seq1[0])
                    del(seq1[0])
                else:
                    temp_result.append(seq2[0])
                    del(seq2[0])
            temp_result += seq1 + seq2
            global_result += [temp_result]

        write(global_result, file1)


def main():
    # Создание файлов
    open('file2.json', 'w').close()
    open('file3.json', 'w').close()

    # Пользовательский ввод
    try:
        data = input('Введите массив данных через запятую:\n').replace(' ', '').split(',')
        data = [int(val) for val in data]
    except ValueError:
        print('Ввод неправильный')
        sys.exit()

    with open('file1.json', 'w') as w:
        json.dump(data, w)

    print()
    simple_merge_sort()


if __name__ == '__main__':
    main()
