from functools import reduce
from io import BytesIO
import pytest
import os


from database import users, tournament_db, tournament_users, users_code
from const import UPLOAD_FOLDER
from main import app as application

global token
global tid


@pytest.fixture
def app():
    return application


def get_query_params(url):
    assert len(url.split('?')) == 2
    _, query = url.split('?')

    data = reduce(
        lambda acc, x: {**acc, x[0]: x[1]},
        map(lambda x: x.split('='), query.split('&')),
        {}
    )

    return data


# ФУНКЦИЯ РЕГИСТРАЦИИ


def test_register_true(client):
    # Case 1
    users.delete_many({})  # Обнуление базы данных
    users_code.delete_many({})
    tournament_users.delete_many({})

    data = {
        "username": "alekc080901",
        "password": "12345",
        "email": "alekc080901@mail.ru",
        "nickname": "HeLlO LoRd",
        "name": "Александр Никитин",
        "group": "Крови на рукаве"
    }

    response = client.post('/api/register', json=data)

    assert response.content_type == 'application/json'
    assert not response.json['error']

    # Case 2

    data = {
        "username": "Scatman",
        "password": "54321",
        "email": "alekc080901@ya.ru",
        "nickname": "Попробую русским",
        "name": "Try English",
        "group": "ABC123"
    }

    response = client.post('/api/register', json=data)

    assert response.content_type == 'application/json'
    assert not response.json['error']


# def test_register_missed_inessential_info(client):
#     users.delete_one({'email': 'alekc080901@ya.ru'})
#
#     data = {
#         "username": "Scatman",
#         "password": "54321",
#         "email": "alekc080901@ya.ru",
#     }
#
#     response = client.post('/api/register', json=data)
#
#     assert response.content_type == 'application/json'
#     assert not response.json['error']
#
#
# def test_register_empty_json(client):
#     users.delete_one({'email': 'alekc080901@ya.ru'})
#
#     data = {}
#
#     response = client.post('/api/register', json=data)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']
#     assert response.json['errno'] == ""
#
#
# def test_register_missed_email(client):
#     data = {
#         "username": "Scatman",
#         "password": "54321",
#     }
#
#     response = client.post('/api/register', json=data)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']
#     assert response.json['errno'] == ""
#
#
# def test_register_missed_password(client):
#     data = {
#         "username": "Scatman",
#         "email": "alekc080901@ya.ru",
#     }
#
#     response = client.post('/api/register', json=data)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']
#     assert response.json['errno'] == ""
#
#
# def test_register_missed_username(client):
#     data = {
#         "password": "12345",
#         "email": "alekc080901@ya.ru",
#     }
#
#     response = client.post('/api/register', json=data)
#
#     assert response.content_type == 'application/json'
#     if response.json['error']:
#         assert response.json['errno'] == ""
#
#
# def test_register_email_occupied(client):
#     data = {
#         "username": "user",
#         "password": "12345",
#         "email": "alekc080901@mail.ru",
#         "nickname": "HeLlO LoRd",
#         "name": "Александр Никитин",
#         "group": "Крови на рукаве"
#     }
#
#     response = client.post('/api/register', json=data)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']
#     assert response.json['errno'] == "email.occupied"
#
#
# def test_register_email_not_exist(client):
#     data = {
#         "username": "kekekekeke",
#         "password": "12345",
#         "email": "obviesly_nonexistent_mail@mail.ru",
#         "nickname": "HeLlO LoRd",
#         "name": "Александр Никитин",
#         "group": "Крови на рукаве"
#     }
#
#     response = client.post('/api/register', json=data)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']
#     assert response.json['errno'] == "email.not_exist"
#
#
# def test_register_username_occupied(client):
#     data = {
#         "username": "alekc080901",
#         "password": "12345",
#         "email": "alekc080901@ya.ru",
#         "nickname": "HeLlO LoRd",
#         "name": "Александр Никитин",
#         "group": "Крови на рукаве"
#     }
#
#     response = client.post('/api/register', json=data)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']
#     assert response.json['errno'] == "username.duplicate"
#
#
# # ФУНКЦИЯ ПРОВЕРКИ РЕГИСТРАЦИИ
#
def test_register_valid_true(client):
    user = users.find_one({'username': 'alekc080901'})

    response = client.get(f'/verify/{user["auth"]["verification"]}')

    # Если последний символ пути 1
    # Проверка не очень как-то (
    # Можно пропарсить параметры, я думаю
    # assert response.location[-1] == '1'
    data = get_query_params(response.location)

    assert data["verified"] == '1'
#
#
# def test_register_valid_false(client):
#     response = client.get('/verify/123456')
#
#     # Если последний символ пути 0
#     # assert response.location[-1] == '0'
#
#     data = get_query_params(response.location)
#
#     assert data["verified"] == '0'


# ФУНКЦИЯ АВТОРИЗАЦИИ


def test_login_true(client):
    data = {
        "username": "alekc080901",
        "password": "12345",
    }

    response = client.post('/api/login', json=data)

    assert response.content_type == 'application/json'
    assert not response.json['error']

    global token  # Не знаю, как обойтись без этой глобальной переменной
    token = response.json['token']


# def test_login_wrong_login(client):
#     data = {
#         "username": "kekekekeke",
#         "password": "12345",
#     }
#
#     response = client.post('/api/login', json=data)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']
#     assert response.json['errno'] == 'username.wrong'
#
#
# def test_login_wrong_password(client):
#     data = {
#         "username": "alekc080901",
#         "password": "1234567",
#     }
#
#     response = client.post('/api/login', json=data)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']
#     assert response.json['errno'] == 'password.wrong'
#
#
# def test_login_missed_login(client):
#     data = {
#         "password": "12345"
#     }
#
#     response = client.post('/api/login', json=data)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']
#     assert response.json['errno'] == ''
#
#
# def test_login_missed_password(client):
#     data = {
#         'username': "alekc080901",
#     }
#
#     response = client.post('/api/login', json=data)
#
#     assert response.content_type == 'application/json'
#     if response.json['error']:
#         assert response.json['errno'] == ''
#
#
# def test_login_empty_json(client):
#     data = {}
#
#     response = client.post('/api/login', json=data)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']
#     assert response.json['errno'] == ''
#
#
# def test_registration_unfinished(client):
#     # Зарегистрируем аккаунт
#     data = {
#         "username": "Handsome_guy",
#         "password": "12345",
#         "email": "alekc080901@ya.ru",
#     }
#
#     client.post('/api/register', json=data)
#
#     # Произведем попытку войти
#     data = {
#         "username": "Handsome_guy",
#         "password": "12345",
#     }
#
#     response = client.post('/api/login', json=data)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']
#     assert response.json['errno'] == 'account.not_verified'
#
#
# # ФУНКЦИЯ СМЕНЫ ПЕРСОНАЛЬНОЙ ИНФЫ
#
# def test_change_normal(client):
#     global token
#     if token is None:
#         assert False, 'No token (auth was unsuccessful)'
#
#     # Normal case
#     bearer = {'Authorization': f'Bearer {token}'}
#     data = {
#         "nickname": "GoOdByE LoRd",
#         "name": "Никита Александров",
#         "group": "Punk"
#     }
#
#     response = client.post("/api/info/change", json=data, headers=bearer)
#
#     assert response.content_type == 'application/json'
#     assert not response.json['error']
#
#
# def test_change_missed_info(client):
#     global token
#     if token is None:
#         assert False, 'No token (auth was unsuccessful)'
#
#     bearer = {'Authorization': f'Bearer {token}'}
#     data = {
#         "nickname": "GoOdByE LoRd",
#         "group": "Punk"
#     }
#
#     response = client.post("/api/info/change", json=data, headers=bearer)
#
#     assert response.content_type == 'application/json'
#     assert not response.json['error']
#
#
# def test_change_no_bearer(client):
#     data = {
#         "nickname": "GoOdByE LoRd",
#         "name": "Никита Александров",
#         "group": "Punk"
#     }
#
#     response = client.post("/api/info/change", json=data)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']
#     assert response.json['errno'] == 'authorization.invalid'
#
#
# def test_change_wrong_bearer(client):
#     bearer = {'Authorization': 'Bearer 123456.123.123'}
#     data = {
#         "nickname": "GoOdByE LoRd",
#         "name": "Никита Александров",
#         "group": "Punk"
#     }
#
#     response = client.post("/api/info/change", json=data, headers=bearer)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']
#     assert response.json['errno'] == 'authorization.invalid'
#
#
# def test_change_empty_json(client):
#     global token
#     if token is None:
#         assert False, 'No token (auth was unsuccessful)'
#
#     bearer = {'Authorization': f'Bearer {token}'}
#     data = {}
#
#     response = client.post("/api/info/change", json=data, headers=bearer)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']
#     assert response.json['errno'] == 'data.empty'
#
#
# # ФУНКЦИЯ СМЕНЫ ПАРОЛЯ 1
#
# def test_password_change1_normal(client):
#     data = {
#         "email": "alekc080901@mail.ru"
#     }
#
#     response = client.post('/api/forgot/request', json=data)
#
#     assert response.content_type == 'application/json'
#     assert not response.json['error']
#
#
# def test_password_change1_wrong_email(client):
#     data = {
#         "email": "alekc08090765745641@mail.ru"
#     }
#
#     response = client.post('/api/forgot/request', json=data)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']
#     assert response.json['errno'] == 'email.not_found'
#
#
# def test_password_change1_account_not_verified(client):
#     # Используем неполноценного Handsome_guy, объявленного выше
#     data = {
#         "email": "alekc080901@ya.ru"
#     }
#
#     response = client.post('/api/forgot/request', json=data)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']
#     assert response.json['errno'] == 'account.not_verified'
#
#
# def test_password_change1_empty_json(client):
#     data = {}
#
#     response = client.post('/api/forgot/request', json=data)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']
#     assert response.json['errno'] == ''
#
#
# # ФУНКЦИЯ СМЕНЫ ПАРОЛЯ 2
#
# def test_password_change2_normal(client):
#     user = users.find_one({"email": 'alekc080901@mail.ru'})
#     data = {
#         "email": "alekc080901@mail.ru",
#         "code": user['auth']['verification'],
#         "password": '54321'
#     }
#
#     response = client.post('/api/forgot/change', json=data)
#
#     assert response.content_type == 'application/json'
#     assert not response.json['error']
#
#
# def test_password_change2_empty_json(client):
#     data = {}
#
#     response = client.post('/api/forgot/change', json=data)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']
#     assert response.json['errno'] == ''
#
#
# def test_password_change2_missed_info(client):
#     data = {
#         "email": "alekc080901@mail.ru",
#         "password": '54321'
#     }
#
#     response = client.post('/api/forgot/change', json=data)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']
#     assert response.json['errno'] == ''
#
#
# def test_password_change2_wrong_code(client):
#     data = {
#         "email": "alekc080901@mail.ru",
#         "code": "123456",
#         "password": '54321'
#     }
#
#     response = client.post('/api/forgot/change', json=data)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']
#
#
# def test_password_change2_wrong_email(client):
#     data = {
#         "email": "alekc080901654645@mail.ru",
#         "code": "123456",
#         "password": '54321'
#     }
#
#     response = client.post('/api/forgot/change', json=data)
#
#     assert response.content_type == 'application/json'
#     assert response.json['error']


# СОЗДАНИЕ ТУРНИРА


def test_tournament_create_normal(client):
    tournament_db.delete_many({})

    data = {
        "name": "1234",
        "icon": os.path.abspath("./test_files/ПОЛИРОИД.png"),
        "description": "fjebfjewbfiuweewf",
        "createdAt": 1234,
        "finishesAt": 123456
    }

    response = client.post('/api/admin/tournament', json=data, method='POST')

    global tid
    tid = tournament_db.find_one({"display.name": "1234"})["tid"]

    assert response.content_type == 'application/json'
    assert not response.json['error']


def test_tournament_wrong_path(client):
    data = {
        "name": "1234",
        "icon": "./test_file...s/ПОgregreЛИРОИД.png",
        "description": "fjebfjewbfiuweewf",
        "finishesAt": 123456
    }

    response = client.post('/api/admin/tournament', json=data, method='POST')

    assert response.content_type == 'application/json'
    assert response.json['error']
    assert response.json['errno'] == 'icon'


def test_tournament_wrong_finish(client):
    data = {
        "name": "1234",
        "icon": "./test_files/ПОЛИРОИД.png",
        "description": "fjebfjewbfiuweewf",
        "forever": False
    }

    response = client.post('/api/admin/tournament', json=data, method='POST')

    assert response.content_type == 'application/json'
    assert response.json['error']
    assert response.json['errno'] == 'finishesAt'


def test_tournament_empty_json(client):
    data = {}

    response = client.post('/api/admin/tournament', json=data, method='POST')

    assert response.content_type == 'application/json'
    assert response.json['error']


def test_tournament_miss_some_info(client):
    data = {
        "description": "fjebfjewbfiuweewf"
    }

    response = client.post('/api/admin/tournament', json=data, method='POST')

    assert response.content_type == 'application/json'
    assert response.json['error']
    assert response.json['errno'] == ''


# ИЗМЕНЕНИЕ ТУРНИРА

def test_tournament_change_normal(client):
    global tid
    data = {
        "tid": tid,
        "name": "12345678",
        "icon": os.path.abspath("./test_files/ПОЛИРОИД.png"),
        "description": "fjebfjewbfiuweewf",
        "finishesAt": 123456,
        "createdAt": 1234
    }

    response = client.put('/api/admin/tournament', json=data)

    assert response.content_type == 'application/json'
    assert not response.json['error']


def test_tournament_change_miss_info(client):
    data = {
        "finishesAt": 123456
    }

    response = client.put('/api/admin/tournament', json=data)

    assert response.content_type == 'application/json'
    assert response.json['error']
    assert response.json['errno'] == ''


def test_tournament_change_empty_json(client):
    data = {}

    response = client.put('/api/admin/tournament', json=data, method='UPDATE')

    assert response.content_type == 'application/json'
    assert response.json['error']
    assert response.json['errno'] == ''


def test_tournament_wrong_tid(client):
    data = {
        "tid": "this_is_wrong",
        "name": "12345678"
    }

    response = client.put('/api/admin/tournament', json=data)

    assert response.content_type == 'application/json'
    assert response.json['error']
    assert response.json['errno'] == "tid.wrong"


def test_tournament_keys(client):
    global tid
    data = {
        "tid": tid,
        "name": "12345678",
        "now": True,
        "forever": True
    }

    response = client.put('/api/admin/tournament', json=data)

    assert response.content_type == 'application/json'
    assert response.json['error']
    assert response.json['errno'] == "keys.both_true"


def test_sending_file_normal(client):
    global tid
    global token

    # Удаление файлов предыдущих тестов
    files = os.listdir(UPLOAD_FOLDER)
    for item in files:
        if item.endswith(".py"):
            os.remove(os.path.join(UPLOAD_FOLDER, item))

    if token is None:
        assert False, 'No token (auth was unsuccessful)'
    bearer = {'Authorization': f'Bearer {token}'}

    server_file = {'file': (BytesIO(b'info'), 'send.py')}

    response = client.post(f'/api/tournament/{tid}/solution', data=server_file, headers=bearer)

    assert not response.json['error']

    global cid
    cid = users_code.find_one({"username": "alekc080901"})["cid"]


def test_sending_file_wrong_extension(client):
    global tid

    global token
    if token is None:
        assert False, 'No token (auth was unsuccessful)'
    bearer = {'Authorization': f'Bearer {token}'}

    server_file = {'file': (BytesIO(b'info'), 'send.exe')}

    response = client.post(f'/api/tournament/{tid}/solution', data=server_file, headers=bearer)

    assert response.json['error']
    assert response.json['errno'] == 'filename.wrong_extension'


def test_sending_file_wrong_name(client):
    global tid

    global token
    if token is None:
        assert False, 'No token (auth was unsuccessful)'
    bearer = {'Authorization': f'Bearer {token}'}

    server_file = {'file': (BytesIO(b'info'), 'sen.d.py')}

    response = client.post(f'/api/tournament/{tid}/solution', data=server_file, headers=bearer)

    assert response.json['error']
    assert response.json['errno'] == 'file.wrong_name'


def test_sending_file_wrong_file_header(client):
    global tid

    global token
    if token is None:
        assert False, 'No token (auth was unsuccessful)'
    bearer = {'Authorization': f'Bearer {token}'}

    server_file = {'wrong': (BytesIO(b'info'), 'sen.d.py')}

    response = client.post(f'/api/tournament/{tid}/solution', data=server_file, headers=bearer)

    assert response.json is None  # Сервер принимает только заголовок 'file'. В ином случае ответа от сервера не будет


def test_sending_file_wrong_type(client):
    global tid

    global token
    if token is None:
        assert False, 'No token (auth was unsuccessful)'
    bearer = {'Authorization': f'Bearer {token}'}

    data = {"1": 2}

    response = client.post(f'/api/tournament/{tid}/solution', json=data, headers=bearer)

    assert response.json is None


def test_cid_activation_normal(client):
    global tid

    global token
    if token is None:
        assert False, 'No token (auth was unsuccessful)'
    bearer = {'Authorization': f'Bearer {token}'}

    global cid
    old_cid = cid
    test_sending_file_normal(client)

    response = client.post(f'/api/code/activate/{old_cid}', headers=bearer)

    user = tournament_users.find_one({"uid": "alekc080901"})
    assert response.status_code == 200
    assert user['code'] == old_cid


def test_cid_activation_wrong_cid(client):
    global tid

    global token
    if token is None:
        assert False, 'No token (auth was unsuccessful)'
    bearer = {'Authorization': f'Bearer {token}'}

    response = client.post(f'/api/code/activate/12345', headers=bearer)

    assert response.status_code == 404
    assert response.json['error']
    assert response.json['errno'] == 'cid'


# GET-ЗАПРОСЫ


def test_tournament_info(client):
    global tid
    response = client.get(f'/api/tournament/{tid}/info')

    assert response.status_code == 200
    assert response.json == {
        "tid": tid,
        "createdAt": 1234,
        "finishesAt": 123456,
        "display": {
            "name": "12345678",
            "icon": os.path.abspath("./test_files/ПОЛИРОИД.png"),
            "description": "fjebfjewbfiuweewf"
        }
    }


def test_user_tournament(client):
    global tid
    response = client.get('/api/user/alekc080901/tournament_list')

    assert response.status_code == 200
    assert response.json['tournaments'] == [tid]


def test_user_file_list(client):
    global tid
    global token
    if token is None:
        assert False, 'No token (auth was unsuccessful)'
    bearer = {'Authorization': f'Bearer {token}'}

    response = client.get(f'/api/code/find/{tid}', headers=bearer)

    assert response.status_code == 200  # Так как значения каждый раз разные, проверять их валидность затруднительно


def test_user_info(client):
    global tid
    response = client.get('/api/user/alekc080901/info')

    assert response.status_code == 200
    assert response.json == {
        "nickname": "HeLlO LoRd",
        "name": "Александр Никитин",
        "group": "Крови на рукаве"
    }



