#include <string.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdbool.h>

#include "socketOperations.h"

/*! \brief Writes the buffer content into socket.
 *
 *  \param[in] s File descriptor of socket
 *  \param[in] buf The information to be written
 *  \param[in] len Length of this information
 *
 *  \return Is the operation successful.
 */
bool sendSocketBuf(int s, void* buf, int len)
{
    int writeError = send(s, buf, len, 0);
    if (writeError == -1)
    {
        perror("Write length error");
        return false;
    }
    return true;
}

/*! \brief Writes the text into socket.
 *
 *  \param[in] socketFileDescriptor File descriptor of socket
 *  \param[in] text Text that will be written into socket
 *
 *  \return Nothing.
 */
void sendSocketText(int socketFileDescriptor, char* text)
{
    int length = strlen(text) + 1;

    // Записываем длину
    sendSocketBuf(socketFileDescriptor, &length, sizeof(int));
    // Записываем строку
    sendSocketBuf(socketFileDescriptor, text, length);
}

/*! \brief Read the information from socket and saves it into the buffer.
 *
 *  \param[in] s File descriptor of socket
 *  \param[out] buf The information to be read
 *  \param[in] len Length of this information
 *
 *  \return Is the operation successful.
 */
bool readSocketBuf(int s, void* buf, int len)
{
    int recvError = recv(s, buf, len, 0);
    if (recvError == -1)
    {
        perror("Socket read error");
        return false;
    }
    return true;
}

/*! \brief Read the text from socket.
 *
 *  \param[in] clientSocketFileDescriptor File descriptor of socket
 *  \param[out] text Text that where the information from socket will be written
 *
 *  \return Is the operation successful.
 */
bool receiveSocketText(int clientSocketFileDescriptor, char** text)
{
    int length;

    if (!readSocketBuf(clientSocketFileDescriptor, &length, sizeof(int)))
        return false;

    char temp[length];
    *text = malloc(sizeof(char) * length);

    if (!readSocketBuf(clientSocketFileDescriptor, temp, length))
        return false;

    strcpy(*text, temp);

    printf("The information from socket has been received. Content: %s\n", *text);

    return true;
}

/*! \brief Creates a TCP socket for a client part.
 *
 *  \return File descriptor of the socket.
 */
int createClientTCPSocket()
{
    int socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDescriptor == -1)
    {
        perror("Socket creation error");
        return -1;
    }
    return socketFileDescriptor;
}

/*! \brief Creates a TCP socket for a server part.
 *
 *  \return File descriptor of the socket.
 */
int createServerTCPSocket()
{
    int socketFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    int i = 1;
    int setsockError = setsockopt(socketFileDescriptor, SOL_SOCKET, SO_REUSEADDR,
                                  (const char*) &i, sizeof(i)
    );

    if (socketFileDescriptor == -1 || setsockError == -1)
    {
        perror("Socket creation error");
        return -1;
    }
    return socketFileDescriptor;
}

/*! \brief Creates the name to the TCP socket and binds it to it.
 *
 *  \param[in] socketFileDescriptor File descriptor of socket
 *  \param[in] port TCP port
 *
 *  \return Is the operation successful.
 */
bool bindTCPSocket(int socketFileDescriptor, char* port)
{
    int portNumber = strtol(port, NULL, 10);

    struct sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_port = htons((u_short) portNumber);
    name.sin_addr.s_addr = INADDR_ANY;

    int bindError = bind(socketFileDescriptor, (const struct sockaddr*) &name, sizeof(name));
    if (bindError == -1)
    {
        perror("Bind error");
        return false;
    }

    return true;
}

/*! \brief Connects socket to the server.
 *
 *  \param[in] socketFileDescriptor File descriptor of socket
  * \param[in] serverIP An IP to connect the socket
 *  \param[in] port TCP port
 *
 *  \return Is the operation successful.
 */
bool connectTCPSocket(int socketFileDescriptor, char* serverIP, char* port)
{
    struct sockaddr_in name;
    memset((char*) &name, 0, sizeof(name));

    name.sin_family = AF_INET;
    name.sin_addr.s_addr = inet_addr(serverIP);

    int portNumber = strtol(port, NULL, 10);

    if (name.sin_addr.s_addr == INADDR_NONE)
    {
        puts("Incorrect IP address!");
        return EXIT_FAILURE;
    }
    name.sin_port = htons((u_short) portNumber);

    int connectionError = connect(socketFileDescriptor, (struct sockaddr*) &name, (socklen_t)
    sizeof(name));
    if (connectionError == -1)
    {
        perror("Connection error");
        return false;
    }

    return true;
}

/*! \brief Switch server into the ready-to-listen to sockets state.
 *
 *  \param[in] socketFileDescriptor File descriptor of socket
 *
 *  \return Is the operation successful.
 */
bool serverListen(int socketFileDescriptor)
{
    int listenError = listen(socketFileDescriptor, BACKLOG_NUMBER);
    if (listenError == -1)
    {
        perror("Listen error");
        return false;
    }

    return true;
}

/*! \brief Switch server into the waiting-for-sockets state.
 *
 *  \param[in] socketFileDescriptor File descriptor of socket
 *
 *  \return Is the operation successful.
 */
int acceptTCPSocket(int socketFileDescriptor)
{
    struct sockaddr_in clientName;
    socklen_t clientNameLength = sizeof(clientName);

    int clientSocketFileDescriptor = accept(socketFileDescriptor, (struct sockaddr*) &clientName, &clientNameLength
    );

    if (clientSocketFileDescriptor == -1)
    {
        perror("Accept error");
        return -1;
    }

    return clientSocketFileDescriptor;
}