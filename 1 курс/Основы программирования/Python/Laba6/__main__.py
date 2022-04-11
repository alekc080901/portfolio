import argparse
import pytest
import Laba6
from check import input_nat0


def graph_create(n):
    g_lst = []
    for i in range(n - 1):  # Создание связей в графе
        for j in range(i + 1, n):
            g_lst.append(i + 1)
            g_lst.append(j + 1)
    g_kort = tuple(g_lst)

    connections = int(len(g_kort) / 2)  # Количество пар связей
    m = 0
    g_dic = {}
    for i in range(connections):  # Ввод веса веток графа
        branch = g_kort[m:m + 2]
        m = m + 2
        print('Введите вес ветки', branch, 'если точки не связаны, вес принять равным 0')
        weight = input_nat0()
        if weight != 0:
            g_dic.update({branch: weight})

    weight_lst = list(g_dic.items())  # Сортировка словаря по возрастанию значений
    weight_lst.sort(key=lambda l: l[1])
    g_dic = {}
    for i in weight_lst:
        g_dic.update({i[0]: i[1]})
    return g_dic


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--test', action="store_true", help='Запуск тестов')
    par_values = parser.parse_args()

    if par_values.test:
        pytest.main(['-v', 'test_kr.py'])

    else:
        my_check = input('Ввод самим (1) или по умолчанию (0) ')
        if my_check == '1':
            number_of_tops = input_nat0('Введите количество вершин ')
            graph = graph_create(number_of_tops)
            Laba6.graph_view(graph, Laba6.kruskal(graph), number_of_tops)
        else:
            graph = {(2, 5): 1, (4, 5): 2, (1, 3): 3, (1, 2): 6, (2, 4): 7, (3, 4): 8}
            Laba6.graph_view(graph, Laba6.kruskal(graph), 5)


if __name__ == '__main__':
    main()
