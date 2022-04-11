import pymongo
import os

client = pymongo.MongoClient(
    "mongodb+srv://JoJo_Heaven:tetriandoh@coderoyal-ahqiz.mongodb.net/test?retryWrites=true&w=majority")

if os.environ.get('ENVIRONMENT', 'production') == 'test':
    database = client[os.environ.get('DB_NAME')]
else:
    database = client.coderoyale

users: pymongo.collection.Collection = database.users
users_code: pymongo.collection.Collection = database.usercoderecords
tournament_users: pymongo.collection.Collection = database.tournamentusers
tournament_db: pymongo.collection.Collection = database.tournaments
