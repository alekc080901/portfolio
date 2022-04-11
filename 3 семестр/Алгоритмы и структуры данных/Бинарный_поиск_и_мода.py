def find_mode(array: list):
    frequency = {}
    for i in array:
        if i not in frequency:
            frequency[i] = 1
        else:
            frequency[i] += 1

    return max(frequency, key=frequency.get)


def binary_search(array: list, elem: int):
    array.sort()
    while len(array) // 2 > 0:
        middle_length = len(array) // 2
        if elem == array[middle_length]:
            return True
        elif elem > array[middle_length]:
            array = array[middle_length:]
        else:
            array = array[:middle_length]
    return False


def main():
    array = input("Введите массив чисел через запятую:\n").replace(' ', '').split(',')
    count = 0
    for i in array:
        try:
            array[count] = int(i)
            count += 1
        except ValueError:
            print('Вы должны ввести число!')
            return
    print(array)
    algorithm_choice = input("1. Найти моду\n"
                             "2. Найти элемент\n")
    if algorithm_choice == '1':
        print('Мода массива:', find_mode(array))

    elif algorithm_choice == '2':
        elem_choice = input("Введите число, которое хотите найти:\n")
        try:
            elem_choice = int(elem_choice)
        except ValueError:
            print('Вы должны ввести число!')
            return
            
        if binary_search(array, elem_choice):
            print("Число найдено")
        else:
            print("Число не найдено")
    else:
        print("Вы должны ввести 1 или 2!")


if __name__ == '__main__':
    main()
