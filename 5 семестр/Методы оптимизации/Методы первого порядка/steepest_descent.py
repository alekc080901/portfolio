import numpy as np
from sympy.solvers import solve
from sympy import Symbol
from const import func, assess_func

t = Symbol('t')


def calculate_step(f, x, gradient):
    t_function = f.calc(x - t * gradient)
    return solve(t_function.diff(t), t)[0]


def steepest_gradient_descent_method(f, x0, epsilon1=0.1, epsilon2=0.1, M=100):
    x_list = [np.array(x0).astype(float)]
    k = 0
    while k < M:
        gradient = f.gradient_value(x_list[k])
        if np.linalg.norm(gradient) < epsilon1:
            return x_list[k], k + 1

        step = float(calculate_step(f, x_list[k], gradient))

        x_list.append(x_list[k] - step * gradient)

        if np.linalg.norm(x_list[k + 1] - x_list[k]) < epsilon2 \
                and abs(f.calc(x_list[k + 1]) - f.calc(x_list[k])) < epsilon2 \
                and len(x_list) > 2 \
                and np.linalg.norm(x_list[k] - x_list[k - 1]) < epsilon2 \
                and abs(f.calc(x_list[k]) - f.calc(x_list[k - 1])) < epsilon2:
            return x_list[k + 1], k + 1

        k += 1

    return x_list[-1], k


if __name__ == '__main__':
    print(steepest_gradient_descent_method(assess_func, [0.5, 1], epsilon1=0.1, epsilon2=0.1, M=15))
