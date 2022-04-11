from hooke_jeeves import hooke_jeeves_method
from nelder_mead import nelder_mead_algorithm
from powell import powell_method_n
from rosenbrock import rosenbrock_algorithm
from matplotlib import pyplot as plt
from const import Function
from sympy import Symbol
import numpy as np
import math
from time import time

x1 = Symbol('x1')
x2 = Symbol('x2')

param_start = 0.01
param_end = 2.
param_step = 0.02
function_interval = [-50, 50]
x0 = [10, -10]

plt.rcParams["figure.figsize"] = (10, 5)


def assess(method, *args, **kwargs):
    t1 = time()
    extremum = method(*args, **kwargs)[0]
    t2 = time()
    return extremum, t2 - t1


def compare(func, exact_extremum):
    deltas = {'powell': [], 'hooke': [], 'nelder': [], 'rosenbrock': []}
    iterations = {'powell': [], 'hooke': [], 'nelder': [], 'rosenbrock': []}
    epsilons = []

    for param in np.arange(param_start, param_end, param_step):
        hooke_jeeves_results = assess(hooke_jeeves_method, func, x0, epsilon=param, steps=[2.01, 2.01])
        nelder_mead_results = assess(nelder_mead_algorithm, func, ((-10, -10), (10, -10), (0, 10)), epsilon=param)
        rosenbrock_results = assess(rosenbrock_algorithm, func, x0, epsilon=param)
        powell_results = assess(powell_method_n, func, x0, function_interval, epsilon=param)

        delta = sum([abs(exact_extremum[i] - powell_results[0][i]) for i in range(len(exact_extremum))])
        deltas['powell'].append(delta)
        delta = sum([abs(exact_extremum[i] - hooke_jeeves_results[0][i]) for i in range(len(exact_extremum))])
        deltas['hooke'].append(delta)
        delta = sum([abs(exact_extremum[i] - nelder_mead_results[0][i]) for i in range(len(exact_extremum))])
        deltas['nelder'].append(delta)
        delta = sum([abs(exact_extremum[i] - rosenbrock_results[0][i]) for i in range(len(exact_extremum))])
        deltas['rosenbrock'].append(delta)
        iterations['powell'].append(powell_results[1])
        iterations['hooke'].append(hooke_jeeves_results[1])
        iterations['nelder'].append(nelder_mead_results[1])
        iterations['rosenbrock'].append(rosenbrock_results[1])

        epsilons.append(param)

    fig, ax = plt.subplots(nrows=1, ncols=2)
    powell_color = np.random.rand(3, )
    ax[0].plot(epsilons, deltas['powell'], c=powell_color)
    hooke_color = np.random.rand(3, )
    ax[0].plot(epsilons, deltas['hooke'], c=hooke_color)
    nelder_color = np.random.rand(3, )
    ax[0].plot(epsilons, deltas['nelder'], c=nelder_color)
    rosenbrock_color = np.random.rand(3, )
    ax[0].plot(epsilons, deltas['rosenbrock'], c=rosenbrock_color)

    ax[0].set_xlabel('epsilon')
    ax[0].set_ylabel('accuracy')
    ax[0].legend(['Пауэлл', 'Хук-Дживс', 'Нелдер-Мид', 'Розенброк'])

    ax[1].plot(epsilons, iterations['powell'], c=powell_color)
    ax[1].plot(epsilons, iterations['hooke'], c=hooke_color)
    ax[1].plot(epsilons, iterations['nelder'], c=nelder_color)
    ax[1].plot(epsilons, iterations['rosenbrock'], c=rosenbrock_color)

    ax[1].set_xlabel('epsilon')
    ax[1].set_ylabel('iterations_number')

    ax[1].legend(['Пауэлл', 'Хук-Дживс', 'Нелдер-Мид', 'Розенброк'])
    plt.show()


if __name__ == '__main__':
    func1 = Function(3 * x1**2 + x1 * x2 + 2 * x2**2 - x1 - 4 * x2, (x1, x2))
    func2 = Function((x1 - 4)**2 + (x2 - 1)**2, (x1, x2))
    func3 = Function(2 * x1**2 - x2 + 18 * x2**2, (x1, x2))
    exact_extremum1 = [0, 1]
    exact_extremum2 = [4, 1]
    exact_extremum3 = [0, 1/36]
    compare(func3, exact_extremum3)
    compare(func1, exact_extremum1)
    compare(func2, exact_extremum2)
