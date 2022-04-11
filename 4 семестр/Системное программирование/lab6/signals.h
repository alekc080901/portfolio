#ifndef LAB5_SIGNALS_H

#define LAB5_SIGNALS_H

#define SUCCESS_CODE 0
#define ERROR_CODE -1
#define EXPIRATION_EXIT_CODE 2
#define SERVER_INACTIVITY_TIME_MS 0
#define CLIENT_INACTIVITY_TIME_MS 0


void setTimerServer(int sec);
void setTimerClient(int sec);
void registerHandler();

#endif
