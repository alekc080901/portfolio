import os

SECRET = 'tetriandoh'
DEFAULT_RATE = 1800

MAILGUN_API_KEY = os.environ["MAILGUN_API_KEY"]
MAILGUN_DOMAIN = os.environ['MAILGUN_DOMAIN']
MAILGUN_MAIL = f"king@{MAILGUN_DOMAIN}"

if os.environ.get('ENVIRONMENT', 'production') == 'test':
    UPLOAD_FOLDER = './test_files'
else:
    UPLOAD_FOLDER = os.environ["USERS_CODE_DIRECTORY"]

# ALLOWED_EXTENSIONS = ('zip', 'rar', '7z', 'tar', 'gzip', 'bzip2', 'js', 'py', 'pas', 'cs', 'cpp', 'c', 'java')
ALLOWED_EXTENSIONS = ('js', 'py', 'pas', 'cs', 'cpp', 'c', 'java')
