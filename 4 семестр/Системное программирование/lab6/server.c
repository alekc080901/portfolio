/*! \file    server.c
 *  \brief   Server part of project.
 *
 *  \details Accepts the info from client, process it and returns back.
 *
 *  \author Nikitin Alexander, KI19-17/1Á
 */

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#include "algorithm.h"
#include "server.h"
#include "socketOperations.h"
#include "signals.h"
#include "log.h"

/*! \brief Checks if the string is a natural number
 *
 * \param[in] string String that may be a number or not
 *
 *  \return true or false
 */
bool checkNat(char* string)
{
    for (int i = 0; string[i] != '\0'; i++)
        if (!isdigit(string[i]))
            return false;

    if (strtol(string, NULL, 10) <= 0)
        return false;
    return true;
}

/*! \brief Server main function
 *  \param[in] argc  Number of command line arguments
 *  \param[in] argv  An array of command line arguments.
 *               argv[0] - the program name,
 *               argv[1] - the port number,
 *               argv[2] - log file name,
 *               argv[3] - server existence time without activity in seconds.
 *  \return Integer 0 upon exit success,
 *          or EXIT_FAILURE otherwise.
 */
int main(int argc, const char* argv[])
{
    registerHandler();

    char* socketFirstFraction = NULL;
    char* socketOperation = NULL;
    char* socketSecondFraction = NULL;

    fractionInfo_t firstFraction;
    fractionInfo_t secondFraction;
    fractionInfo_t result;

    if (argc != 4)
    {
        puts("Port number, log file and server existence time expected.\n");
        return EXIT_FAILURE;
    }

    if (!checkNat((char*) argv[1]))
    {
        puts("Incorrect port number.\n");
        return EXIT_FAILURE;
    }

    if (strchr(argv[2], '/') != NULL)
    {
        puts("Incorrect log name.\n");
        return EXIT_FAILURE;
    }

    if (!checkNat((char*) argv[3]))
    {
        puts("Incorrect time.\n");
        return EXIT_FAILURE;
    }

    puts("Server is running.");

    char* port = (char*) argv[1];

    char* logDirectoryPath = "./logs";
    char logPath[strlen(logDirectoryPath) + strlen(argv[2]) + 1];
    strcpy(logPath, logDirectoryPath);
    strcat(logPath, "/");
    strcat(logPath, argv[2]);

    int time = strtol(argv[3], NULL, 10);

    int socketFileDescriptor = createServerTCPSocket();

    bindTCPSocket(socketFileDescriptor, port);

    serverListen(socketFileDescriptor);
    puts("Server is listening.");

    int clientSocketFileDescriptor;
    while (true)
    {
        setTimerServer(time);
        clientSocketFileDescriptor = acceptTCPSocket(socketFileDescriptor);
        printf("The socket has been connected to the server.\n");

        receiveSocketText(clientSocketFileDescriptor, &socketFirstFraction);
        printf("The information from socket has been received. Content: %s\n", socketFirstFraction);
        receiveSocketText(clientSocketFileDescriptor, &socketOperation);
        printf("The information from socket has been received. Content: %s\n", socketOperation);
        receiveSocketText(clientSocketFileDescriptor, &socketSecondFraction);
        printf("The information from socket has been received. Content: %s\n", socketSecondFraction);

        firstFraction = makeIntoFraction(socketFirstFraction);
        secondFraction = makeIntoFraction(socketSecondFraction);

        char* sentInfo = malloc( sizeof (char) * (sizeof (socketFirstFraction) + sizeof (socketOperation)
                                                  + sizeof (socketSecondFraction) + 40));

        if (firstFraction.isWrong || secondFraction.isWrong)
        {
            sprintf(sentInfo, "%s", "Incorrect fraction information!");
            continue;
        }

        if (strcmp(socketOperation, "+") == 0 || strcmp(socketOperation, "-") == 0 ||
            strcmp(socketOperation, "/") == 0 || strcmp(socketOperation, "*") == 0)
        {
            result = calculate(firstFraction, secondFraction, socketOperation);

            if (result.type == COMMON)
                if (result.isNegative)
                    sprintf(sentInfo, "%s %s %s = -%d/%d\n", socketFirstFraction, socketOperation,
                            socketSecondFraction, result.firstPart, result.secondPart);
                else
                    sprintf(sentInfo, "%s %s %s = %d/%d\n", socketFirstFraction, socketOperation,
                            socketSecondFraction, result.firstPart, result.secondPart);
            else
                if (result.isNegative)
                    sprintf(sentInfo, "%s %s %s = -%d.%d\n", socketFirstFraction, socketOperation,
                            socketSecondFraction, result.firstPart, result.secondPart);
                else
                    sprintf(sentInfo, "%s %s %s = %d.%d\n", socketFirstFraction, socketOperation,
                            socketSecondFraction, result.firstPart, result.secondPart);
        }
        else if (compare(firstFraction, secondFraction, socketOperation))
            sprintf(sentInfo, "%s %s %s: True\n", socketFirstFraction, socketOperation,
                     socketSecondFraction);
        else
            sprintf(sentInfo, "%s %s %s: False\n", socketFirstFraction, socketOperation,
                    socketSecondFraction);

        printf("\n%s\n", sentInfo);
        writeLog(logPath, sentInfo);
        sendSocketText(clientSocketFileDescriptor, sentInfo);

        free(socketFirstFraction);
        free(socketOperation);
        free(socketSecondFraction);
        free(sentInfo);

        close(clientSocketFileDescriptor);
    }
    return 0;
}
