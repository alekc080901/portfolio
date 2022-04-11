from random import randint


# Быстрая сортировка
def quick_sort(a, start, end):
    if start >= end:  # len(a) меньше или равно 1, когда старт меньше конца
        return
    else:
        middle = a[start:end + 1][len(a[start:end + 1]) // 2]
        i = start
        j = end
        while i <= j:
            while a[i] < middle:
                i += 1
            while a[j] > middle:
                j -= 1
            if i <= j:
                a[i], a[j] = a[j], a[i]
                i += 1
                j -= 1
                quick_sort(a, start, j)
                quick_sort(a, i, end)


# Шейкерная сортировка
def cocktail_shaker_sort(a: list):
    right_position = len(a) - 1
    left_position = 0
    while left_position <= len(a) // 2:
        for i in range(right_position - 1):
            if a[i] > a[i + 1]:
                a[i], a[i + 1] = a[i + 1], a[i]
        right_position -= 1

        for i in range(right_position, 1, -1):
            if a[i] < a[i - 1]:
                a[i], a[i - 1] = a[i - 1], a[i]
        left_position += 1

    return a


def main():
    try:
        length = int(input("Введите длину массива:\n"))
    except ValueError:
        print("Необходимо ввести число!")

    array = [randint(0, 100) for _ in range(length)]
    print(array, '\n')

    print("Результат быстрой сортировки:")
    quick_sort(array, 0, len(array) - 1)
    print(array, '\n')

    print("Результат шейкерной сортировки:")
    cocktail_shaker_sort(array)
    print(array)


if __name__ == '__main__':
    main()