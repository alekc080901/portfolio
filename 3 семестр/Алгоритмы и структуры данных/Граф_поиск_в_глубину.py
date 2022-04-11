"""Поиск в глубину"""

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
            if int(number) <= 1:
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
            connections = []
        self.number = number
        self.connections = connections
        self.is_visited = False

    def connect(self, node):
        if not isinstance(node, Node):
            raise Exception("Подан не тот тип")

        self.connections.append(node)


class Graph:

    def __init__(self, nodes_lst=None):
        if nodes_lst is None:
            nodes_lst = []
        self.nodes = nodes_lst

        self.graph_image = graphviz.Digraph(filename="Graph", format='png', strict=True)
        self.count = 0

    def add_node(self, node):
        if not isinstance(node, Node):
            raise Exception("Подан не тот тип")

        self.nodes.append(node)
        self.graph_image.clear()
        self.form_image()

    def form_image(self):
        for source in self.nodes:
            for dest in source.connections:
                self.graph_image.edge(str(source.number), str(dest.number), color="gray")

    def depth_first(self, source_node=None):
        if not self.nodes:
            print("Вершины графа не заполнены!")
            return

        if source_node is None:
            source_node = self.nodes[0]

        if source_node not in self.nodes:
            print("Вершины", source_node, "в графе нет!")
            return

        source_node.is_visited = True
        for dest_node in source_node.connections:
            if dest_node.is_visited:
                continue

            self.count += 1
            self.graph_image.edge(str(source_node.number), str(dest_node.number), label=str(self.count), color="red")

            self.depth_first(dest_node)

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

            if all([conn > node_amount or conn == i + 1 for conn in node_connections]) and node_connections != []:
                print("Введите корректные вершины!")
                continue

            for conn in node_connections:
                cur_node.connect(nodes[conn-1])

            break
        graph.add_node(cur_node)
        node_number += 1

    return graph


def main():
    graph = graph_create()
    graph.depth_first()
    graph.show()


if __name__ == '__main__':
    main()

