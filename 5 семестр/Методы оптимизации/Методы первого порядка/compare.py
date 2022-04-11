from constant_descent import constant_gradient_descent_method
from coordinate_descent import coordinate_gradient_descent_method
from steepest_descent import steepest_gradient_descent_method
from gauss_seidel import gauss_seidel_method
from fletcher_reeves import fletcher_reeves_method
from devidon_fletcher_powell import devidon_fletcher_powell_method
from matplotlib import pyplot as plt
from const import Function
from sympy import Symbol
import numpy as np
from time import time

x1 = Symbol('x1')
x2 = Symbol('x2')

param_start = 0.01
param_end = 3
param_step = 0.03
x0 = [-10, 10]

plt.rcParams["figure.figsize"] = (10, 5)


def assess(method, *args, **kwargs):
    t1 = time()
    extremum = method(*args, **kwargs)[0]
    t2 = time()
    return extremum, t2 - t1


def compare(func, exact_extremum):
    deltas = {'constant_gradient': [], 'coordinate_gradient': [], 'steepest_gradient': [],
              'gauss_seidel': [], 'fletcher_reeves': [], 'devidon_fletcher_powell': []}
    performances = {'constant_gradient': [], 'coordinate_gradient': [], 'steepest_gradient': [],
                    'gauss_seidel': [], 'fletcher_reeves': [], 'devidon_fletcher_powell': []}
    names = tuple(deltas.keys())

    epsilons = np.arange(param_start, param_end, param_step)

    for param in np.arange(param_start, param_end, param_step):
        methods = (constant_gradient_descent_method, coordinate_gradient_descent_method,
                   steepest_gradient_descent_method, gauss_seidel_method, fletcher_reeves_method,
                   devidon_fletcher_powell_method)
        results = [assess(method, func, x0, epsilon1=param, epsilon2=param) for method in methods]
        [deltas[key].append(sum([abs(exact_extremum[i] - result[0][i]) for i in range(len(exact_extremum))]))
         for key, result in zip(names, results)]
        [performances[key].append(result[1]) for key, result in zip(names, results)]

    fig, ax = plt.subplots(nrows=1, ncols=2)
    colors = [np.random.rand(3, ) for _ in range(len(methods))]
    [ax[0].plot(epsilons, delta, c=color) for delta, color in zip(deltas.values(), colors)]

    ax[0].set_xlabel('epsilon')
    ax[0].set_ylabel('accuracy')

    [ax[1].plot(epsilons, iteration, c=color) for iteration, color in zip(performances.values(), colors)]

    ax[1].set_xlabel('epsilon')
    ax[1].set_ylabel('time')

    ax[1].legend(names)
    plt.show()


if __name__ == '__main__':
    # func1 = Function(3 * x1 ** 2 + x1 * x2 + 2 * x2 ** 2 - x1 - 4 * x2, (x1, x2))
    # func2 = Function((x1 - 4)**2 + (x2 - 1)**2, (x1, x2))
    func3 = Function(2 * x1**2 - 2 * x1 + x1 * x2 - x2 + x2**2, (x1, x2))
    # exact_extremum1 = [0., 1.]
    # exact_extremum2 = [4, 1]
    exact_extremum3 = [3/7, 2/7]
    # compare(func1, exact_extremum1)
    # compare(func2, exact_extremum2)
    compare(func3, exact_extremum3)
