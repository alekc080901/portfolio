from const import func, assess_func
import numpy as np


def constant_gradient_descent_method(f, x0, epsilon=0.1, epsilon1=0.1, epsilon2=0.1, initial_step=0.5, M=100):
    x_list = [np.array(x0).astype(float)]
    k = 0
    while k < M:
        step = initial_step

        gradient = f.gradient_value(x_list[k])
        if np.linalg.norm(gradient) < epsilon1:
            return x_list[k], k + 1

        x_list.append(x_list[k] - step * gradient)
        while not (f.calc(x_list[k + 1]) - f.calc(x_list[k]) < 0 or
                   f.calc(x_list[k + 1]) - f.calc(x_list[k]) < -epsilon * gradient.dot(gradient)):
            step /= 2
            x_list[k + 1] = x_list[k] - step * gradient

        if np.linalg.norm(x_list[k + 1] - x_list[k]) < epsilon2 \
                and abs(f.calc(x_list[k + 1]) - f.calc(x_list[k])) < epsilon2 \
                and len(x_list) > 2 \
                and np.linalg.norm(x_list[k] - x_list[k - 1]) < epsilon2 \
                and abs(f.calc(x_list[k]) - f.calc(x_list[k - 1])) < epsilon2:
            return x_list[k + 1], k + 1

        k += 1

    return x_list[-1], k + 1


if __name__ == '__main__':
    print(constant_gradient_descent_method(assess_func, [10, -10], epsilon1=0.1, epsilon2=0.1, initial_step=0.5, M=20))
