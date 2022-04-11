/*! \file   parent.c
 *  \brief  Fork and execute child process
 *  \author Nikitin Alexander, KI19-17/1Á
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

/*! \brief Spawns a child process
 *
 *  \param program Name of the compiled program in the directory
 *  \param argList Additional arguments to run the program
 *  \return Child process id
 */
int spawn(char* program, char** argList)
{
    pid_t childPid;
    childPid = fork();
    if (childPid != 0)
        return childPid;
    else
    {
        execvp(program, argList);
        abort();
    }
}

int main()
{
    char *args[]={"./child", NULL};

    int childStatus;
    spawn(args[0], args);
    wait(&childStatus);
    if(WIFEXITED(childStatus))
        printf("The child process exited normally with code %d.\n", WEXITSTATUS(childStatus));
    else
        printf("The child process exited abnormally.\n");
    return 0;
}