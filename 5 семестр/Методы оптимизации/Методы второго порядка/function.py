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

    def diff(self, variable):
        return Function(self.func.diff(variable), self.args)

    def _gradient(self):
        return (self.diff(arg) for arg in self.args)

    def gradient_value(self, x):
        return np.array(list(map(lambda f: f.calc(x), self._gradient()))).astype(float)

    def hessian(self, x):
        return np.array([
            self.diff(var1)
                .diff(var2)
                .calc(x)
            for var1 in self.args
            for var2 in self.args
        ]).reshape((len(self.args), len(self.args))).astype(float)
