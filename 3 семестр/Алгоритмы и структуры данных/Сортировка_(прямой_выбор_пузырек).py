import random


# Сортировка с помощью прямого выбора
def selection_sort(a: list):
    for i in range(len(a)):
        mn = min(range(i, len(a)), key=a.__getitem__)  # Позиция минимального числа
        a[i], a[mn] = a[mn], a[i]
    return a

# Сортировка с помощью прямого обмена (пузырьком)
def bubble_sort(a: list):
    n = len(a)
    for i in range(n - 1):
        for j in range(n - i - 1):
            if a[j] > a[j + 1]:
                a[j], a[j + 1] = a[j + 1], a[j]
    return a


def main():
    try:
        length = int(input("Введите длину массива:\n"))
    except ValueError:
        print("Введите целое число!")
        return

    array = [random.randint(1, 100) for _ in range(length)]
    print(array, '\n')

    print("Результат обработки сортировкой пузырька:\n")
    print(bubble_sort(array), '\n')

    print("Результат обработки сортировкой включения:\n")
    print(selection_sort(array))


if __name__ == '__main__':
    main()
