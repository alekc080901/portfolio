import graphviz
import os
import pickle


GRAPHVIZ_PATH = 'C:/Program Files (x86)/Graphviz2.38/'
os.environ["PATH"] += os.pathsep + GRAPHVIZ_PATH + 'bin/'
graph_image = graphviz.Digraph(filename="Graph", format='png', strict=True)


class BinaryTree:
    def __init__(self, info=None):
        self.left = None
        self.right = None
        self.info = info

    @staticmethod
    def traversal(cur_node):
        graph_image.node(str(cur_node.info))

        if cur_node.left is not None:
            graph_image.edge(str(cur_node.info), str(cur_node.left.info))
            cur_node.traversal(cur_node.left)

        if cur_node.right is not None:
            graph_image.edge(str(cur_node.info), str(cur_node.right.info))
            cur_node.traversal(cur_node.right)

    def show(self):
        graph_image.clear()
        self.traversal(self)
        graph_image.view()

    def insert(self, info):
        if not self.info:
            self.info = info
            return

        if self.info == info:
            return

        if info < self.info:
            if self.left:
                self.left.insert(info)
                return
            self.left = BinaryTree(info)
            return

        if self.right:
            self.right.insert(info)
            return

        self.right = BinaryTree(info)

    def get_left(self):
        current = self
        while current.left is not None:
            current = current.left

        return current.info

    def get_right(self):
        current = self
        while current.right is not None:
            current = current.right

        return current.info

    def delete(self, info):
        if self is None:
            return self

        if info < self.info:
            if self.left:
                self.left = self.left.delete(info)
            return self

        if info > self.info:
            if self.right:
                self.right = self.right.delete(info)
            return self

        if self.right is None:
            return self.left

        if self.left is None:
            return self.right

        min_larger_node = self.right
        while min_larger_node.left:
            min_larger_node = min_larger_node.left
        self.info = min_larger_node.info
        self.right = self.right.delete(min_larger_node.info)

        return self

    def _find_min(self, parent):
        if self.left:
            return self.left._find_min(self)
        else:
            return [parent, self]

    def has(self, val):
        if val == self.info:
            return True

        if val < self.info:
            if self.left is None:
                return False
            return self.left.has(val)

        if self.right is None:
            return False

        return self.right.has(val)

    def save(self, path):
        with open(path, 'wb') as bt:
            pickle.dump(self, bt)


def read_tree(path):
    with open(path, 'rb') as bt:
        return pickle.load(bt)


def main():
    bt = BinaryTree()
    bt.insert(4)
    bt.insert(3)
    bt.insert(8)
    bt.insert(10)
    bt.insert(2)
    bt.insert(7)
    bt.insert(5)
    bt.insert(9)

    print('Левый элемент:', bt.get_left())
    print('Правый элемент:', bt.get_right())
    print('Элемент 6 есть в дереве') if bt.has(6) else print('Элемента 6 нет в дереве')

    bt.save("bt")
    read_tree("bt").show()
    # bt.delete(7).show()


if __name__ == '__main__':
    main()
