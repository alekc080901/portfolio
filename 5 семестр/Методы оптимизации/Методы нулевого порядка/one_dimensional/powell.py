from const import func, function_interval


def calculate_anchor_point(f, x1, step):
    x2 = x1 + step
    y1 = f.calc(x1)
    y2 = f.calc(x2)

    x3 = x1 + 2 * step if y1 > y2 else x1 - step
    y3 = f.calc(x3)

    return {
        x1: y1,
        x2: y2,
        x3: y3
    }


def find_minimal_point(point1, point2, point3):
    (x1, y1), (x2, y2), (x3, y3) = point1, point2, point3
    if min(y1, y2, y3) == y1:
        return x1, y1
    elif min(y1, y2, y3) == y2:
        return x2, y2
    else:
        return x3, y3


def powell_method_1(f, interval: tuple, x1=None, step=0.1, epsilon1=0.1, epsilon2=0.1):
    if x1 and interval[0] > x1 > interval[1]:
        raise Exception('Wrong starting point!')

    if not x1:
        x1 = (interval[0] + interval[1]) / 2

    iteration_num = 0
    while True:
        iteration_num += 1

        (x1, y1), (x2, y2), (x3, y3) = calculate_anchor_point(f, x1, step).items()
        x_min, y_min = find_minimal_point((x1, y1), (x2, y2), (x3, y3))

        numerator_inter = (x2 ** 2 - x3 ** 2) * y1 + (x3 ** 2 - x1 ** 2) * y2 + (x1 ** 2 - x2 ** 2) * y3
        denominator_inter = (x2 - x3) * y1 + (x3 - x1) * y2 + (x1 - x2) * y3

        if denominator_inter == 0:
            x1 = x_min
            continue

        x_inter = numerator_inter / denominator_inter / 2
        f_inter = f.calc(x_inter)

        if abs((y_min - f_inter)) < 1.e-10:
            break

        break_conditions = (
            abs((y_min - f_inter) / f_inter) < epsilon1,
            abs((x_min - x_inter) / x_inter) < epsilon2
        )

        if all(break_conditions):
            break
        elif x1 < x_inter < x3 and x_min < x_inter:
            x1 = x_min
        else:
            x1 = x_inter

    return x_inter, iteration_num


def main():
    x_extremum = powell_method_1(func, function_interval)[0]
    print('Точка экстремума:', round(x_extremum, 3))
    # print('Экстремум:', round(f.calc(x_extremum), 3))


if __name__ == '__main__':
    main()
