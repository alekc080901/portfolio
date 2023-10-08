import cv2
import numpy as np

from fastapi import FastAPI, Request
from fastapi.middleware.cors import CORSMiddleware
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
from fastapi.responses import FileResponse

from server.image import pixelate, resize_image, adjust_image, fix_image_palette, adjust_shape, Shape
from server.const import DEFAULT_BLOCK, ORIENTATIONS, ALGORITHMS, STATIC_FILES_DIRECTORY, WEAVINGS

app = FastAPI()

origins = ['*']

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=['*'],
    allow_headers=['*'],
)

app.mount('/static', StaticFiles(directory=STATIC_FILES_DIRECTORY), name='static')
templates = Jinja2Templates(directory='templates')


async def read_image_from_form(image_from_form):
    raw = await image_from_form.read()
    arr = np.asarray(bytearray(raw), dtype=np.uint8)
    img = cv2.imdecode(arr, -1)
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGBA)
    return img


async def parse_image_form(form):
    return {
        'img': await read_image_from_form(form.get('img')),
        'coefficient': float(form.get('bead_coefficient')),
        'palette_arr': np.array([color.split(',') for color in form.getlist('palette_arr')], dtype=int)
    }


@app.get('/')
async def index(request: Request):
    return templates.TemplateResponse('home.html', {'request': request})


@app.post('/')
async def process_image(request: Request):
    form_data = await parse_image_form(await request.form())

    block_size = Shape(int(DEFAULT_BLOCK.width * form_data['coefficient']),
                       int(DEFAULT_BLOCK.height * form_data['coefficient']))

    image = form_data['img']
    palette = form_data['palette_arr']

    image = resize_image(image)
    fixed_image = fix_image_palette(image, palette)

    processed_images = {}
    for orientation in ORIENTATIONS:
        adjust_shape(block_size, orientation=orientation)

        processed_images[orientation] = {}

        for weaving in WEAVINGS:
            processed_images[orientation][weaving] = {}

            fixed_oriented = adjust_image(fixed_image, block_size, orientation=orientation, weaving=weaving)

            for algorithm in ALGORITHMS:
                processed_images[orientation][weaving][algorithm] = {}

                processed_images[orientation][weaving][algorithm] = pixelate(fixed_oriented, palette, block_size,
                                                                             algorithm=algorithm,
                                                                             orientation=orientation,
                                                                             weaving=weaving,
                                                                             save_as='blocks').tolist()

    return {
        'error': False,
        'schemes': processed_images,
    }


@app.get('/favicon.ico')
async def index(request: Request):
    return FileResponse(f'{STATIC_FILES_DIRECTORY}/img/favicon.ico')
