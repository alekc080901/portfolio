from fibonacci import fibonacci_method as fibonacci
from powell import powell_method_1 as powell
from matplotlib import pyplot as plt
from const import Function
from sympy import Symbol
import numpy as np
import math
from time import time

x = Symbol('x')


param_start = 0.01
param_end = 2.
param_step = 0.02
function_interval = (-20, 20)

plt.rcParams["figure.figsize"] = (10, 5)


def assess(method, *args, **kwargs):
    t1 = time()
    extremum = method(*args, **kwargs)[0]
    t2 = time()
    return extremum, t2 - t1


def compare(func, exact_extremum):
    deltas = {'powell': [], 'fib': []}
    iterations = {'powell': [], 'fib': []}
    epsilons = []

    for param in np.arange(param_start, param_end, param_step):
        powell_results = assess(powell, func, function_interval, epsilon1=param, epsilon2=param)
        fibonacci_results = assess(fibonacci, func, function_interval, l=param)

        deltas['powell'].append(abs(powell_results[0] - exact_extremum))
        deltas['fib'].append(abs(fibonacci_results[0] - exact_extremum))
        iterations['powell'].append(powell_results[1])
        iterations['fib'].append(fibonacci_results[1])

        epsilons.append(param)

    fig, ax = plt.subplots(nrows=1, ncols=2)
    ax[0].plot(epsilons, deltas['powell'], c=np.random.rand(3, ))
    ax[0].plot(epsilons, deltas['fib'], c=np.random.rand(3, ))
    ax[0].set_xlabel('epsilon, l')
    ax[0].set_ylabel('accuracy')
    ax[0].legend(['Пауэлл', 'Фибоначчи'])
    ax[1].plot(epsilons, iterations['powell'], c=np.random.rand(3, ))
    ax[1].plot(epsilons, iterations['fib'], c=np.random.rand(3, ))
    ax[1].set_xlabel('epsilon, l')
    ax[1].set_ylabel('iterations_number')
    ax[1].legend(['Пауэлл', 'Фибоначчи'])
    plt.show()


if __name__ == '__main__':
    func1 = Function(x ** 4 + 2 * x ** 2 + 4 * x + 1, x)
    func2 = Function(x * (x - 1)**2 * (x - 3)**3, x)
    func3 = Function(math.e**x - 2 * x + 4 * (x + 2)**2, x)
    exact_extremum1 = -0.682
    exact_extremum2 = 0.263
    exact_extremum3 = -1.77
    compare(func3, exact_extremum3)
    compare(func1, exact_extremum1)
    compare(func2, exact_extremum2)
