#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#include "algorithm.h"
#include "server.h"
#include "socketOperations.h"

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
 *               argv[1] - the port number.
 *  \return Integer 0 upon exit success,
 *          or EXIT_FAILURE otherwise.
 */
int main(int argc, const char* argv[])
{
    char* socketFirstFraction = NULL;
    char* socketOperation = NULL;
    char* socketSecondFraction = NULL;

    fractionInfo_t firstFraction;
    fractionInfo_t secondFraction;
    fractionInfo_t result;

    if (argc != 2)
    {
        puts("Port number expected.\n");
        return EXIT_FAILURE;
    }

    if (!checkNat((char*) argv[1]))
    {
        puts("Incorrect port number.\n");
        return EXIT_FAILURE;
    }

    puts("Server is running.");

    char* port = (char*) argv[1];

    int socketFileDescriptor = createServerTCPSocket();

    bindTCPSocket(socketFileDescriptor, port);

    serverListen(socketFileDescriptor);
    puts("Server is listening.");

    int clientSocketFileDescriptor;
    while (true)
    {
        clientSocketFileDescriptor = acceptTCPSocket(socketFileDescriptor);
        printf("The socket has been connected to the server.\n");

        receiveSocketText(clientSocketFileDescriptor, &socketFirstFraction);
        receiveSocketText(clientSocketFileDescriptor, &socketOperation);
        receiveSocketText(clientSocketFileDescriptor, &socketSecondFraction);

        firstFraction = makeIntoFraction(socketFirstFraction);
        secondFraction = makeIntoFraction(socketSecondFraction);

        if (firstFraction.isWrong || secondFraction.isWrong)
        {
            puts("Incorrect fraction information!");
            continue;
        }

        if (strcmp(socketOperation, "+") == 0 || strcmp(socketOperation, "-") == 0 ||
            strcmp(socketOperation, "/") == 0 || strcmp(socketOperation, "*") == 0)
        {
            result = calculate(firstFraction, secondFraction, socketOperation);

            if (result.isNegative)
                printf("-");
            if (result.type == COMMON)
                printf("Result: %d/%d\n", result.firstPart, result.secondPart);
            else
                printf("Result: %d.%d\n", result.firstPart, result.secondPart);
        }
        else if (compare(firstFraction, secondFraction, socketOperation))
            puts("true");
        else
            puts("false");

        free(socketFirstFraction);
        free(socketOperation);
        free(socketSecondFraction);

        close(clientSocketFileDescriptor);
    }
    close(socketFileDescriptor);
    puts("The server stopped working");
    return 0;
}
