import numpy as np
from const import func, assess_func


def generate_n_basis_vectors(n):
    return np.array([[1. if k == j else 0. for k in range(n)] for j in range(n)])


def coordinate_gradient_descent_method(f, x0, epsilon=0.1, epsilon1=0.1, epsilon2=0.1, initial_step=0.5, M=100):
    x_list = [[np.array(x0).astype(float)]]
    basis_vectors = generate_n_basis_vectors(len(f.args))
    for j in range(M):

        for k, arg in enumerate(f.args):
            step = initial_step

            gradient = f.gradient_value(x_list[j][k])
            if np.linalg.norm(gradient) < epsilon1:
                return x_list[j][k], j + 1

            x_list[j].append(x_list[j][k] - step * f.partial_diff(arg, x_list[j][k]) * basis_vectors[k])
            while not (f.calc(x_list[j][k + 1]) - f.calc(x_list[j][k]) < 0 or
                       f.calc(x_list[j][k + 1]) - f.calc(x_list[j][k]) < -epsilon * gradient.dot(gradient)):
                step /= 2
                x_list[j][k + 1] = x_list[j][k] - step * f.partial_diff(arg, x_list[j][k]) * basis_vectors[k]

            if np.linalg.norm(x_list[j][k + 1] - x_list[j][k]) < epsilon2 \
                    and abs(f.calc(x_list[j][k + 1]) - f.calc(x_list[j][k])) < epsilon2 \
                    and len(x_list) > 2 \
                    and np.linalg.norm(x_list[j][k] - x_list[j][k - 1]) < epsilon2 \
                    and abs(f.calc(x_list[j][k]) - f.calc(x_list[j][k - 1])) < epsilon2:
                return x_list[j][k + 1], j + 1

        x_list.append([x_list[-1][-1]])

    return x_list[-1][-1], M


if __name__ == '__main__':
    print(
        coordinate_gradient_descent_method(assess_func, [10, -10], epsilon1=0.1, epsilon2=0.1, initial_step=0.5, M=10))
