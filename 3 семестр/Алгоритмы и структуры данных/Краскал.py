"""Алгоритм Краскала"""

import graphviz
import os

os.environ["PATH"] += os.pathsep + 'C:/Program Files (x86)/Graphviz2.38/bin/'


def input_nat0(name=''):
    while True:
        number = input(name)
        try:
            int(number)
            if int(number) < 0:
                print('Число должно быть неотрицательным')
            else:
                number = int(number)
                break
        except ValueError:
            print('Неверный тип данных')
    return number


def make_dicts(x, parent, rank):
    if not isinstance(x, int):
        raise ValueError('Неправильный тип вершины графа')
    parent[x] = x
    rank[x] = 0
    return parent, rank


def find(x, parent):
    if parent[x] != x:
        parent[x] = find(parent[x], parent)
    return parent[x]


def union(x, y, parent, rank):
    if not isinstance(x, int) or not isinstance(y, int):
        raise ValueError('Неправильный тип вершины графа')

    x_root = find(x, parent)
    y_root = find(y, parent)
    if rank[x_root] < rank[y_root]:
        x_root, y_root = y_root, x_root
    parent[y_root] = x_root
    if rank[x_root] == rank[y_root]:
        rank[x_root] += 1


def kruskal(g):
    tops = set()
    for edges in g:
        tops.add(edges)
    v = len(tops) + 1

    final = {}
    parent = {}
    rank = {}
    for connection in range(1, v+1):
        parent, rank = make_dicts(connection, parent, rank)
    for connection in g:
        if find(connection[0], parent) != find(connection[1], parent):
            final[connection] = g[connection]
            union(find(connection[0], parent), find(connection[1], parent), parent, rank)
    return final


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


def graph_view(graph_first, graph_final, top):
    show = graphviz.Graph(filename="Graph", format='png')

    node_lst = [i for i in range(1, top + 1)]  # Показ вершин графа
    for top in node_lst:
        show.node(str(top))

    for edge in graph_first:
        if edge in graph_final:
            show.edge(str(edge[0]), str(edge[1]), label=str(graph_final[edge]))  # Показ веток финального графа
        else:
            show.edge(str(edge[0]), str(edge[1]), label=str(graph_first[edge]),  # Показ веток начального графа
                         color="gray", fontcolor="gray")
    show.view()


def main():
    my_check = input('Ввод самим (1) или по умолчанию (0) ')
    if my_check == '1':
        number_of_tops = input_nat0('Введите количество вершин ')
        graph = graph_create(number_of_tops)
        graph_view(graph, kruskal(graph), number_of_tops)
    else:
        graph = {(2, 5): 1, (4, 5): 2, (1, 3): 3, (1, 2): 6, (2, 4): 7, (3, 4): 8}
        graph_view(graph, kruskal(graph), 5)


if __name__ == '__main__':
    main()
