CC = gcc
CFLAGS = -std=gnu99 -g
SERVER_SOURCES = server.c algorithm.c socketOperations.c signals.c log.c
CLIENT_SOURCES = client.c socketOperations.c signals.c log.c
LIBRARIES = -lm

all:
	$(CC) $(CFLAGS) $(SERVER_SOURCES) $(LIBRARIES) -o server.o
	$(CC) $(CFLAGS) $(CLIENT_SOURCES) -o client.o
