import numpy as np
import matplotlib.pyplot as plt
from const import exact_extremum, assess_func
from newton import newton_method
from newton_raphson import newton_raphson_method
from marquardt import marquardt_method


def check_params_format(*args):
    if any(map(lambda arg: arg is None, args)):
        return False

    are_params_list = list(map(lambda x: isinstance(x, list), args))
    if any(are_params_list) and not all(are_params_list):
        return False

    if all(are_params_list) and len(set(map(len, args))) != 1:
        return False
    return True


def to_list(var):
    if not isinstance(var, list):
        return [var]
    return var


def assess(method, param_name, param_start, param_end, param_step, **kwargs):
    if not check_params_format(param_start, param_end, param_step):
        raise Exception('Wrong parameter data type!')

    param_start, param_end, param_step = to_list(param_start), to_list(param_end), to_list(param_step)

    deltas = []
    parameters = []
    iteration_numbers = []

    for params in zip(
            *[np.arange(param_start[j], param_end[j], param_step[j]) for j in range(len(param_step))]
    ):

        params = list(params) if len(params) != 1 else params[0]

        parameter_val = {param_name: params}

        estimated_extremum, iteration_num = method(**parameter_val, **kwargs)
        delta = sum([abs(exact_extremum[i] - estimated_extremum[i]) for i in range(len(estimated_extremum))])

        deltas.append(delta)
        parameters.append(params)
        iteration_numbers.append(iteration_num)

    plt.figure(figsize=(10, 4))
    plt.subplot(1, 2, 1)
    plt.plot(parameters, deltas, c=np.random.rand(3,))
    plt.xlabel(param_name + '-parameter'),
    plt.ylabel('accuracy')
    plt.subplot(1, 2, 2)
    plt.plot(parameters, iteration_numbers, c=np.random.rand(3, ))
    plt.xlabel(param_name + '-parameter'),
    plt.ylabel('iterations_number')
    plt.show()


if __name__ == '__main__':
    assess(newton_method, 'M', 1, 15, 1, f=assess_func, x0=(-10, 10))
