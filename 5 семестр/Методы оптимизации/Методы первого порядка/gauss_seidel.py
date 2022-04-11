import numpy as np
from const import func, assess_func
from sympy import Symbol
from sympy.solvers import solve

t = Symbol('t')


def calculate_step(f, x, diff_val, basis):
    t_function = f.calc(x - t * diff_val * basis)
    return float(solve(t_function.diff(t), t)[0])


def generate_n_basis_vectors(n):
    return np.array([[1. if k == j else 0. for k in range(n)] for j in range(n)])


def gauss_seidel_method(f, x0, epsilon1=0.1, epsilon2=0.1, M=100):
    x_list = [[np.array(x0).astype(float)]]
    basis_vectors = generate_n_basis_vectors(len(f.args))
    for j in range(M):
        for k, arg in enumerate(f.args):
            gradient = f.gradient_value(x_list[j][k])
            if np.linalg.norm(gradient) < epsilon1:
                return x_list[j][k], j + 1

            partial_diff_val = f.partial_diff(arg, x_list[j][k])
            step = calculate_step(f, x_list[j][k], partial_diff_val, basis_vectors[k])
            x_list[j].append(x_list[j][k] - step * partial_diff_val * basis_vectors[k])

            if np.linalg.norm(x_list[j][k + 1] - x_list[j][k]) < epsilon2 \
                    and abs(f.calc(x_list[j][k + 1]) - f.calc(x_list[j][k])) < epsilon2 \
                    and len(x_list) > 2 \
                    and np.linalg.norm(x_list[j][k] - x_list[j][k - 1]) < epsilon2 \
                    and abs(f.calc(x_list[j][k]) - f.calc(x_list[j][k - 1])) < epsilon2:
                return x_list[j][k + 1], j + 1

        x_list.append([x_list[-1][-1]])

    return x_list[-1][-1], M


if __name__ == '__main__':
    print(gauss_seidel_method(assess_func, [-10, 10], epsilon1=0.1, epsilon2=0.15, M=10))
