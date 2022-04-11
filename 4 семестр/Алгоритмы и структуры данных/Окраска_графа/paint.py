import graphviz
import os
import random
import networkx as nx

GRAPHVIZ_PATH = 'C:/Program Files (x86)/Graphviz2.38/'
os.environ["PATH"] += os.pathsep + GRAPHVIZ_PATH + 'bin/'

COLORS = ('antiquewhite', 'aqua', 'aquamarine', 'azure', 'beige', 'bisque', 'blanchedalmond',
          'blue', 'blueviolet', 'brown', 'burlywood', 'cadetblue', 'chartreuse', 'chocolate', 'coral', 'cornflowerblue',
          'cornsilk', 'crimson', 'cyan', 'darkblue', 'darkcyan', 'darkgoldenrod', 'darkgreen',
          'darkkhaki', 'darkmagenta', 'darkolivegreen', 'darkorange', 'darkorchid', 'darkred', 'darksalmon',
          'darkseagreen', 'darkslateblue', 'darkslategray', 'darkslategrey', 'darkturquoise', 'darkviolet', 'deeppink',
          'deepskyblue', 'dimgray', 'dimgrey', 'dodgerblue', 'firebrick', 'floralwhite', 'forestgreen', 'fuchsia',
          'gainsboro', 'ghostwhite', 'gold', 'goldenrod', 'green', 'greenyellow', 'honeydew', 'hotpink',
          'indianred', 'indigo', 'khaki', 'lavender', 'lavenderblush', 'lawngreen', 'lemonchiffon',
          'lightblue', 'lightcoral', 'lightcyan', 'lightgoldenrodyellow', 'lightgray', 'lightgreen', 'lightgrey',
          'lightpink', 'lightsalmon', 'lightseagreen', 'lightskyblue', 'lightslategray', 'lightslategrey',
          'lightsteelblue', 'lightyellow', 'linen', 'magenta', 'maroon', 'mediumaquamarine',
          'mediumblue', 'mediumorchid', 'mediumpurple', 'mediumseagreen', 'mediumslateblue', 'mediumspringgreen',
          'mediumturquoise', 'mediumvioletred', 'midnightblue', 'mistyrose', 'moccasin', 'navajowhite',
          'navy', 'oldlace', 'olive', 'olivedrab', 'orange', 'orangered', 'orchid', 'palegoldenrod', 'palegreen',
          'paleturquoise', 'palevioletred', 'papayawhip', 'peachpuff', 'peru', 'pink', 'plum', 'powderblue', 'purple',
          'red', 'rosybrown', 'royalblue', 'saddlebrown', 'salmon', 'sandybrown', 'seagreen', 'seashell', 'sienna',
          'silver', 'skyblue', 'slateblue', 'slategray', 'slategrey', 'springgreen', 'steelblue', 'tan', 'teal',
          'thistle', 'tomato', 'turquoise', 'violet', 'wheat', 'yellow', 'yellowgreen')
COLORS_LEN = len(COLORS)


def dict2graph(graph_dict):
    nodes = [Node(i + 1) for i in range(len(graph_dict))]

    for node, connections in graph_dict.items():
        for adj_node in connections:
            nodes[node].connect(nodes[adj_node])

    return Graph(nodes)


def input_int(name='', restrict=1):
    while True:
        number = input(name)
        try:
            int(number)
            if int(number) < restrict:
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
        self.number: int = number
        self.connections: list = connections
        self.color: int = -1

    def connect(self, node):
        if not isinstance(node, Node):
            raise Exception("Подан не тот тип")

        self.connections.append(node)
        node.connections.append(self)


class Graph:

    def __init__(self, nodes_lst=None):
        if nodes_lst is None:
            nodes_lst = []
        self.nodes: list = nodes_lst

        self.graph_image = graphviz.Graph(filename="Graph", format='png', strict=True)
        self.form_image()

    def form_image(self):
        for node in self.nodes:
            self.graph_image.node(str(node.number), str(node.number))

        for source in self.nodes:
            for dest in source.connections:
                self.graph_image.edge(str(source.number), str(dest.number))

    def add_node(self, node):
        if not isinstance(node, Node):
            raise Exception("Подан не тот тип")

        self.nodes.append(node)

    def get_colors_amount(self):
        return max([node.color for node in self.nodes]) + 1

    def paint(self):
        node_degrees = {node: len(node.connections) for node in self.nodes}
        node_degrees_sorted = dict(sorted(node_degrees.items(), key=lambda elem: elem[1], reverse=True))

        color = 0
        while len(unmatched_nodes := [i for i in node_degrees_sorted if i.color == -1]) != 0:
            node = unmatched_nodes[0]
            node.color = color

            matched_nodes = [node]
            for unmatched_node in unmatched_nodes:
                if all(map(lambda matched_node: unmatched_node not in matched_node.connections, matched_nodes)):
                    unmatched_node.color = color
                    matched_nodes.append(unmatched_node)

            color += 1

        assert self.get_colors_amount() < COLORS_LEN, "Количество цветов превысило допустимый"

        colors = list(COLORS)
        random.shuffle(colors)
        for node in self.nodes:
            self.graph_image.node(str(node.number), str(node.number), style='filled', colorscheme="SVG",
                                  fillcolor=colors[node.color])

        for source in self.nodes:
            for dest in source.connections:
                self.graph_image.edge(str(source.number), str(dest.number))

        print('Количество цветов:', len(set(node.color for node in self.nodes)))

    def show(self):
        self.graph_image.view()


def graph_create():
    graph = Graph()
    node_amount = input_int("Введите количество вершин графа\n")
    nodes = []
    for i in range(node_amount):
        nodes.append(Node(i + 1))

    # Объявление вершин
    node_number = 0
    for i in range(node_amount):
        cur_node = nodes[i]
        # Связывание вершин
        while i != node_amount - 1:
            print("Перечислите через запятую вершины, с которыми связана вершина", node_number + 1)
            node_connections = input_several()

            if any([conn > node_amount or conn == node_number + 1 for conn in node_connections]) \
                    and node_connections != []:
                print("Введите корректные вершины!")
                continue

            for conn in node_connections:
                cur_node.connect(nodes[conn - 1])
            break
        graph.add_node(cur_node)
        node_number += 1

    return graph


def get_default_graph():
    n = [Node(i + 1) for i in range(20)]

    n[0].connect(n[1])
    n[0].connect(n[2])
    n[0].connect(n[5])
    n[0].connect(n[9])
    n[0].connect(n[19])
    n[1].connect(n[16])
    n[2].connect(n[11])
    n[3].connect(n[13])
    n[3].connect(n[14])
    n[4].connect(n[15])
    n[4].connect(n[7])
    n[5].connect(n[10])
    n[5].connect(n[8])
    n[6].connect(n[16])
    n[6].connect(n[13])
    n[7].connect(n[10])
    n[8].connect(n[11])
    n[9].connect(n[12])
    n[9].connect(n[17])
    n[11].connect(n[14])
    n[12].connect(n[18])
    n[12].connect(n[19])
    n[15].connect(n[19])
    n[16].connect(n[17])

    return Graph(n)


def main():
    graph = dict2graph(nx.to_dict_of_lists(nx.mycielski_graph(6)))
    # graph = get_default_graph()
    graph.paint()
    graph.show()


if __name__ == '__main__':
    main()
