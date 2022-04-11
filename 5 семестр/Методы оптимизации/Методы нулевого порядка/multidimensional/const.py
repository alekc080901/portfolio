from sympy import Symbol
import numpy as np


class Function:

    def __init__(self, function, args):
        self.func = function
        self.args = args if isinstance(args, list) or isinstance(args, tuple) or isinstance(args, np.ndarray) else [args]

    def _form_arguments(self, values):
        return {argument: value for argument, value in zip(self.args, values)}

    def calc(self, values):
        if not isinstance(values, list) and not isinstance(values, tuple) and not isinstance(values, np.ndarray):
            values = [values]
        arguments_dict = self._form_arguments(values)
        return self.func.subs(arguments_dict)


x1 = Symbol('x1')
x2 = Symbol('x2')
x = Symbol('x')
func = Function((x1 + x2 - 1)**2 + 2 * (x1 - 2)**2, (x1, x2))

function_interval = (-6, 6)

f_arguments = (x1, x2)

exact_extremum = [2, -1]


def form_arguments(values):
    return {argument: value for argument, value in zip(f_arguments, values)}


def f(values):
    arguments_dict = form_arguments(values)
    return func.subs(arguments_dict)
