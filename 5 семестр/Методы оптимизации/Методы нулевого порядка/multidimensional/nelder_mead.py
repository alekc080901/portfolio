import numpy as np
from const import func
from functools import reduce
import math


def nelder_mead_algorithm(f, vertexes, alpha=1., beta=0.5, gamma=2., epsilon=0.01):
    n = len(vertexes) - 1

    iterations = 0
    while True:
        iterations += 1
        vertexes_y = list(map(f.calc, vertexes))

        vertexes = np.array(sorted(vertexes, key=f.calc))

        min_vert, premin_vert = vertexes[:2]
        worst_vert = vertexes[-1]

        mass_center = sum(vertexes[:-1]) / n

        sigma = math.sqrt(reduce(lambda prev, y: prev + (y - f.calc(mass_center))**2, vertexes_y, 0) / (n + 1))

        if sigma <= epsilon:
            return min_vert, iterations

        reflected_vert = mass_center + alpha * (mass_center - worst_vert)

        if f.calc(reflected_vert) <= f.calc(min_vert):
            stretched_vert = mass_center + gamma * (reflected_vert - mass_center)
            vertexes[-1] = stretched_vert if f.calc(stretched_vert) < f.calc(min_vert) else reflected_vert

        elif f.calc(premin_vert) < f.calc(reflected_vert) <= f.calc(worst_vert):
            compressed_vert = mass_center + beta * (worst_vert - mass_center)
            vertexes[-1] = compressed_vert

        else:
            vertexes = min_vert + (vertexes - min_vert) / 2


if __name__ == '__main__':
    print(nelder_mead_algorithm(func, ((-10, -10), (10, -10), (0, 10)), alpha=1, beta=0.5, gamma=0.9))
