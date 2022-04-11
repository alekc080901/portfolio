from xml.etree import ElementTree as etree
from xml.etree.ElementTree import Element
import pymongo
from wiki_parser import delete_trash

client = pymongo.MongoClient("mongodb://127.0.0.1:27017")
database = client.wiki
articles_db: pymongo.collection.Collection = database.articles


def check_title(title: str):
    if title.lower().startswith('категория') or title.lower().startswith('шаблон')\
            or title.lower().startswith('файл') or title.lower().startswith('проект')\
            or title.lower().startswith('mediawiki') or title.lower().startswith('портал')\
            or title.lower().startswith('википедия'):
        return False
    return True


def write_xml_to_db(path: str):
    title = None
    content = None
    for event, elem in etree.iterparse(path):
        elem: Element = elem
        if elem.tag == '{http://www.mediawiki.org/xml/export-0.10/}title' and elem.text is not None:
            title = elem.text
        if elem.tag == '{http://www.mediawiki.org/xml/export-0.10/}text' and elem.text is not None:
            try:
                content = delete_trash(elem.text)
            except Exception as e:
                continue

        if title and content and check_title(title):
            print(title)
            articles_db.update_one({'title': title}, {'$set': {'content': content}}, upsert=True)
            title = None
            content = None


if __name__ == '__main__':
    write_xml_to_db('wiki-articles3.xml')
