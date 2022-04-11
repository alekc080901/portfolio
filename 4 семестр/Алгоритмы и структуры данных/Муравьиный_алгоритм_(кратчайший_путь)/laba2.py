import graphviz
import os
import random
import math
from functools import reduce

GRAPHVIZ_PATH = 'C:/Program Files (x86)/Graphviz2.38/'
os.environ["PATH"] += os.pathsep + GRAPHVIZ_PATH + 'bin/'


def get_last(lst: list):
    if len(lst) == 0:
        return None
    return lst[len(lst) - 1]


def input_int(name='', border=0):
    while True:
        number = input(name)
        try:
            int(number)
            if int(number) <= border:
                print('Число должно быть больше 1')
            else:
                number = int(number)
                break
        except ValueError:
            print('Неверный тип данных')
    return number


def get_connection(graph, node1, node2):
    for node in graph.nodes:
        for conn in node.connections:
            if conn.node1 == node1 and conn.node2 == node2 or conn.node2 == node1 and conn.node1 == node2:
                return conn


class Connection:

    def __init__(self, node1, node2, weight, pheromones):
        self.node1: Node = node1
        self.node2: Node = node2
        self.weight: int = weight
        self.pheromones: int = pheromones


class Node:

    def __init__(self, number):
        self.number: int = number
        self.connections = []

    def connect(self, dest, weight):
        if not isinstance(dest, Node):
            raise Exception("Подан не тот тип")

        if weight < 0:
            raise Exception("Подан отрицательный вес")

        tau0 = 5  # Изначальный уровень феромонов
        connection = Connection(self, dest, weight, tau0)
        self.connections.append(connection)
        dest.connections.append(connection)


class Graph:

    def __init__(self, nodes_lst=None):
        if nodes_lst is None:
            nodes_lst = []
        self.nodes: list = nodes_lst

        self.graph_image = graphviz.Graph(filename="Graph", format='png', strict=True)

    def add_node(self, node: Node):
        if not isinstance(node, Node):
            raise Exception("Подан не тот тип")

        self.nodes.append(node)
        self.graph_image.clear()
        self.form_image()

    def form_image(self):
        visited = []
        for source in self.nodes:
            for conn in source.connections:
                if conn.node2 in visited:
                    continue

                self.graph_image.node(str(conn.node1.number))
                visited.append(conn.node1)

        for source in self.nodes:
            for conn in source.connections:
                self.graph_image.edge(str(conn.node1.number), str(conn.node2.number), label=str(conn.weight),
                                      color="#B3B3B3")

    def show(self):
        # Подсчитываем общее количество феромонов
        sum_pheromones = 0
        for node in self.nodes:
            for conn in node.connections:
                sum_pheromones += conn.pheromones
        sum_pheromones /= 2

        for node in self.nodes:
            for conn in node.connections:
                red_tone_10 = 255 - round(255 * conn.pheromones / sum_pheromones)
                if red_tone_10 <= 40:
                    red_tone_10 = 40

                red_tone_16 = hex(red_tone_10)[2:].zfill(2).upper()

                self.graph_image.edge(str(conn.node2.number), str(conn.node1.number),
                                      label=str(conn.weight), color=f'#FF{red_tone_16}{red_tone_16}')

        self.graph_image.view()


class Ant:

    def __init__(self, graph: Graph, alpha=2, beta=1, k=5, evaporation_rate=0.1):
        self.graph = graph
        self.alpha = alpha
        self.beta = beta
        self.k = k
        self.evaporation = evaporation_rate
        self.path_nodes = []
        self.path_connections = []

    def walk(self):

        source_node = self.graph.nodes[0]
        dest_node = self.graph.nodes[-1]

        while source_node != dest_node:
            chances = {}
            for conn in source_node.connections:
                if conn.node1 != source_node and conn.node1 in self.path_nodes\
                        or conn.node2 != source_node and conn.node2 in self.path_nodes:
                    chances[conn] = 0.0
                    continue

                probability = ((conn.pheromones ** self.alpha) * (1 / conn.weight ** self.beta))
                chances[conn] = probability

            # Нормализация вероятностей
            chances = {conn: prob / sum(chances.values()) for conn, prob in chances.items()}

            # Выбор вершины из вероятностей
            chosen_conn = None
            ant_prob = random.random()
            sum_chances = 0.0
            for conn, chance in chances.items():
                sum_chances += chance
                if sum_chances >= ant_prob:
                    chosen_conn = conn
                    break

            assert chosen_conn

            self.path_nodes.append(source_node)
            self.path_connections.append(chosen_conn)
            source_node = chosen_conn.node2 if source_node != chosen_conn.node2 else chosen_conn.node1

        # Обновление феромонов
        weight = 0
        for conn in self.path_connections:
            weight += conn.weight

        for conn in self.path_connections:
            conn.pheromones += self.k / weight

        # Испарение
        for source_node in self.graph.nodes:
            for conn in source_node.connections:
                conn.pheromones *= math.sqrt(1 - self.evaporation)  # Квадрат, так как одна
                # связь итерируется дважды


def graph_create():
    graph = Graph()
    node_amount = input_int("Введите количество вершин графа\n", 1)
    nodes = []
    for i in range(node_amount):
        nodes.append(Node(i + 1))

    # Объявление вершин
    for i, cur_node in enumerate(nodes):
        # Связывание вершин
        while True:
            for node in range(node_amount):
                if node <= i:
                    continue

                weight = input_int(f"Введите вес между вершиной {i + 1} и {node + 1}\n")
                cur_node.connect(nodes[node], weight)

            break
        graph.add_node(cur_node)

    return graph


def main():
    graph = graph_create()

    for _ in range(10000):
        ant = Ant(graph)
        ant.walk()

    graph.show()


if __name__ == '__main__':
    main()
