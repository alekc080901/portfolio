import numpy as np
from sympy import Symbol
from const import func


def generate_n_basis_vectors(n):
    return np.array([[1. if k == j else 0. for k in range(n)] for j in range(n)])


def marquardt_method(f, x0, epsilon1=0.1, my=10, M=100, **kwargs):
    x = np.array(x0).astype(float)
    k = 0
    while k < M:
        gradient = f.gradient_value(x)

        if np.linalg.norm(gradient) < epsilon1:
            return x, k + 1

        E = generate_n_basis_vectors(2)
        hessian = f.hessian(x)

        while True:
            h_E = hessian + my * E
            inv_h_E = np.linalg.inv(h_E)

            d = -inv_h_E @ gradient.reshape((len(gradient), 1)).squeeze()

            x_old = x.copy()
            x += d

            if f.calc(x) < f.calc(x_old):
                k += 1
                my /= 2
                break

            my *= 2

    return x, k


if __name__ == '__main__':
    print(marquardt_method(func, [0.5, 1], epsilon1=0.1, my=20, M=10))
