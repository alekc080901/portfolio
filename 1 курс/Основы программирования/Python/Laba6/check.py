def input_nat(name=''):
    while 2 < 3:
        h = input(name)
        try:
            int(h)
            if int(h) <= 0:
                print('Число должно быть положительным')
            else:
                h = int(h)
                break
        except ValueError:
            print('Неверный тип данных')
    return h


def input_nat0(name=''):
    while 2 < 3:
        h = input(name)
        try:
            int(h)
            if int(h) < 0:
                print('Число должно быть неотрицательным')
            else:
                h = int(h)
                break
        except ValueError:
            print('Неверный тип данных')
    return h


def input_int(name=''):
    while 2 < 3:
        h = input(name)
        try:
            int(h)
            break
        except ValueError:
            print('Неверный тип данных')
    return h


def input_float(name=''):
    while 2 < 3:
        h = input(name)
        try:
            float(h)
            break
        except ValueError:
            print('Неверный тип данных')
    return h

