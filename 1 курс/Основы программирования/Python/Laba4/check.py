def input_nat0(name=''):
    """
    Проверка ввода на натуральное число с учетом ноля и возвращение исправленного пользователем значения
    :param name: вводимый пользователем текст
    :type name: str
    :return: натуральное число или 0: int
    """
    while 2 < 3:
        number = input(name)
        try:
            int(number)
            if int(number) < 0:
                print('Число должно быть неотрицательным')
            else:
                number = int(number)
                break
        except ValueError:
            print('Неверный тип данных')
    return number
