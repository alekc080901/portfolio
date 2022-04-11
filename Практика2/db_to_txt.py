import pymongo
import random

client = pymongo.MongoClient("mongodb://127.0.0.1:27017")
database = client.wiki
articles_db: pymongo.collection.Collection = database.articles

validation_rate = 0.1
success_rate = 0.2

with open('train.txt', 'w', encoding='utf-8') as train, open('valid.txt', 'w', encoding='utf-8') as valid:
    for article in articles_db.find({}):
        if random.random() > success_rate:
            continue
        if random.random() > validation_rate:
            train.write(article['content'] + '\n')
        else:
            valid.write(article['content'] + '\n')
