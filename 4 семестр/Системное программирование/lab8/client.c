/*! \file    client.c
 *  \brief   client part of project.
 *
 *  \details Sends the info to server and takes the processed info.
 *
 *  \author Nikitin Alexander, KI19-17/1Б
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "client.h"
#include "socketOperations.h"
#include "signals.h"
#include "log.h"
#include "security.h"

#define RADIX 10
#define NUMBER_OF_COMPARISON_OPERATORS 10
#define MAX_LENGTH_COMPARISON_OPERATORS 2

/*! \brief Strrev function from <string.h> which is not available in Linux.
 *
 *  \param[in] str Source string
 *
 *  \return Reversed string
 */
char* strrev(char* str)
{
    if (!str || !*str)
        return str;

    int i = strlen(str) - 1, j = 0;

    char ch;
    while (i > j)
    {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;
    }
    return str;
}

///*! \brief Inputs the string from user console (tty) into the variable
// *
// *  \param[out] word String variable of arbitrary length
// *
// *  \return Nothing
// */
void inputString(char** word)
{
    int count = 0;
    char inputChar = 0;

    int fd = open("/dev/tty", O_RDWR | O_NOCTTY);
    FILE* tty = fdopen(fd, "w+");

    fflush(tty);

    *word = NULL;
    while (1)
    {
        inputChar = getc(tty);
        if (inputChar == '\n')
            if (count != 0)  // ќбработка считывани¤ единичного \n
                break;
            else
                continue;
        else
        {
            *word = realloc(*word, count + 1);
            if (*word == NULL)
                perror("Realloc has returned a NULL pointer");

            (*word)[count] = inputChar;
            count++;
        }
    }
    (*word)[count] = '\0';
}

/*! \brief Checks whether the string is fraction-type (x/x, x.x) or not.
 *
 *  \param[in] string Verifiable string
 *
 *  \return Is the string fraction-type or not
 */
bool checkFraction(char* string)
{
    char* endPtr = NULL;

    strtol(string, &endPtr, RADIX);
    if (strcmp(string, endPtr) == 0 || (endPtr[0] != '.' && endPtr[0] != '/' && endPtr[0] != ','))  // Если строка не
        // начинается с символа и первая часть не заканчивается разделителем
        return false;

    strcpy(string, strrev(string));
    strtol(string, &endPtr, RADIX);
    if (strcmp(string, endPtr) == 0 || (endPtr[0] != '.' && endPtr[0] != '/' && endPtr[0] != ','))  // Если строка не
        // начинается с символа и первая часть не заканчивается разделителем
        return false;

    strrev(string);
    return true;
}

/*! \brief Checks if the operation type is supportable in the program.
* List of operations: ("+", "-", "*", "/", "<", ">", "=", "!=", ">=", "<=")
*
*  \param[in] operation Operation string
*
*  \return If the operator is appropriate (true or false)
*/
bool checkOperation(char* operation)
{
    char allOperations[NUMBER_OF_COMPARISON_OPERATORS][MAX_LENGTH_COMPARISON_OPERATORS + 1]
            = {"+", "-", "*", "/", "<", ">", "=", "!=", ">=", "<="};

    for (int i = 0; i < sizeof(allOperations) / sizeof(*allOperations); i++)
        if (strcmp(allOperations[i], operation) == 0)
            return true;
    return false;
}

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
    printf("-i - (optional) server IP assignment;\n"
           "-p - port assignment\n"
           "-l - (optional) log name assignment\n"
           "-t - (optional) client life time assignment\n"
           "-h - (optional) show help\n"
           "-c - (optional) check if the disk is full\n"
           "You need to enter password to run this program.\n");
}

/*! \brief Client main function
 *  \param argc  Number of command line arguments
 *  \param argv  An array of command line arguments.
 *  \return Integer 0 upon exit success,
 *          or EXIT_FAILURE otherwise.
 */
int main(int argc, const char* argv[])
{
    registerHandler();

    char* firstFraction = NULL;
    char* secondFraction = NULL;
    char* operationSign = NULL;

    if (argc == 1)
    {
        printArguments();
        exit(EXIT_SUCCESS);
    }

    auth();

    // Задаем значения по умолчанию
    char* serverIP = "127.0.0.1";
    char* port = NULL;
    char* logPath = "./logs/clients.log";
    int time = 60;

    int opt;
    bool diskCheck = false;
    while((opt = getopt(argc, (char* const*) argv, "i:p:l:t:hc")) != -1)
    {
        switch(opt)
        {
        case 'i':
            serverIP = (char*) optarg;
            break;

        case 'p':
            port = (char*) optarg;
            break;

        case 'l':
            if (strlen(optarg) > MAX_LOG_LENGTH)
            {
                printf("Log name must be less than 30 symbols\n");
                exit(EXIT_SUCCESS);
            }

            logPath = (char*) optarg;
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

    int socketFileDescriptor;
    while (true)
    {
        setTimerClient(time);
        do
        {
            puts("Input first fraction:");
            inputString(&firstFraction);
        } while (!checkFraction(firstFraction));

        do
        {
            puts("Input operation:");
            inputString(&operationSign);
        } while (!checkOperation(operationSign));

        do
        {
            puts("Input second fraction:");
            inputString(&secondFraction);
        } while (!checkFraction(secondFraction));

        socketFileDescriptor = createClientTCPSocket();
        connectTCPSocket(socketFileDescriptor, serverIP, port);

        sendSocketText(socketFileDescriptor, firstFraction);
        sendSocketText(socketFileDescriptor, operationSign);
        sendSocketText(socketFileDescriptor, secondFraction);

        char buffer[strlen(firstFraction) + strlen(operationSign) + strlen(secondFraction) + 3];
        strcpy(buffer, firstFraction);
        strcat(buffer, " ");
        strcat(buffer, operationSign);
        strcat(buffer, " ");
        strcat(buffer, secondFraction);
        strcat(buffer, "\n");

        if (diskCheck)
            checkFullness(logPath);
        writeLog(logPath, buffer);

        char* info = NULL;
        receiveSocketText(socketFileDescriptor, &info);
        printf("\n%s\n", info);
        free(info);

        close(socketFileDescriptor);
    }
    return 0;
}