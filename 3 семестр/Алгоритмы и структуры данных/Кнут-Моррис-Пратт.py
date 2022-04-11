def get_prefix(string):
    array = [0 for _ in range(len(string))]
    j = 0
    i = 1
    while i < len(string):
        if string[i] == string[j]:
            array[i] = j + 1
            j += 1
            i += 1
        elif j == 0:
            array[i] = 0
            i += 1
        else:
            j = array[j - 1]
    print(array)
    return array


def algorithm(string, image):
    prefix_array = get_prefix(image)
    s = 0
    i = 0
    while s < len(string):
        if string[s] == image[i]:
            s += 1
            i += 1
            if i == len(image)-1:
                return True
        elif i == 0:
            s += 1
        else:
            i = prefix_array[i-1]
    return False


def main():
    string = input("Введите строку:\n")
    image = input("Введите образ:\n")

    while True:
        register = input("Игнорировать верхний регистр? (y/n, по умолчанию n):\n")
        if register == 'y':
            string = string.lower()
            image = image.lower()
        elif register not in ('n', ''):
            print("Введите y или n!")
            continue
        break

    if string != '' and image != '' and len(string) >= len(image) and algorithm(string, image):
        print("Образ найден")
    else:
        print("Образ не найден")


if __name__ == "__main__":
    main()
