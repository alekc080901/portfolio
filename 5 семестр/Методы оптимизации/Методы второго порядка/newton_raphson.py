import numpy as np
from sympy.solvers import solve
from sympy import Symbol
from const import func

t = Symbol('t')


def matrix_positivity_check(arr):
    if arr.shape[0] != arr.shape[1]:
        raise ValueError('Matrix must be square!')

    return all([np.linalg.det(arr[:i + 1, :i + 1]) > 0 for i in range(arr.shape[0])])


def calculate_step(f, x, d):
    t_function = f.calc(x + t * d)
    return solve(t_function.diff(t), t)[0]


def newton_raphson_method(f, x0, epsilon1=0.1, epsilon2=0.1, M=100):
    x_list = [np.array(x0).astype(float)]
    d_list = []
    k = 0
    while k < M:
        gradient = f.gradient_value(x_list[k])

        if np.linalg.norm(gradient) < epsilon1:
            return x_list[k], k + 1

        hessian = f.hessian(x_list[k])
        inv_hessian = np.linalg.inv(hessian)

        if matrix_positivity_check(inv_hessian):
            d_list.append(-inv_hessian @ gradient.reshape((len(gradient), 1)).squeeze())
            step = 1
        else:
            d_list.append(-gradient)
            step = calculate_step(f, x_list[k], d_list[k])

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
    print(newton_raphson_method(func, [0.5, 1], epsilon1=0.1, epsilon2=0.15, M=10))
