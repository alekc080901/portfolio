import json
import re
import pandas as pd


with open('encrypted_message.txt', 'r', encoding='utf-8') as file:
    SOURCE_MESSAGE = file.read()
    ENCRYPTED_MESSAGE = re.sub('[^А-Я]', '', SOURCE_MESSAGE)

with open('vigenere_table.json', 'r', encoding='utf-8') as file:
    VIGENERE_ARRAY = json.load(file)

RUSSIAN_SYMBOLS = list('АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ')

AFFINITY_INDEXES = pd.DataFrame(data={
    'min': (0.055, 0.0395, 0.0355, 0.035, 0.0335, 0.0325, 0.0315),
    'max': (0.0615, 0.055, 0.044, 0.0405, 0.039, 0.0385, 0.0365),
    'avg': (0.058, 0.046, 0.04, 0.0375, 0.036, 0.0352, 0.0345),
}, index=(1, 2, 3, 4, 5, 6, 7))

VIGENERE_TABLE = pd.DataFrame(data=VIGENERE_ARRAY, columns=RUSSIAN_SYMBOLS, index=RUSSIAN_SYMBOLS)

RUSSIAN_SYMBOLS_FREQUENCY = {'О': 0.10996, 'Е': 0.08483, 'А': 0.07998, 'И': 0.07367, 'Н': 0.067, 'Т': 0.06318,
                             'С': 0.05473, 'Р': 0.04746, 'В': 0.04533, 'Л': 0.04343, 'К': 0.03486, 'М': 0.03203,
                             'Д': 0.02977, 'П': 0.02804, 'У': 0.02615, 'Я': 0.02001, 'Ы': 0.01898, 'Ь': 0.01735,
                             'Г': 0.01687, 'З': 0.01641, 'Б': 0.01592, 'Ч': 0.0145, 'Й': 0.01208, 'Х': 0.00966,
                             'Ж': 0.0094, 'Ш': 0.00718, 'Ю': 0.00639, 'Ц': 0.00486, 'Щ': 0.00361, 'Э': 0.00331,
                             'Ф': 0.00267, 'Ъ': 0.00037}
