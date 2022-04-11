from functools import wraps

import jwt
from flask import jsonify, request
from jsonschema import Draft7Validator
from jwt import PyJWTError

from const import SECRET
from database import users
from validators import validate


def use_validator(validator):
    if not isinstance(validator, Draft7Validator):
        raise TypeError(f"Cannot wrap with validator like this: {validator}")

    def wrapper(func):
        @wraps(func)
        def decorated(*args, **kwargs):
            data = request.get_json()
            is_valid, cause = validate(validator, data)

            if not is_valid:
                resp = jsonify(error=True, errno=cause)
                resp.status_code = 403
                return resp

            return func(*args, data=data, **kwargs)

        return decorated

    return wrapper


def use_authorisation(func):
    @wraps(func)
    def decorated(*args, **kwargs):
        auth = request.headers.get("Authorization", '').split(' ')

        if len(auth) != 2 or auth[0] != 'Bearer':
            resp = jsonify(error=True, errno="authorization.invalid")
            resp.status_code = 401
            return resp

        try:
            result = jwt.decode(auth[1], SECRET, verify=True, algorithms=['HS256'])
        except PyJWTError as err:
            resp = jsonify(error=True, errno="authorization.invalid")
            resp.status_code = 401
            return resp

        username = result["user"]

        return func(*args, username=username, **kwargs)

    return decorated


def use_get_user(func):
    @wraps(func)
    def decorated(*args, username=None, **kwargs):
        if username is None:
            user = None
        else:
            user = users.find_one({"username": username})

        return func(*args, username=username, user=user, **kwargs)

    return decorated
