FROM ubuntu:18.04

ARG FILENAME
ENV FILE_RUN_COMMAND="python3.6 -u $/files/$FILENAME"
ENV SOCK_HOST="127.0.0.1"
ENV SOCK_PORT="8888"

RUN apt-get update -yqq \
    && apt-get install \
        --no-install-recommends \
        -yqq \
        curl \
    && add-apt-repository ppa:deadsnakes/ppa -y \
    && apt-get install python3.7 -yqq \
    && curl https://bootstrap.pypa.io/get-pip.py -o /tmp/get-pip.py \
    && python3.7 /tmp/get-pip.py \
    && python3.7 -m pip install -U numpy scipy scikit-learn pandas

WORKDIR /coderoyale/worker

COPY . /coderoyale/worker
