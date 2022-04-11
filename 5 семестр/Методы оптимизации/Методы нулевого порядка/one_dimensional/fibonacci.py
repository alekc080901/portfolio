from const import func, function_interval


def fibonacci_generator():
    a, b = 1, 1
    while True:
        yield a
        a, b = b, a + b


def fibonacci(n: int):
    if n < 1:
        raise Exception('Incorrect n!')

    generator = fibonacci_generator()
    for _ in range(n):
        number = next(generator)
    return number


def fibonacci_list(n: int):
    a, b = 1, 1
    series = []
    for _ in range(n):
        series.append(a)
        a, b = b, a + b
    return series


def find_iteration_number(l0: float, l: float):
    fib_gen = fibonacci_generator()

    n = 1
    while next(fib_gen) < (l0 / l):
        n += 1
    return n


def fibonacci_method(f, interval: tuple, l=0.1, epsilon=0.1, float_n=3):
    if len(interval) != 2 or interval[0] > interval[1]:
        raise Exception('Wrong interval!')

    a0 = interval[0]
    b0 = interval[1]
    N = find_iteration_number(b0 - a0, l)
    F = fibonacci_list(N)

    ak = a0
    bk = b0
    yk = ak + F[N - 2 - 1] / F[N - 1] * (bk - ak)
    zk = ak + F[N - 1 - 1] / F[N - 1] * (bk - ak)

    for k in range(N - 3):
        fyk = f.calc(yk)
        fzk = f.calc(zk)

        if fyk <= fzk:
            bk = zk
            zk = yk
            yk = ak + F[N - k - 3 - 1] / F[N - k - 1 - 1] * (bk - ak)
        else:
            ak = yk
            yk = zk
            zk = ak + F[N - k - 2 - 1] / F[N - k - 1 - 1] * (bk - ak)

    yn = zk
    zn = zk + epsilon

    if f.calc(yn) <= f.calc(zn):
        if __name__ == '__main__':
            print('Интервал неопределенности:', round(ak, float_n), round(zn, float_n))

        return round((ak + zn) / 2, 3), N - 3
    else:
        if __name__ == '__main__':
            print('Интервал неопределенности:', round(yn, float_n), round(bk, float_n))

        return round((yn + bk) / 2, 3), N - 3


def main():
    estimated_extremum = fibonacci_method(func, function_interval)[0]
    print('Точка экстремума:', estimated_extremum)
    print('Экстремум:', round(func.calc(estimated_extremum), 3))


if __name__ == '__main__':
    main()
