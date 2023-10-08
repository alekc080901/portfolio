class Shape:
    def __init__(self, width, height):
        self.width = width
        self.height = height

    def __str__(self):
        return f'({self.width}, {self.height})'


STATIC_FILES_DIRECTORY = 'static'


DEFAULT_WIDTH = 400
DEFAULT_HEIGHT = 400

DEFAULT_BLOCK = Shape(width=8, height=12)
ORIENTATIONS = ('vertical', 'horizontal')
WEAVINGS = ('straight', 'alternate')
ALGORITHMS = ('max', 'average')
