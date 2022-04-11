import re
import pymongo

# Подключение к базе данных
client = pymongo.MongoClient("mongodb://127.0.0.1:27017")
database = client.wiki
articles_db: pymongo.collection.Collection = database.articles


def delete_tables(text: str):
    """
    Удаляет все таблицы из статьи
    :param text: вики-разметка с таблицами
    :return: вики-разметка без таблиц
    """
    text = text.replace('\n |', '\n|')

    # Таблицы формата {| ... |}
    while (start_index := text.find('{|')) != -1:
        end_index = text[start_index:].find('|}') + start_index + 2
        text = text.replace(text[start_index:end_index + 1], '')

    # Таблицы формата {{Категория | ... | ... }}
    cur_pos = 0
    max_iter_number = 0
    while (start_index := text[cur_pos:].find('{{')) != -1:

        # Экстренное прекращение, если поиск зациклился
        if max_iter_number > 5000:
            break
        max_iter_number += 1

        if text[start_index + cur_pos:].find('\n|') != -1 and \
                text[start_index + cur_pos:].find('\n|') < text[start_index + cur_pos:].find('}}'):
            rows = text[start_index + cur_pos:].split('\n')
            end_index = start_index
            for i, row in enumerate(rows):
                if len(rows) == i + 1 and row.endswith('}}'):
                    end_index += len(row) + 1
                    break

                if row.startswith('|') and not rows[i + 1].startswith('|') and not rows[i + 1].startswith('*'):
                    if rows[i + 1].startswith('}}'):
                        end_index += len(row) + 5
                        break
                    elif row.endswith('}}'):
                        end_index += len(row) + 1
                        break
                    else:
                        return None
                end_index += len(row) + 1

            text = text.replace(text[start_index + cur_pos:end_index + cur_pos + 1], '')
        else:
            cur_pos += text[start_index + cur_pos:].find('}}') + start_index

    return text


def delete_title(title: str, text: str):
    """
    Удаляет заголовок вместе с содержанием внутри его
    :param title: название заголовка
    :param text: вики-разметка с ненужным заголовком
    :return: вики-разметка без заголовка
    """

    # Ссылки всегда идет последними, так что текст после них обрезается
    if title == 'Ссылки':
        text = text[:text.find('== Ссылки ==')]

    required_title = None
    for source_title in re.finditer(r'== (.*?) ==', text):
        if required_title is not None:
            text = text.replace(text[required_title.start(): source_title.start()], '')

            required_title = None

        if source_title.group().strip('= ') == title:
            required_title = source_title

    return text


def delete_links(text: str):
    """
    Удаляет все гиперссылки в тексте
    :param text: вики-разметка с гиперссылками
    :return: вики-разметка без гиперссылок
    """
    while (url := re.search(r'http(?:s)?://\S+', text)) \
            is not None:
        text = text.replace(text[url.start(): url.end() + 1], '')

    return text


def delete_files(text: str):
    """
    Удаляет все элементы с файлами в тексте
    :param text: вики-разметка с файлами
    :return: вики-разметка без файлов
    """
    return re.sub(r'\[\[([фФ]айл|[fF]ile).*\]\]', '', text)


def delete_empty_titles(text: str):
    """
    Удаляет все заголовки, содержимое которого по тем или иным причинам было удалено, т.е. пустые заголовки
    :param text: вики-разметка с пустыми заголовкам
    :return: вики-разметка без пустых заголовков
    """

    text_tmp = re.sub(r'\n{2,}', '\n', text)

    # Удаление "заголовков заголовка"
    for subtitle in re.finditer(r'; [А-Я].*', text_tmp):
        if text_tmp.endswith(subtitle.group()) or text_tmp[subtitle.end() + 1] in (';', '='):
            text = text.replace(subtitle.group(), '')

    # Удаление заголовков 3 уровня
    for subtitle in re.finditer(r'==== (.*?) ====', text_tmp):
        if text_tmp.endswith(subtitle.group()) or text_tmp[subtitle.end() + 1:subtitle.end() + 3] == '==':
            text = text.replace(subtitle.group(), '')

    # Удаление заголовков 2 уровня
    for subtitle in re.finditer(r'=== (.*?) ===', text_tmp):
        if text_tmp.endswith(subtitle.group()) or text_tmp[subtitle.end() + 1:subtitle.end() + 3] == '==':
            text = text.replace(subtitle.group(), '')

    # Удаление заголовков 1 уровня
    for title in re.finditer(r'== (.*?) ==', text_tmp):
        if text_tmp.endswith(title.group()) or text_tmp[title.end() + 1: title.end() + 3] == '==' and text_tmp[
            title.end() + 3] != '=':
            text = text.replace(title.group(), '')

    return text


def delete_trash(article_text: str):
    """
    Удаление ненужной информации в тексте вики-разметке
    :param article_text: вики-текст с "мусорной" информацией
    :return: вики-текст, готовый к обработке нейросетью
    """
    # Удаление перенаправлений и прочих "однострочных" статей
    if article_text.lower().startswith('#redirect') or article_text.lower().startswith('mediawiki') or \
            article_text.lower().startswith('#перенаправление') or article_text.lower().startswith('[[категория'):
        return None

    article_text = article_text.replace(u'\xa0', u' ')
    article_text = article_text.replace(u'\xd0', u' ')
    article_text = re.sub(r'<!--[\s\S]*?-->\n?', '', article_text)
    article_text = delete_tables(article_text)

    if article_text is None:
        return None

    article_text = re.sub(r'<ref(.*?)<\/ref>', '', article_text)
    article_text = re.sub(r'<ref(.*?)>', '', article_text)
    article_text = re.sub(r'<[^\/].*?>[\s\S]*?<\/.*?>', '', article_text)

    article_text = delete_title('Примечания', article_text)
    article_text = delete_title('Ссылки', article_text)

    article_text = delete_links(article_text)
    article_text = delete_files(article_text)

    article_text = re.sub(r'\{\{[дД]ругие значения\|.*\}\}', '', article_text)
    article_text = re.sub(r'\{\{[rR]edirect\|.*\}\}', '', article_text)
    article_text = re.sub(r'\{\{[пП]еренаправлени[ея]\|.*\}\}', '', article_text)
    article_text = re.sub(r'\{\{[гГ]лавная\|.*\}\}', '', article_text)
    article_text = re.sub(r'\{\{[оО]сновная статья\|.*\}\}', '', article_text)
    article_text = re.sub(r'\{\{[оО]сновная\|.*\}\}', '', article_text)
    article_text = re.sub(r'\{\{[mM]ain\|.*\}\}', '', article_text)
    article_text = re.sub(r'\{\{[тТ]акже\|.*\}\}', '', article_text)
    article_text = re.sub(r'\{\{[sS]ee also\|.*\}\}', '', article_text)
    article_text = re.sub(r'\{\{[яЯ]корь\|.*\}\}', '', article_text)
    article_text = re.sub(r'\{\{[зЗ]начения\|.*\}\}', '', article_text)
    article_text = re.sub(r'\{\{[сС]лушать\|.*\}\}', '', article_text)
    article_text = re.sub(r'\{\{[дД]ругие значения\|.*\}\}', '', article_text)

    article_text = article_text.strip('\n *')

    article_text = delete_empty_titles(article_text)

    article_text = re.sub(r'\n{3,}', '\n', article_text)

    return article_text
