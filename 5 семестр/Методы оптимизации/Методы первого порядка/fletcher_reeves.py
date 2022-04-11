import numpy as np
from sympy.solvers import solve
from sympy import Symbol
from const import func, assess_func

t = Symbol('t')


def calculate_step(f, x, d):
    t_function = f.calc(x + t * d)
    return solve(t_function.diff(t), t)[0]


def fletcher_reeves_method(f, x0, epsilon1=0.1, epsilon2=0.1, M=100):
    x_list = [np.array(x0).astype(float)]
    d_list = []
    k = 0
    while k < M:
        gradient = f.gradient_value(x_list[k])

        if np.linalg.norm(gradient) < epsilon1:
            return x_list[k], k + 1

        if k != 0:
            prev_gradient = f.gradient_value(x_list[k - 1])
            beta = np.linalg.norm(gradient)**2 / np.linalg.norm(prev_gradient)**2
            d = -gradient + beta * d_list[k - 1]
        else:
            d = -gradient

        d_list.append(d)

        step = float(calculate_step(f, x_list[k], d_list[-1]))

        x_list.append(x_list[k] + step * d_list[k])

        if np.linalg.norm(x_list[k + 1] - x_list[k]) < epsilon2 \
                and abs(f.calc(x_list[k + 1]) - f.calc(x_list[k])) < epsilon2 \
                and len(x_list) > 2 \
                and np.linalg.norm(x_list[k] - x_list[k - 1]) < epsilon2 \
                and abs(f.calc(x_list[k]) - f.calc(x_list[k - 1])) < epsilon2:
            return x_list[k + 1], k + 1

        k += 1

    return x_list[-1], k


if __name__ == '__main__':
    print(fletcher_reeves_method(assess_func, [-10, 10], epsilon1=0.1, epsilon2=0.1, M=100))
