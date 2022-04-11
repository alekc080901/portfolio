FROM ubuntu:18.04

ENV MAILGUN_API_KEY="a69de5447db8f3ad99df1b53d395c641-ee13fadb-21463b2f" \
    MAILGUN_DOMAIN="sandboxcfc7fbd2b1a4454d9cffa8040df53368.mailgun.org" \
    PORT=5000

EXPOSE 5000

RUN apt-get update -yqq \
    && apt-get install \
        --no-install-recommends \
        -yqq \
        curl \
        software-properties-common \
        apt-utils \
    && add-apt-repository ppa:deadsnakes/ppa -y \
    && apt-get install python3.7 -yqq \
    && curl https://bootstrap.pypa.io/get-pip.py -o /tmp/get-pip.py \
    && python3.7 /tmp/get-pip.py

COPY . /coderoyale

WORKDIR /coderoyale

RUN python3.7 -m pip install --no-cache-dir -q -r requirements.txt

CMD ["uvicorn", "main:app"]