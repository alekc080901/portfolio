CC = gcc
CFLAGS = -std=gnu99 -g
SERVER_SOURCES = server.c algorithm.c socketOperations.c signals.c log.c security.c
CLIENT_SOURCES = client.c socketOperations.c signals.c log.c security.c
LIBRARIES = -lm -lpam -lpam_misc

all:
	$(CC) $(CFLAGS) $(SERVER_SOURCES) -o server.out $(LIBRARIES)
	$(CC) $(CFLAGS) $(CLIENT_SOURCES) -o client.out $(LIBRARIES)
