import cv2
import numpy as np
from PIL import Image, ImageDraw

from server.const import DEFAULT_WIDTH, DEFAULT_HEIGHT, Shape, ORIENTATIONS, WEAVINGS, ALGORITHMS


def adjust_shape(shape, orientation):
    if orientation == 'vertical':
        shape.width, shape.height = \
            min(shape.width, shape.height), max(shape.width, shape.height)
    elif orientation == 'horizontal':
        shape.width, shape.height = \
            max(shape.width, shape.height), min(shape.width, shape.height)


def adjust_image(image, block_shape, orientation='vertical', weaving='alternate'):
    assert orientation in ORIENTATIONS
    assert weaving in WEAVINGS

    row_indent = block_shape.width // 2 if weaving == 'alternate' and orientation == 'horizontal' else 0
    col_indent = block_shape.height // 2 if weaving == 'alternate' and orientation == 'vertical' else 0

    old_shape = image.shape[:2]

    # Исправляем размер изображения для соответствия количества блоков
    fix_shape = (old_shape[1] - old_shape[1] % block_shape.width + row_indent,
                 old_shape[0] - old_shape[0] % block_shape.height + col_indent)

    return cv2.resize(image, fix_shape, interpolation=cv2.INTER_NEAREST)


def resize_image(image):
    old_shape = image.shape[:2]

    width_ratio = DEFAULT_WIDTH / old_shape[1]
    height_ratio = DEFAULT_HEIGHT / old_shape[0]

    resize_shape = (DEFAULT_WIDTH, int(old_shape[0] * width_ratio)) if old_shape[1] > old_shape[0] else \
        (int(old_shape[1] * height_ratio), DEFAULT_HEIGHT)

    return cv2.resize(image, resize_shape)


def get_average_colour(block):
    return np.array(block.mean(axis=0).mean(axis=0), dtype=int)


def get_dominant_colour(block):
    block = block.reshape(-1, block.shape[2])
    colors, counts = np.unique(block, return_counts=True, axis=0)
    return colors[np.argmax(counts)]


def nearest_colour(subject_color, palette):
    return min(
        palette,
        key=lambda subject: sum((s - q) ** 2 for s, q in zip(subject, subject_color))
    )[:len(subject_color)]


def fix_image_palette(image, palette):
    for i in range(len(image)):
        for j in range(len(image[i])):
            pixel = image[i][j]
            if len(pixel) == 4 and pixel[3] == 0:  # Dealing with transparent pixels
                image[i][j] = (0, 0, 0, 0)
            else:
                pixel[3] = 255
                image[i][j] = nearest_colour(pixel, palette)
    return image


def frames(image, block_shape, orientation='vertical'):
    image_width = image.shape[1]
    image_height = image.shape[0]

    row_indent = block_shape.width // 2 if orientation == 'horizontal' else 0
    col_indent = block_shape.height // 2 if orientation == 'vertical' else 0

    im = Image.fromarray(image)
    draw = ImageDraw.Draw(im)

    previous_even = False
    image_bound1 = image_width if 'vertical' else image_height
    image_step1 = block_shape.width if 'vertical' else block_shape.height
    for j, row_idx in enumerate(range(0, image_bound1, image_step1)):

        image_bound2 = image_height - col_indent if 'vertical' else image_width - row_indent
        image_step2 = block_shape.height if 'vertical' else block_shape.width

        start_indent_col = col_indent if 'vertical' and previous_even else 0
        start_indent_row = col_indent if 'horizontal' and previous_even else 0

        for i, col_idx in enumerate(range(0, image_bound2, image_step2)):
            draw.rectangle((row_idx + start_indent_row, col_idx + start_indent_col,
                            row_idx + block_shape.width + start_indent_row,
                            col_idx + block_shape.height + start_indent_col), outline=(0, 0, 0))

        previous_even = j % 2 == 0
    im.show()


def pixelate(image, palette, block_shape, orientation='vertical', weaving='alternate',
             algorithm='max', save_as='image'):
    assert algorithm in ALGORITHMS
    assert weaving in WEAVINGS
    assert orientation in ORIENTATIONS
    assert save_as in ('image', 'blocks')

    row_indent = block_shape.width // 2 if weaving == 'alternate' and orientation == 'horizontal' else 0
    col_indent = block_shape.height // 2 if weaving == 'alternate' and orientation == 'vertical' else 0

    color_func = get_dominant_colour if algorithm == 'max' else get_average_colour

    image_width = image.shape[1]
    image_height = image.shape[0]
    image_channels = image.shape[2]

    blocks_in_row = image_width // block_shape.width
    blocks_in_col = image_height // block_shape.height

    if orientation == 'vertical':
        blocks = np.empty((blocks_in_row, blocks_in_col, image_channels), dtype=int)
    else:
        blocks = np.empty((blocks_in_col, blocks_in_row, image_channels), dtype=int)

    previous_even = False
    image_bound1 = image_width if orientation == 'vertical' else image_height
    image_step1 = block_shape.width if orientation == 'vertical' else block_shape.height
    for j, row_idx in enumerate(range(0, image_bound1, image_step1)):

        image_bound2 = image_height - col_indent if orientation == 'vertical' else image_width - row_indent
        image_step2 = block_shape.height if orientation == 'vertical' else block_shape.width

        start_indent_col = col_indent if orientation == 'vertical' and previous_even else 0
        start_indent_row = row_indent if orientation == 'horizontal' and previous_even else 0

        for i, col_idx in enumerate(range(0, image_bound2, image_step2)):

            if orientation == 'vertical':
                image_block = image[col_idx + start_indent_col:col_idx + block_shape.height + start_indent_col,
                              row_idx + start_indent_row:row_idx + block_shape.width + start_indent_row]
            else:
                image_block = image[row_idx + start_indent_col:row_idx + block_shape.height + start_indent_col,
                              col_idx + start_indent_row:col_idx + block_shape.width + start_indent_row]

            image_block_color = color_func(image_block)
            if algorithm == 'average':
                image_block_color = nearest_colour(image_block_color, palette)

            if save_as == 'image':

                if orientation == 'vertical':
                    image[col_idx + start_indent_col:col_idx + block_shape.height + start_indent_col,
                    row_idx + start_indent_row:row_idx + block_shape.width + start_indent_row] = image_block_color
                else:
                    image[row_idx + start_indent_col:row_idx + block_shape.height + start_indent_col,
                    col_idx + start_indent_row:col_idx + block_shape.width + start_indent_row] = image_block_color

            elif save_as == 'blocks':
                blocks[j][i] = image_block_color

        previous_even = j % 2 == 0
    return image if save_as == 'image' else blocks if save_as == 'blocks' else None


def main():
    block_shape = Shape(width=8, height=12)
    adjust_shape(block_shape, orientation='horizontal')

    image = cv2.imread('../glasses-trans.png', flags=cv2.IMREAD_UNCHANGED)
    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGBA)
    palette = (
        [0, 0, 0, 0],
        [255, 255, 255, 0],
        [0, 0, 0, 255],
        [255, 255, 255, 255],
        [192, 192, 192, 255],
        [128, 128, 128, 255],
        [255, 0, 0, 255],
        [128, 0, 0, 255],
        [255, 255, 0, 255],
        [128, 128, 0, 255],
        [0, 255, 0, 255],
        [0, 128, 0, 255],
        [0, 255, 255, 255],
        [0, 128, 128, 255],
        [0, 0, 255, 255],
        [0, 0, 128, 255],
        [255, 0, 255, 255],
        [128, 0, 12, 255]
    )

    image = resize_image(image)
    image = fix_image_palette(image, palette)
    image = adjust_image(image, block_shape, orientation='horizontal')

    image = pixelate(image, palette, block_shape, save_as='image', weaving='straight', orientation='horizontal',
                     algorithm="max")

    # print(np.unique(image, return_counts=True, ))

    # frames(image)
    # print(image)
    cv2.imshow('test', image[..., ::-1])
    cv2.waitKey(0)


if __name__ == '__main__':
    main()
