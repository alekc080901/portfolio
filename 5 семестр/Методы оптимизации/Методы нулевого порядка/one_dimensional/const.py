from sympy import Symbol


class Function:

    def __init__(self, function, args):
        self.func = function
        self.args = args if isinstance(args, list) or isinstance(args, tuple) else [args]

    def _form_arguments(self, values):
        return {argument: value for argument, value in zip(self.args, values)}

    def calc(self, values):
        if not isinstance(values, list) and not isinstance(values, tuple):
            values = [values]
        arguments_dict = self._form_arguments(values)
        return self.func.subs(arguments_dict)


x = Symbol('x')
# func = 7 * (x ** 2) - 2 * x - 2
# 4 * x**4 - 4 * x**3
func = Function(x**4 + 2 * x**2 + 4 * x + 1, x)

function_interval = (-50, 50)
exact_extremum = 3
