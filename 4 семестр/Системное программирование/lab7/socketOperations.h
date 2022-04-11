#ifndef INC_1_SOCKETOPERATIONS_H

#define INC_1_SOCKETOPERATIONS_H

#define BACKLOG_NUMBER 4

void setTimerServer();

void setTimerClient();

void sendSocketText(int socketFileDescriptor, char* text);

bool readSocketBuf(int s, void* buf, int len);

bool receiveSocketText(int socketFileDescriptor, char** text);

int createClientTCPSocket();

int createServerTCPSocket();

bool connectTCPSocket(int socketFileDescriptor, char* serverIP, char* port);

bool bindTCPSocket(int socketFileDescriptor, char* port);

bool serverListen(int socketFileDescriptor);

int acceptTCPSocket(int socketFileDescriptor);

#endif
