import numpy as np
from const import func
import math


def init_directions(length):
    directions = np.array([np.zeros((length, 1)) for _ in range(length)])
    for i in range(length):
        directions[i][i] = 1.

    return (directions)


def calc_a_param(lambdas, directions):
    a_list = []
    for i in range(len(directions)):
        if lambdas[i] == 0.:
            a_list.append(directions[i])
            continue

        a = np.zeros((len(directions), 1))
        for lmbda, d in zip(lambdas[i:], directions[i:]):
            a = a + lmbda * d
        a_list.append(a)

    return a_list


def rosenbrock_algorithm(f, x0, alpha=2, beta=-0.5, epsilon=0.01, N=4, steps_list=None):
    x0 = np.array(x0).astype(float)
    if steps_list is None:
        steps_list = [1.] * len(x0)
    steps = np.array(steps_list).astype(float)

    directions = init_directions(len(x0))
    y = x0.copy()

    iterations = 0
    count = 0
    while True:
        iterations += 1
        l = 0
        unchanged_y = y.copy()
        unchanged_steps = steps.copy()

        for i in range(len(x0)):
            # print(count, steps, y)
            count += 1
            point_direction = np.array(np.transpose(directions[i])).ravel()
            if f.calc(y + steps[i] * point_direction) < f.calc(y):
                y += steps[i] * point_direction
                steps[i] *= alpha
            else:
                steps[i] *= beta

        if f.calc(y) < f.calc(unchanged_y):
            continue

        elif f.calc(y) == f.calc(x0) and l <= N:
            l += 1
            if all(abs(unchanged_steps) < epsilon):
                return y, iterations
            continue

        else:
            if math.sqrt(sum(np.square(y - x0))) <= epsilon:
                return y, iterations

            lambdas = sum((y - x0) * directions)
            lambdas = np.array([l[0] for l in lambdas])

            a_list = calc_a_param(lambdas, directions)

            new_directions = directions.copy()

            b = a_list[0]
            new_directions[0] = b / np.linalg.norm(b)
            for i in range(1, len(directions)):
                b = a_list[i] - float(np.matrix(np.transpose(a_list[i])) * np.matrix(directions[i-1])) * directions[i-1]
                new_directions[i] = b / np.linalg.norm(b)

            x0 = y.copy()
            steps = np.array(steps_list).astype(float)

            for i in range(len(new_directions)):
                if lambdas[i] != 0:
                    directions[i] = new_directions[i]


if __name__ == '__main__':
    print(rosenbrock_algorithm(func, (0.5, 1), alpha=3, beta=-0.5, steps_list=[0.1, 0.1], N=3, epsilon=0.075))
