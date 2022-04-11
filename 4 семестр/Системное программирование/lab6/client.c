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

#include "client.h"
#include "socketOperations.h"
#include "signals.h"
#include "log.h"

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

/*! \brief Inputs the string from user console into the variable
 *
 *  \param[out] word String variable of arbitrary length
 *
 *  \return Nothing
 */
void inputString(char** word)
{
    int count = 0;
    char inputChar = 0;

    fflush(stdin);
    *word = NULL;

    while (1)
    {
        inputChar = getchar();
        if (inputChar == '\n')
            break;
        else
        {
            *word = realloc(*word, count + 2);
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

/*! \brief Client main function
 *  \param argc  Number of command line arguments
 *  \param argv  An array of command line arguments.
 *               argv[0] - the program name,
 *               argv[1] - a socket IP-address,
 *               argv[2] - a socket port number,
 *               argv[3] - log file name,
 *               argv[4] - server existence time without activity in seconds.
 *  \return Integer 0 upon exit success,
 *          or EXIT_FAILURE otherwise.
 */
int main(int argc, const char* argv[])
{
    registerHandler();
    char* firstFraction = NULL;
    char* secondFraction = NULL;
    char* operationSign = NULL;

    if (argc != 5)
    {
        puts("Socket name, port number, log file and client existence time expected.\n");
        return EXIT_FAILURE;
    }

    if (!checkNat((char*) argv[2]))
    {
        puts("Incorrect port number expected.\n");
        return EXIT_FAILURE;
    }

    if (strchr(argv[3], '/') != NULL)
    {
        puts("Incorrect log name.\n");
        return EXIT_FAILURE;
    }

    if (!checkNat((char*) argv[4]))
    {
        puts("Incorrect time.\n");
        return EXIT_FAILURE;
    }

    char* serverIP = (char*) argv[1];
    char* port = (char*) argv[2];

    char* logDirectoryPath = "./logs";
    char logPath[strlen(logDirectoryPath) + strlen(argv[3]) + 1];
    strcpy(logPath, logDirectoryPath);
    strcat(logPath, "/");
    strcat(logPath, argv[3]);

    int time = strtol(argv[4], NULL, 10);

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

        writeLog(logPath, buffer);

        char* info = NULL;
        receiveSocketText(socketFileDescriptor, &info);
        printf("\n%s\n", info);
        free(info);

        close(socketFileDescriptor);
    }
    return 0;
}