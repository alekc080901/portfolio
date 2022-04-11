import numpy as np
from sympy.solvers import solve
from sympy import Symbol
from const import func, assess_func

t = Symbol('t')


def generate_n_basis_vectors(n):
    return np.array([[1. if k == j else 0. for k in range(n)] for j in range(n)])


def calculate_step(f, x, a, gradient):
    t_function = f.calc(x - t * np.matmul(a, gradient))
    return solve(t_function.diff(t), t)[0]


def calculate_a(f, x_list, a, k):
    prev_gradient, gradient = f.gradient_value(x_list[k - 1]), f.gradient_value(x_list[k])
    dx = x_list[k] - x_list[k - 1]
    dg = gradient - prev_gradient

    a_first_part = np.matmul(np.transpose([dx]), [dx]) / np.matmul([dx], np.transpose([dg]))
    a_second_part_numerator = np.matmul(np.matmul(np.matmul(a, np.transpose([dg])), [dg]), a)
    a_second_part_denominator = np.matmul(np.matmul([dg], a), np.transpose([dg]))

    return a_first_part - a_second_part_numerator / a_second_part_denominator


def devidon_fletcher_powell_method(f, x0, epsilon1=0.1, epsilon2=0.1, M=100):
    x_list = [np.array(x0).astype(float)]
    k = 0
    a = generate_n_basis_vectors(2)
    while k < M:
        gradient = f.gradient_value(x_list[k])

        if np.linalg.norm(gradient) < epsilon1:
            return x_list[k], k + 1

        if k != 0:
            a += calculate_a(f, x_list, a, k)

        step = float(calculate_step(f, x_list[k], a, gradient))
        d = - np.matmul(a, gradient)

        x_list.append(x_list[k] + step * d)

        # print(x_list[k], a, step, sep='\n', end='\n\n')

        if np.linalg.norm(x_list[k + 1] - x_list[k]) < epsilon2 \
                and abs(f.calc(x_list[k + 1]) - f.calc(x_list[k])) < epsilon2 \
                and len(x_list) > 2 \
                and np.linalg.norm(x_list[k] - x_list[k - 1]) < epsilon2 \
                and abs(f.calc(x_list[k]) - f.calc(x_list[k - 1])) < epsilon2:
            return x_list[k + 1], k + 1

        k += 1

    return x_list[-1], k


if __name__ == '__main__':
    print(devidon_fletcher_powell_method(assess_func, [-10, 10], epsilon1=0.1, epsilon2=0.15, M=10))
