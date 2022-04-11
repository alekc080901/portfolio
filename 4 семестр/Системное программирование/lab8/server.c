/*! \file    server.c
 *  \brief   Server part of project.
 *
 *  \details Accepts the info from client, process it and returns back.
 *
 *  \author Nikitin Alexander, KI19-17/1Б
 */

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "algorithm.h"
#include "server.h"
#include "socketOperations.h"
#include "signals.h"
#include "log.h"
#include "security.h"

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

/*! \brief Checks if the string is a natural number or 0
 *
 * \param[in] string String that may be a number or not
 *
 *  \return true or false
 */
bool checkNat0(char* string)
{
    for (int i = 0; string[i] != '\0'; i++)
        if (!isdigit(string[i]))
            return false;

    if (strtol(string, NULL, 10) < 0)
        return false;
    return true;
}

/*! \brief Outputs the console parameters to the user
 *
 *  \return Nothing
 */
void printArguments()
{
    printf("-p - port assignment\n"
           "-l - (optional) log name assignment\n"
           "-t - (optional) server life time assignment\n"
           "-h - (optional) show help\n"
           "-c - (optional) check if the disk is full\n"
           "You need to be a root to run this program.\n");
}

/*! \brief Calculates the file size
 *
 * \param fd File descriptor
 *
 *  \return File size
 */
int getFileSize(int fd)
{
    struct stat info;
    int fstatSuccess = fstat(fd, &info);
    if (fstatSuccess)
    {
        perror("Getting file info went wrong");
    }

    return info.st_size;
}

/*! \brief Checks is the same copy of server currently run. If it is so, kills the program.
 *
 *  \return Nothing
 */
void checkServerUnique()
{
    int fd = open(SERVER_UNIQUE_FILE_PATH, O_RDONLY | O_CREAT , 0666);
    if (getFileSize(fd) != 0)
    {
        printf("Server must be unique!\n");
        exit(EXIT_SUCCESS);
    }
    close(fd);
}

/*! \brief Block the server not allowing another copy of the server to be run.
 *
 *  \return Nothing
 */
void block()
{
    char* message = "Closed";
    int fd = open(SERVER_UNIQUE_FILE_PATH, O_WRONLY | O_CREAT , 0660);
    int wrErr = write(fd, message, strlen(message));
    if (wrErr == -1)
    {
        perror("Write error");
        exit(EXIT_EMPTINESS);
    }
    close(fd);
}

/*! \brief Server main function
 *  \param[in] argc  Number of command line arguments
 *  \param[in] argv  An array of command line arguments.
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

    if (argc == 1)
    {
        printArguments();
        exit(EXIT_SUCCESS);
    }

    rootCheck();
    checkServerUnique();

    // Задаем значения по умолчанию
    char* port = NULL;
    char* logPath = "./logs/clients.log";;
    int time = 60;

    int opt;
    bool diskCheck = false;
    while((opt = getopt(argc, (char* const*) argv, "p:l:t:hc")) != -1)
    {
        switch(opt)
        {
        case 'p':
            port = (char*) optarg;
            break;

        case 'l':
            if (strlen(optarg) > MAX_LOG_LENGTH)
            {
                printf("Log name must be less than 30 symbols\n");
                exit(EXIT_SUCCESS);
            }
            logPath = optarg;
            break;

        case 't':
            if (!checkNat(optarg))
            {
                printf("Time must be a number!\n");
            }
            time = strtol(optarg, NULL, 10);
            break;

        case 'h':
            printArguments();
            exit(EXIT_SUCCESS);
            break;

        case 'c':
            diskCheck = true;
            break;

        case '?':
            printf("Unknown option: %c\n", optopt);
            exit(EXIT_FAILURE);
            break;
        }
    }

    if (port == NULL)
    {
        printf("Port number must be specified!\n");
        exit(EXIT_SUCCESS);
    }

    bool isWrong = false;

    if (!checkNat0(port))
    {
        printf("Incorrect port number: %s.\n", port);
        isWrong = true;
    }

    if (time <= 0)
    {
        printf("Incorrect time: %d.\n", time);
        isWrong = true;
    }

    if (isWrong)
        return EXIT_FAILURE;

    if (diskCheck)
        checkFullness(logPath);

    block();
    puts("Server is running.");

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

        if (diskCheck)
            checkFullness(logPath);
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
