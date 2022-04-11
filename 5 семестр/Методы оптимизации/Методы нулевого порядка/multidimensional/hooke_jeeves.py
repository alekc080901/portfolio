from const import func


def hooke_jeeves_method(f, x0, steps=None, epsilon=0.099, lambda_parameter=1.5, decreasing_coef=1.1):
    if steps is None:
        steps = [0.5] * len(x0)
    xk = x0

    y = xk.copy()
    iter_num = 0
    while all(map(lambda step: step > epsilon, steps)):
        iter_num += 1
        for i in range(len(x0)):
            if f.calc(y[:i] + [y[i] + steps[i]] + y[i+1:]) < f.calc(y):
                y[i] += steps[i]
            elif f.calc(y[:i] + [y[i] - steps[i]] + y[i+1:]) < f.calc(y):
                y[i] -= steps[i]

        if f.calc((y[0], y[1])) < f.calc((xk[0], xk[1])):
            gap = [a-b for a, b in zip(y, xk)]
            increasing = list(map(lambda x: lambda_parameter * x, gap))

            xk = y.copy()
            y = [a+b for a, b in zip(y, increasing)]
            continue
        else:
            steps = list(map(lambda step: step / decreasing_coef, steps))
            y = xk.copy()

    return xk, iter_num


def main():
    print(hooke_jeeves_method(func, [10, -10], epsilon=0.7, lambda_parameter=1, decreasing_coef=2, steps=[0.1, 0.1]))


if __name__ == '__main__':
    main()
