CC = gcc
CFLAGS = -std=gnu99
SERVER_SOURCES = server.c algorithm.c socketOperations.c
CLIENT_SOURCES = client.c socketOperations.c
LIBRARIES = -lm

all:
	$(CC) $(CFLAGS) $(SERVER_SOURCES) $(LIBRARIES) -o server.o
	$(CC) $(CFLAGS) $(CLIENT_SOURCES) -o client.o
