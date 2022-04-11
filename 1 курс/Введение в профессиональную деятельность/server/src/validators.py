import time
from typing import Optional, Tuple

from jsonschema import Draft7Validator, ValidationError

login_validator = Draft7Validator({
    "required": ["username", "password"],
    "properties": {
        "username": {
            "type": "string",
            "pattern": r"[a-zA-Z0-9-_]{4,32}"
        },
        "password": {
            "type": "string",
            "minLength": 4,
            "maxLength": 32
        }
    }
})

register_validator = Draft7Validator({
    "required": ["username", "password", "email"],
    "properties": {
        "username": {
            "type": "string",
            "pattern": r"[a-zA-Z0-9-_]{4,32}"
        },
        "password": {
            "type": "string",
            "minLength": 4,
            "maxLength": 32
        },
        "email": {
            "type": "string",
            "pattern": r"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)"
        },
        "group": {
            "type": "string",
            "maxLength": 16,
        },
        "name": {
            "type": "string",
            "maxLength": 64,
        },
        "nickname": {
            "type": "string",
            "maxLength": 32,
        }
    }
})

change_info_validator = Draft7Validator({
    "required": [],
    "properties": {
        "nickname": {
            "type": "string",
            "maxLength": 32,
        },
        "name": {
            "type": "string",
            "maxLength": 64,
        },
        "group": {
            "type": "string",
            "maxLength": 16,
        },
        "status": {
            "type": "string",
            "maxLength": 120,
        },
        "about_myself": {
            "type": "string",
            "maxLength": 500,
        },
        "language": {
            "type": "integer",
            "minimum": 1,
            "maximum": 7  # 6 основных языков и вторая версия Питона. Будет дополняться при необходимости
        }
    }
})

forgot_password_stage_one_validator = Draft7Validator({
    "required": ["email"],
    "properties": {
        "email": {
            "type": "string",
            "pattern": r"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)"
        }
    }
})

change_password_stage_two_validator = Draft7Validator({
    "required": ["email", "code", "password"],
    "properties": {
        "email": {
            "type": "string",
            "pattern": r"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)"
        },
        "code": {
            "type": "string",
            "pattern": r"^[0-9]{6}$"
        },
        "password": {
            "type": "string",
            "minLength": 4,
            "maxLength": 32
        }
    }
})

tournament_validator_create = Draft7Validator({
    "required": ["name", "description", "icon"],
    "type": "object",
    "properties": {
        "tid": {
            "type": "string",
            "maxLength": 32
        },
        "name": {
            "type": "string",
            "maxLength": 32
        },
        "description": {
            "type": "string",
            "maxLength": 1024
        },
        "icon": {
            "type": "string",
            "pattern": r"\.png$"
        },
        "createdAt": {
            "type": "integer",
            "minimum": 0,
        },
        "finishesAt": {
            "type": "integer",
        },
        "forever": {
            "type": "boolean"
        }
    }
})

tournament_validator_finish = Draft7Validator({
    "required": ["tid"],
    "type": "object",
    "properties": {
        "name": {
            "type": "string",
            "maxLength": 32
        },
        "finishesAt": {
            "type": "integer"
        },
        "forever": {
            "type": "boolean"
        },
        "now": {
            "type": "boolean"
        }
    }
})

tournament_validator_change_cid = Draft7Validator({
    "required": ["cid"],
    "type": "object",
    "properties": {
        "name": {
            "type": "string",
            "maxLength": 32
        },
        "cid": {
            "type": "string"
        }
    }
})


def validate(validator, data: dict) -> Tuple[bool, Optional[str]]:
    try:
        validator.validate(data)
    except ValidationError as err:
        return False, '.'.join(err.path)
    else:
        return True, None
