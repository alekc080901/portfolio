import datetime
import hashlib
import os
import time

import jwt
import requests
from flask import Flask, jsonify, redirect, request
from flask_cors import CORS
from nanoid import generate
from werkzeug.security import gen_salt

from const import SECRET, MAILGUN_API_KEY, MAILGUN_MAIL, MAILGUN_DOMAIN, ALLOWED_EXTENSIONS, UPLOAD_FOLDER, \
    DEFAULT_RATE
from database import users, users_code, tournament_db, tournament_users
from decorators import use_validator, use_authorisation
from validators import login_validator, register_validator, change_info_validator, forgot_password_stage_one_validator, \
    change_password_stage_two_validator, tournament_validator_create, tournament_validator_finish

app = Flask(__name__)
CORS(app, resources={r"/api/*": {"origins": "*"}})
app.config['MAX_CONTENT_LENGTH'] = 16 * 1024 * 1024
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER


@app.route('/api/register', methods=["POST"])
@use_validator(register_validator)
def registration(data):
    if users.find_one({"username": data["username"]}) is not None:
        resp = jsonify(error=True, errno="username.duplicate")
        resp.status_code = 422
        return resp

    # Если почта уже существует
    if users.find_one({"email": data["email"]}):
        resp = jsonify(error=True, errno="email.occupied")
        resp.status_code = 422
        return resp

    # Уникальный путь к сайту для подтверждения регистрации
    register_id = generate(size=50)

    # Отправка письма с запросом на подтверждение на электронную почту
    response = requests.post(
        f"https://api.mailgun.net/v3/{MAILGUN_DOMAIN}/messages",
        auth=("api", MAILGUN_API_KEY),
        data={"from": f"Code Royale <{MAILGUN_MAIL}>",
              "to": f"{data['username']} <{data['email']}>",
              "subject": "Подтверждение почтового адреса",
              "text": "Здравствуйте!\n\n"
                      "Вы указали данный адрес электронной почты при прохождении регистрации на сайте Code Royale.\n"
                      "Для продолжения регистрации пройдите по ссылке:\n"
                      f"http://130.193.38.145/verify/{register_id}\n\n"
                      "Если письмо было отправлено к Вам по ошибке, просто игнорируйте его.\n\n"
                      "С уважением,\n"
                      "Команда разработчиков проекта Code Royal"})

    # Если почта не существует
    if response.status_code == 400:
        resp = jsonify(error=True, errno="email.not_exist")
        resp.status_code = 422
        return resp

    # Создание хэша пароля
    salt = gen_salt(20)
    salty_password = salt + data["password"]
    hashed_password = hashlib.sha256(bytes(salty_password, 'utf-8')).hexdigest()

    # Запись в базу данных
    users.insert_one({
        "username": data["username"],
        "email": data["email"],
        "personal": {
            "nickname": data.get("nickname", ""),
            "name": data.get("name", ""),
            "group": data.get("group", "")
        },
        "auth": {
            "verified": False,
            "salt": salt,
            "password": hashed_password,
            "verification": register_id,
        }
    })

    token = jwt.encode({
        "user": data["username"],
        "exp": datetime.datetime.utcnow() + datetime.timedelta(minutes=720)
    },
        SECRET, algorithm='HS256')

    # Даем пользователю зайти один раз до подтверждения email
    return jsonify(error=False, token=token.decode('ascii'))


@app.route('/verify/<code>', methods=["GET"])
def verify_email(code):
    # Костыль fixed
    result = users.update_one({
        "auth.verification": code
    }, {
        "$set": {
            "auth.verification": "",
            "auth.verified": True
        }
    })

    if result.modified_count == 1:  # данные о пользователе были действительно изменены
        return redirect("/?verified=1", code=307)

    return redirect("/?verified=0", code=307)  # пользователь не был найден, данные не поменялись


@app.route('/api/login', methods=["POST"])
@use_validator(login_validator)
def login(data):
    user = users.find_one({"username": data["username"]})

    if user is None:
        resp: Flask.response_class = jsonify(error=True, errno='username.wrong')
        resp.status_code = 422
        return resp

    password_hash = hashlib.sha256(bytes(user["auth"]["salt"] + data["password"], 'utf-8')).hexdigest()

    # Если пользоатель недопрошел регистрацию
    if not user["auth"]["verified"]:
        resp: Flask.response_class = jsonify(error=True, errno='account.not_verified')
        resp.status_code = 422
        return resp

    if user["auth"]["password"] != password_hash:
        resp: Flask.response_class = jsonify(error=True, errno='password.wrong')
        resp.status_code = 422
        return resp

    token = jwt.encode({
        'user': data["username"],
        'exp': datetime.datetime.utcnow() + datetime.timedelta(minutes=720)
    },
        SECRET, algorithm='HS256')
    return jsonify({"error": False, "token": token.decode('ascii')})


@app.route('/api/info/change', methods=["POST"])
@use_authorisation
@use_validator(change_info_validator)
def change_personal_info(username, data: dict):
    params = ["name", "group", "nickname", "status", "about_myself", "language"]

    if not data:
        resp: Flask.response_class = jsonify(error=True, errno='data.empty')
        resp.status_code = 422
        return resp

    result = users.update_one({
        "username": username
    }, {
        "$set": {
            f"personal.{key}": data.get(key, '') for key in params if data.get(key, None) is not None
        }
    })

    return jsonify(error=result.matched_count != 1)


@app.route('/api/forgot/request', methods=["POST"])
@use_validator(forgot_password_stage_one_validator)
def change_password_stage_one(data: dict):
    user = users.find_one({"email": data["email"]})  # TODO: check not to spam emails

    if user is None:
        resp: Flask.response_class = jsonify(error=True, errno='email.not_found')
        resp.status_code = 422
        return resp

    if not user['auth']['verified']:
        resp: Flask.response_class = jsonify(error=True, errno='account.not_verified')
        resp.status_code = 422
        return resp

    check_id = generate(size=6, alphabet="0123456789")

    # Отправка письма с запросом на изменение пароля на электронную почту
    requests.post(
        f"https://api.mailgun.net/v3/{MAILGUN_DOMAIN}/messages",
        auth=("api", MAILGUN_API_KEY),
        data={"from": f"Code Royale <{MAILGUN_MAIL}>",
              "to": f"{user['username']} <{user['email']}>",
              "subject": "Смена пароля",
              "text": "Здравствуйте!\n\n"
                      "Если вы получили это письмо, кто-то (надеемся, что вы) "
                      "пытается сменить пароль на сайте Code Royale.\n"
                      "Для изменения вашего пароля введите в поле подтвержения этот код:\n"
                      f"<h3>{check_id}</h3>\n\n"
                      "Если вы не запрашивали изменение пароля, просто игнорируйте это письмо.\n\n"
                      "С уважением,\n"
                      "Команда разработчиков проекта Code Royal"})

    users.update_one({
        "email": data["email"]
    }, {
        "$set": {
            "auth.verification": check_id  # TODO: include TTL
        }
    })

    return jsonify(error=False)


@app.route('/api/forgot/change', methods=["POST"])
@use_validator(change_password_stage_two_validator)
def change_password_stage_two(data):
    # Создание хэша пароля
    salt = gen_salt(20)
    salty_password = salt + data["password"]
    hashed_password = hashlib.sha256(bytes(salty_password, 'utf-8')).hexdigest()

    result = users.update_one({
        "email": data["email"],
        "auth.verification": data["code"]
    }, {
        "$set": {
            "auth.verification": '',
            "auth.password": hashed_password,
            "auth.salt": salt,
        }
    })

    resp: Flask.response_class = jsonify(error=result.modified_count != 1)
    resp.status_code = 200 if result.modified_count == 1 else 422
    return resp


@app.route('/api/admin/tournament', methods=["POST"])  # TODO: создать регистрацию на админа
@use_validator(tournament_validator_create)
def create_tournament(data):
    if not os.path.isfile(os.path.abspath(data["icon"])):
        resp: Flask.response_class = jsonify(error=True, errno='icon')
        resp.status_code = 422
        return resp

    # finishesAt не обязательно к заполнению, если "forever" = true
    if data.get("forever", False) is False and "finishesAt" not in data:
        resp: Flask.response_class = jsonify(error=True, errno='finishesAt')
        resp.status_code = 422
        return resp

    if "createdAt" not in data:
        data["createdAt"] = round(time.time())

    tournament_db.insert_one({
        "tid": gen_salt(16),
        "createdAt": data["createdAt"],
        "finishesAt": data["finishesAt"] if data.get("forever", False) is False else -1,
        "display": {
            "name": data["name"],
            "description": data["description"],
            "icon": data["icon"]
        }
    })

    return jsonify(error=False)


# Взял за основу твой код и модифицировал его
@app.route('/api/admin/tournament', methods=["PUT"])  # TODO: создать регистрацию на админа
@use_validator(tournament_validator_finish)
def set_time(data):
    display = {"name", "description", "icon"}

    if tournament_db.find_one({"tid": data["tid"]}) is None:
        resp: Flask.response_class = jsonify(error=True, errno='tid.wrong')
        resp.status_code = 422
        return resp

    if data.get("now") is True and data.get("forever") is True:
        resp: Flask.response_class = jsonify(error=True, errno='keys.both_true')
        resp.status_code = 422
        return resp

    # Делает бесконечным
    if data.get("forever"):
        data["finishesAt"] = -1
    # Завершает
    elif data.get("now"):
        data["finishesAt"] = round(time.time())

    if data.keys() and set(data.keys()) & display:
        tournament_db.update_one({
            "tid": data["tid"]
        }, {
            "$set": {
                f"display.{key}": data.get(key, '') for key in display if data.get(key, None) is not None
            }
        })

    if data.get("finishesAt", None) is not None:
        tournament_db.update_one(
            {
                "tid": data["tid"]
            }, {
                "$set": {
                    "finishesAt": data["finishesAt"]
                         }
            })
    return jsonify(error=False)


@app.route('/api/tournament/<tid>/solution', methods=["POST"])
@use_authorisation
def send_file(username, tid: str):
    file_code = request.files['file']
    if not file_code:
        resp: Flask.response_class = jsonify(error=True, errno='file')
        resp.status_code = 422
        return resp

    current_tournament = tournament_db.find_one({"tid": tid})
    if not current_tournament:
        resp: Flask.response_class = jsonify(error=True, errno='tid')
        resp.status_code = 422
        return resp

    if current_tournament["finishesAt"] != -1 and current_tournament["finishesAt"] > time.time():
        resp: Flask.response_class = jsonify(error=True, errno='tid.finished')
        resp.status_code = 422
        return resp

    if file_code.filename.count('.') != 1:
        resp: Flask.response_class = jsonify(error=True, errno='file.wrong_name')
        resp.status_code = 422
        return resp

    extension = file_code.filename.split('.', 1)[-1]
    extension = extension.replace('"', '')
    # Каким-то неведомым для меня образом, если название русское, в конце
    # расширения ставится кавычка

    if extension not in ALLOWED_EXTENSIONS:
        resp: Flask.response_class = jsonify(error=True, errno='filename.wrong_extension')
        resp.status_code = 422
        return resp

    file_hash = gen_salt(20)
    file_code.filename = f'{file_hash}.{extension}'
    file_code.save(os.path.join(app.config['UPLOAD_FOLDER'], file_code.filename))

    cid = gen_salt(20)
    users_code.insert_one({
        "cid": cid,
        "imagename": file_code.filename,
        "username": username,
        "tournament": tid,
        "createdAt": round(time.time())
    })

    repeated_user = users_code.find({"username": username, "tournament": tid}).sort("createdAt", 1)
    # В первый раз
    if repeated_user.count() == 1:
        tournament_users.insert_one({
            "uid": username,
            "code": cid,
            "tournament": tid,
            "rating": DEFAULT_RATE,
            "games": 0
        })
        return jsonify(error=False)

    # Если пользователь уже отправлял файл
    if repeated_user.count() == 8:  # 8, потому что после удаления останется 7
        path = os.path.join(os.path.abspath(UPLOAD_FOLDER), repeated_user[0]["imagename"])
        os.remove(path)  # Хоть ты и говорил не удалять, но я буду
        users_code.delete_one(repeated_user[0])

    tournament_users.update_one({"uid": username, "tournament": tid}, {"$set": {"code": cid}})

    return jsonify(error=False)


@app.route('/api/user/<username>/info', methods=["GET"])
def show_user(username):
    user = users.find_one({"username": username})

    if user is None:
        resp: Flask.response_class = jsonify(error=True, errno='username')
        resp.status_code = 404
        return resp

    return jsonify(user["personal"])


@app.route('/api/user/<username>/tournament_list', methods=["GET"])
def show_tournament_list(username):
    tl = list(tournament_users.aggregate([
        {
            '$match': {
                'uid': username
            }
        }, {
            '$group': {
                '_id': None,
                'tournaments': {
                    '$push': '$tournament'
                }
            }
        }
    ]))

    if len(tl) == 1:
        return jsonify(error=False, tournaments=tl[0]['tournaments'])

    return jsonify(error=False, tournaments=[])


@app.route('/api/code/find/<tid>', methods=["GET"])
@use_authorisation
def show_code_list(username, tid):
    documents = users_code.find({"username": username, "tournament": tid}).sort("createdAt", 1)

    code = []
    for doc in documents:
        code.append(doc['cid'])
    return jsonify(error=False, code=code)


@app.route('/api/code/activate/<cid>', methods=["POST"])
@use_authorisation
def change_cid(username, cid):
    code = users_code.find_one({"cid": cid})
    if code is None:
        resp: Flask.response_class = jsonify(error=True, errno='cid')
        resp.status_code = 404
        return resp

    tournament_users.update_one({
        "uid": username,
        "tournament": code['tournament']
    }, {
        "$set": {
            "code": cid
        }
    })

    return jsonify(error=False)


# Получение данных о турнире из бд
@app.route('/api/tournament/<tid>/info', methods=["GET"])
def show_tournament_info(tid):
    info = tournament_db.find_one({
        "tid": tid
    }, projection={
        "_id": False,
    })

    if info is None:
        resp: Flask.response_class = jsonify(error=True, errno='tid')
        resp.status_code = 404
        return resp

    return jsonify(info)


#  Статика
@app.route('/<filename>', methods=["GET"])
def static_file(filename):
    return app.send_static_file(filename)


@app.route('/', methods=["GET"])
def main_page():
    # Если название пустое, возвращает главную страницу. Удали, если я не прав
    return app.send_static_file('index.html')


if __name__ == '__main__':
    app.run(debug=False, port=os.environ.get('PORT', 5000))
