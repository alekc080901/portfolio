"""Алгоритм Дейкстры"""

import graphviz
import os


# Необходимо установить graphviz в данную директорию
GRAPHVIZ_PATH = 'C:/Program Files (x86)/Graphviz2.38/'
os.environ["PATH"] += os.pathsep + GRAPHVIZ_PATH + 'bin/'


def input_nat1(name=''):
    while True:
        number = input(name)
        try:
            int(number)
            if int(number) < 1:
                print('Число должно быть больше 1')
            else:
                number = int(number)
                break
        except ValueError:
            print('Неверный тип данных')
    return number


def input_several(sep=','):
    while True:
        data = input().replace(' ', '')
        if data == '':
            return []

        try:
            return list(map(int, data.split(",")))
        except ValueError:
            print(f"Введите данные корректно (используя '{sep}')!")


class Node:

    def __init__(self, number, connections=None):
        if connections is None:
            connections = {}
        self.number: int = number
        self.connections: dict = connections
        self.mark = float("inf")
        self.isVisited = False

    def connect(self, node, weight):
        if not isinstance(node, Node):
            raise Exception("Подан не тот тип")

        if weight < 0:
            raise Exception("Подан отрицательный вес")

        self.connections[node] = weight
        node.connections[self] = weight


class Graph:

    def __init__(self, nodes_lst=None):
        if nodes_lst is None:
            nodes_lst = []
        self.nodes: list = nodes_lst

        self.graph_image = graphviz.Graph(filename="Graph", format='png', strict=True)

    def add_node(self, node):
        if not isinstance(node, Node):
            raise Exception("Подан не тот тип")

        self.nodes.append(node)
        self.graph_image.clear()
        self.form_image()

    def form_image(self):
        for node in self.nodes:
            self.graph_image.node(str(node.number), f"{node.number}({node.mark})")

        for source in self.nodes:
            for dest in source.connections.keys():
                self.graph_image.edge(str(source.number), str(dest.number), label=str(source.connections[dest]),
                                      color="gray")

    def mark_path(self, source=None):
        if not self.nodes:
            print("Вершины графа не заполнены!")
            return

        if source is None:
            source = self.nodes[0]

        if source not in self.nodes:
            print("Вершины", source, "в графе нет!")
            return

        if source.mark == float("inf"):
            source.mark = 0

        visited_nodes = set()
        while True:
            source = min(set(self.nodes) - visited_nodes, key=lambda x: x.mark)
            visited_nodes.add(source)
            if len(visited_nodes) == len(self.nodes):
                break

            for dest in source.connections:
                if dest not in visited_nodes and source.mark + source.connections[dest] < dest.mark:
                    dest.mark = source.mark + source.connections[dest]

    def show_path(self):
        self.mark_path()

        for node in self.nodes:
            self.graph_image.node(str(node.number), f"{node.number}({node.mark})")
            print(f"Минимальный путь до вершины {node.number}: {node.mark}")

        node = self.nodes[-1]
        while node != self.nodes[0]:
            for prev_node in node.connections:
                if node.mark - node.connections[prev_node] == prev_node.mark:
                    self.graph_image.edge(str(prev_node.number), str(node.number),
                                          label=str(prev_node.connections[node]), color="red")
                    node = prev_node
                    break

    def show(self):
        self.graph_image.view()


def graph_create():
    graph = Graph()
    node_amount = input_nat1("Введите количество вершин графа\n")
    nodes = []
    for i in range(node_amount):
        nodes.append(Node(i + 1))

    # Объявление вершин
    node_number = 0
    for i in range(node_amount):
        cur_node = nodes[i]
        # Связывание вершин
        while True:
            print("Перечислите через запятую вершины, с которыми связана вершина", node_number + 1)
            node_connections = input_several()

            if any([conn > node_amount for conn in node_connections]) and node_connections != []:
                print("Введите корректные вершины!")
                continue

            for conn in node_connections:
                weight = input_nat1(f"Введите вес между вершиной {node_number+1} и {conn}\n")
                cur_node.connect(nodes[conn-1], weight)

            break
        graph.add_node(cur_node)
        node_number += 1

    return graph


def main():
    graph = graph_create()
    graph.show_path()
    graph.show()


if __name__ == '__main__':
    main()

