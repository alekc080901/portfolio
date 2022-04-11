import numpy as np
from collections import deque


def array_to_deque(arr: np.ndarray):
    new_deque = deque()
    for elem in arr:
        new_deque.append(list(elem))
    return new_deque


def min_item_in_deque(queue: deque):
    idx = np.argmin(queue) // len(queue[0])
    return queue[idx]


def johnson(sequence: np.ndarray):
    seq = array_to_deque(sequence)
    start_seq = deque()
    end_seq = deque()

    while len(seq) > 0:
        min_item = min_item_in_deque(seq)

        if min_item[0] - min_item[1] < 0:
            start_seq.append(min_item)
        else:
            end_seq.appendleft(min_item)

        seq.remove(min_item)

    return tuple(start_seq) + tuple(end_seq)


def main():
    time_table = np.array([[5, 7, 2, 8, 4, 9, 1, 6], [4, 3, 5, 6, 10, 2, 4, 5]]).swapaxes(0, 1)
    print("Начальный порядок:")
    print(time_table, '\n')

    johnson_order = johnson(time_table)

    print("Преобразованный порядок:")
    print(np.array(johnson_order))


if __name__ == '__main__':
    main()
