"""икитин Александр, КИ19-17/1Б, работа с совпадениями в двух текстах"""

text1 = open('Text1.txt')
text2 = open('Text2.txt')
t1 = text1.read()
t2 = text2.read()
text1.close()
text2.close()
sym = ('~', '!', '@', '#', '$', '%', '^', '&', '*', '_', '+', '=', '|', '{', '}', '(', ')', '[', ']', ':',
       ';', '"', '<', '>', ',', '.', '?', '/')    # Кортеж с символами для исключения

# Превращение текста в набор слов
for i in sym:
    t1 = t1.replace(i, '')
    t2 = t2.replace(i, '')
t1 = t1.lower()
t1 = t1.split()
t2 = t2.lower()
t2 = t2.split()
s1 = set(t1)
s2 = set(t2)
match1 = 0
match2 = 0

# Подсчет одинаковых слов
for i in t1:
    if t1.count(i) > 1:
        match1 += 1
for i in t2:
    if t2.count(i) > 1:
        match2 += 1

print('Пункт А, текст 1:', match1, '\nПункт А, текст 2:', match2, '\nПункт Б:', len(s1 | s2))
print('Пункт В:', len(s1)+len(s2), '\nПункт Г:', (s1 ^ s2))
print('Пункт Д, текст 1:', (s1 - s2), '\nПункт Д, текст 2:', (s2 - s1))
