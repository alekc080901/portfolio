"""Практическая работа №4, вариант 20, Никитин Александр; алгоритм Краскала"""

from check import input_nat0
import graphviz
import os

os.environ["PATH"] += os.pathsep + 'C:/Program Files (x86)/Graphviz2.38/bin/'


def make_dicts(x, parent, rank):
    """
    1 Создание двух словарей
    2 Функция создает два словаря вида parent={'x':x}, rank={'x':0}

    >>>make_dicts(2, {}, {})
    {2: 2} {2: 0}

    :param x: Вершина графа, x > 0
    :type x: int
    :param parent: Словарь, в котором предками каждой точки (изначально) являются они сами.
    :type parent: dict
    :param rank: Словарь, в котором каждой точке соответствует 0 (изначально)
    :type rank: dict
    :return: tuple(parent, rank): tuple
    """
    if not isinstance(x, int):
        raise ValueError('Неправильный тип вершины графа')
    parent[x] = x
    rank[x] = 0
    return parent, rank


def find(x, parent):
    """
    1 Поиск корня точки.
    2 Реализуется обход графа от входной до его корня и связывание этой точки и корня посредством рекурсии.

    >>>find(3, {1: 1, 2: 1, 3: 1, 4: 1, 5: 2})
    1
    >>>find(7, {1:1, 2:3, 3:3, 4:5, 5:1, 6:1, 7:2})
    3
    :param x: вершина графа, x > 0
    :type x: int
    :param parent: Словарь, который содержит пути к корню для разных точек.
    :type parent: dict
    :return: Словарь, который содержит пути к корню для разных точек: dict
    """
    if not isinstance(x, int):
        raise ValueError('Неправильный тип вершины графа')

    if parent[x] != x:
        parent[x] = find(parent[x], parent)
    return parent[x]


def union(x, y, parent, rank):
    """
    Слияние двух деревьев.
    Нахождение корней двух точек и их БЕЗГРАНИЧНОЕ СЛИЯНИЕ (более низкое дерево сливается с более высоким).

    >>>union(1, 3, {1: 1, 2: 2, 3: 3, 4: 2, 5: 2}, {1: 0, 2: 1, 3: 0, 4: 0, 5: 0})
    ({1: 1, 2: 2, 3: 1, 4: 2, 5: 2}, {1: 1, 2: 1, 3: 0, 4: 0, 5: 0})
    >>>union(1, 4, {1: 1, 2: 4, 3: 1, 4: 4, 5: 4, 6: 4}, {1: 1, 2: 0, 3: 0, 4: 1, 5: 0, 6: 0})
    ({1: 1, 2: 4, 3: 1, 4: 1, 5: 4, 6: 4}, {1: 2, 2: 0, 3: 0, 4: 1, 5: 0, 6: 0})

    :param x: Первая вершина графа, x > 0
    :type x: int
    :param y: Вторая вершина графа, y > 0
    :type x: y: int
    :param parent: Словарь, который содержит пути к корню для разных точек.
    :type parent:dict
    :param rank: Словарь, заключающий в себя количество предков графа для каждой точки.
    :type rank: dict
    :return: None
    """
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
    """
    Алгоритм Краскала.
    Нахождение минимального остовного дерева последовательным присоединением веток с минимальным весом до образования
    цикла. В случае цикла исключается ветка с наибольшим весом. Повторение до того, как все вершины соединены.

    Оценка сложности: O(E * log(E))
    >>>kruskal{(2, 5): 1, (4, 5): 2, (1, 3): 3, (1, 2): 6, (2, 4): 7, (3, 4): 8}
    {(2, 5): 1, (4, 5): 2, (1, 3): 3, (1, 2): 6}
    >>>kruskal{(2, 3): 1, (4, 6): 1, (1, 6): 2, (3, 6): 2, (4, 5): 2, (2, 6): 3, (1, 2): 4, (2, 4): 5, (6, 7): 5, (1, 5): 6,
    ...(3, 7): 6, (4, 7): 9}
    {(2, 3): 1, (4, 6): 1, (1, 6): 2, (3, 6): 2, (4, 5): 2, (6, 7): 5}
    >>>kruskal{(2, 3): 1, (1, 4): 2, (1, 2): 3, (3, 4): 3, (1, 3): 4, (2, 4): 5}
    {(2, 3): 1, (1, 4): 2, (1, 2): 3}
    :param g: Отсортированный по возрастанию веса веток граф
    :type g: dict
    :return: Минимальное остовное дерево: dict
    """
    if not isinstance(g, dict):
        raise ValueError('Неправильный тип графа (должен быть словарь)')
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
    print(final)
    return final


def graph_view(graph_first, graph_final, top):
    """
    Визуализация графа
    Показ начального и измененного графа в одном файле расширения .png
    :param graph_first: начальный граф
    :type graph_first: dict
    :param graph_final: измененный алгоритмом граф
    :type graph_final: dict
    :param top: количество вершин графа
    :type top: int
    :return: None
    """
    if not isinstance(graph_first, dict) and isinstance(graph_final, dict):
        raise ValueError('Неправильный тип графа (должен быть словарь)')
    if not isinstance(top, int):
        raise ValueError('Неправильный тип количества вершин графа')

    show_it = graphviz.Graph(filename="Graph", format='png')

    verticle_lst = [i for i in range(1, top + 1)]  # Показ вершин графа
    for top in verticle_lst:
        show_it.node(str(top))

    for edge in graph_first:
        if edge in graph_final:
            show_it.edge(str(edge[0]), str(edge[1]), label=str(graph_final[edge]))  # Показ веток финального графа
        else:
            show_it.edge(str(edge[0]), str(edge[1]), label=str(graph_first[edge]),  # Показ веток начального графа
                         color="gray", fontcolor="gray")
    show_it.view()
