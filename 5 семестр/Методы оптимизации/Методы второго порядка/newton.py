import numpy as np
from const import func


def matrix_positivity_check(arr):
    if arr.shape[0] != arr.shape[1]:
        raise ValueError('Matrix must be square!')

    return all([np.linalg.det(arr[:i + 1, :i + 1]) > 0 for i in range(arr.shape[0])])


def calculate_step(f, x, d):
    t = 0
    while True:
        t += 0.5
        new_x1 = x + t * d
        new_x2 = x - t * d
        if f.calc(new_x1) < f.calc(x):
            return new_x1
        if f.calc(new_x2) < f.calc(x):
            return new_x2


def newton_method(f, x0, epsilon1=0.1, epsilon2=0.1, M=100):
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
    print(newton_method(func, [0.5, 1], epsilon1=0.1, epsilon2=0.15, M=10))
