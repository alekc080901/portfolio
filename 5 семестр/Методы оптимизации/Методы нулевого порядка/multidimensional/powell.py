import numpy as np
from const import x, func, Function
import one_dimensional.powell as one_dim
import math


def init_directions(length):
    directions = np.zeros((length, length))
    for i, row in enumerate(directions):
        row[i] = 1.

    np.insert(directions, 0, directions[-1])
    return np.array(directions)


def change_directions(directions, length, new_direction):
    new_directions = np.array([d for d in directions[1:]])
    np.insert(new_directions, [0, length], new_direction)

    if np.linalg.matrix_rank(new_directions) == length:
        return new_directions
    return directions


def powell_method_n(f, x0, interval, epsilon=0.01):
    n = len(x0)
    x0 = np.array(x0).astype(float)
    d = init_directions(len(x0))

    y = x0.copy()
    iterations = 0
    while True:
        iterations += 1
        y0 = y.copy()

        for i in range(n):
            one_dim_func = Function(f.calc(y + x * d[i]), x)
            t = one_dim.powell_method_1(one_dim_func, interval)[0]
            y = y + t * d[i]

            if i == 0:
                y1 = y.copy()
            elif i == n - 2 and (y == y0).all():
                return y, iterations

        if (y == y1).all():
            return y, iterations

        if math.sqrt(sum(np.square(y - x0))) < epsilon:
            return y, iterations

        d = change_directions(d, n, y - y1)
        x0 = y.copy()


if __name__ == '__main__':
    print(powell_method_n(func, (500, 500), interval=[-1000, 1000], epsilon=0.01))
