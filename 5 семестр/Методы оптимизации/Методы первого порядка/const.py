from sympy import Symbol
from function import Function


x1 = Symbol('x1')
x2 = Symbol('x2')

f_arguments = (x1, x2)
func = Function(2 * x1**2 + x1 * x2 + x2**2, f_arguments)

# assess_func = Function((x1 + x2 - 1) ** 2 + 2 * (x1 - 2) ** 2, f_arguments)
# assess_func = Function(x1**4 + x2**4 - 2 * x1**2 + 4 * x1 * x2 - 2 * x2**2, (x1, x2))
assess_func = Function(2 * x1**2 - x2 + 18 * x2**2, (x1, x2))

exact_extremum = [2, -1]


def form_arguments(values):
    return {argument: value for argument, value in zip(f_arguments, values)}
