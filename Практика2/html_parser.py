from urllib.request import urlopen
from bs4 import BeautifulSoup, Comment, Tag
import re


def get_html():
    """
    Получает HTML-документ Википедии
    :return: HTML-текст формата utf-8
    """
    with urlopen('https://ru.wikipedia.org/wiki/%D0%A1%D0%BB%D1%83%D0%B6%D0%B5%D0%B1%D0%BD%D0%B0%D1%8F:%D0%A1%D0%BB%D1%83%D1%87%D0%B0%D0%B9%D0%BD%D0%B0%D1%8F_%D1%81%D1%82%D1%80%D0%B0%D0%BD%D0%B8%D1%86%D0%B0') as fp:
        bytes_html = fp.read()
        raw_html = bytes_html.decode('utf8')
    return raw_html


def check_h3(soup: BeautifulSoup):
    """
    Проверяет, есть ил в статье вложенные заголовки
    :param soup: HTML-текст
    :return: True или False
    """
    content = soup.find("div", class_="mw-parser-output")
    if content.find("h3"):
        return True
    return False


def delete_trash(soup: BeautifulSoup):
    """
    Оставляет только необходимую информацию в html-документе сайта Wikipedia
    :param soup: необработанный HTML-документ Wikipedia
    :return: обработанный HTML-документ с содержанием статьи и заголовками Wikipedia
    """
    content = soup.find("div", class_="mw-parser-output")

    tags_with_info = re.findall('<.*>', str(content))
    short_tags_list = set([full_tag.replace('<', '').replace('>', ' ').replace('/', '').split(' ')[0]
                           for full_tag in tags_with_info])
    useless_tags = short_tags_list - {'p', 'h2', 'span', 'i', 'a', 'b'}

    # Костыль для удаления тега стиля, который иногда проскакивает
    for elem in content.findAll("style"):
        elem.decompose()

    # Избавление от поля [править | править код] у заголовков
    for elem in content.findAll("span", class_='mw-editsection'):
        elem.decompose()

    # Удаление тего и содержимого тегов ненужных для анализа данных
    for tag in useless_tags:
        for elem in content.findAll(tag):
            elem.decompose()

    # Удаление костылей Википедии в заголовках
    for header in content.findAll("h2"):
        header.span.unwrap()
        header.span.unwrap()

    # Удаление комментариев в HTML-коде
    for child in content.children:
        if isinstance(child, Comment):
            child.extract()

    return content


def correct_text(wiki_text: str):
    """
    Исправляет неточности текста, связанных с парсингом HTML-документа
    :param wiki_text: параграф текста Википедии
    :return: исправленный текст
    """
    wiki_text = wiki_text.replace(u'\xa0', u' ')
    wiki_text = re.sub(r'\[\d]', '', wiki_text)
    return wiki_text


def delete_tags(html_text: str):
    """
    Удаляет все теги в HTML-тексте
    :param html_text: HTML-текст с тегами
    :return: простой текст без HTML-тегов
    """
    return re.sub('<.*?>', '', html_text)


def delete_points(string: str):
    return string.replace('.', '')


def separate(content: Tag):
    """
    Разделяет HTML-текст с заголовками и параграфами на заголовки и параграфы, а затем формирует их в словарь
    :param content: HTML-текст для преобразования
    :return: словарь типа {Заголовок: Содержание заголовка, ...}
    """
    headers = ["Базовое описание"] + list(map(lambda x: x.get_text(), content.findAll("h2")))
    headers = list(map(delete_points, headers))
    tagged_headers = list(map(lambda h: f'<h2>{h}</h2>', headers))

    tagged_paragraphs = re.split('|'.join(map(re.escape, tagged_headers)), correct_text(str(content)))
    paragraphs = list(map(delete_tags, tagged_paragraphs))
    paragraphs = list(map(lambda x: x.strip('\n'), paragraphs))

    text_with_headers = {}
    for header, paragraph in zip(headers, paragraphs):
        text_with_headers[header] = paragraph

    return text_with_headers


def form_row():
    """
    Формирует строчку для записи в базу данных с информацией страници Википедии заданого названия
    :param title: Название статьи
    :return: словарь типа {Название статьи: Название, Заголовок1: Содержание заголовка1, ...}
    """
    wiki_content = get_html()
    wiki_soup = BeautifulSoup(wiki_content, "html.parser")
    if check_h3(wiki_soup):
        return None

    wiki_content = delete_trash(wiki_soup)
    wiki_article = {"Заголовок статьи": wiki_soup.find("h1").get_text()}
    wiki_article.update(separate(wiki_content))
    return wiki_article


if __name__ == '__main__':
    print(form_row())
