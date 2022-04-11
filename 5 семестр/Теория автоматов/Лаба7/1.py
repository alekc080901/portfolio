def increment(a):
    return a + 1


def decrement(a):
    if a == 0:
        return 0
    else:
        return a - 1


def add(a, b):
    if b == 0:
        return a
    else:
        return increment(add(a, decrement(b)))


def mult(a, b):
    if b == 0:
        return 0
    else:
        return add(a, mult(a, decrement(b)))


def pow(x, exp):
    if exp == 0:
        return increment(0)
    else:
        return mult(x, pow(x, decrement(exp)))


def f(x):
    return pow(x, x)


def main():
    while True:
        try:
            x = int(input("Введите x:\n"))
            if x <= 0:
                print('x must be greater than 0!')
                continue
            res = f(x)
            break
        except ValueError:
            print("x must be a number")
    print(f'f({x}) = {res}')


if __name__ == '__main__':
    main()
