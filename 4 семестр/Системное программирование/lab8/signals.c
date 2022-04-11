/*! \file    signals.c
 *  \brief   Working with signals.
 *
 *  \details Have functions of processing different signals and setting out the timer for program existence.
 *
 *  \author Nikitin Alexander, KI19-17/1Á
 */

#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "signals.h"
#include "log.h"

const char* g_errorLogPath = "./logs/errors.log";

/*! \brief Crashes handler.
 *
 *  \param   signo The number of signal to handle
 *
 *  \return Nothing
 */
void crashHandler(int signo)
{
    remove(SERVER_UNIQUE_FILE_PATH);
    if (signo == SIGABRT)
    {
        printf("Abort has happened!\n");
        writeLog((char*) g_errorLogPath, "Abort has happened.");
    }
    else if (signo == SIGFPE)
    {
        printf("Arithmetical operation error has happened!\n");
        writeLog((char*) g_errorLogPath, "Arithmetical operation error has happened.");
    }
    else if (signo == SIGBUS)
    {
        printf("Hardware error has happened!\n");
        writeLog((char*) g_errorLogPath, "Hardware error has happened.");
    }
    else if (signo == SIGILL)
    {
        printf("Not permitted instruction error has happened!\n");
        writeLog((char*) g_errorLogPath, "Not permitted instruction error has happened.");
    }
    else if (signo == SIGSEGV)
    {
        printf("Segmentation error has happened!\n");
        writeLog((char*) g_errorLogPath, "Segmentation error has happened.");
    }
    else if (signo == SIGSYS)
    {
        printf("Impermissible system call error has happened!\n");
        writeLog((char*) g_errorLogPath, "Impermissible system call error has happened.");
    }
    else if (signo == SIGTRAP)
    {
        printf("Breakpoint has been reached!\n");
        writeLog((char*) g_errorLogPath, "Breakpoint has been reached.");
    }
    else if (signo == SIGXCPU)
    {
        printf("Process resources limit has been exceeded!\n");
        writeLog((char*) g_errorLogPath, "Process resources limit has been exceeded.");
    }
    else if (signo == SIGXFSZ)
    {
        printf("File resources limit has been exceeded!\n");
        writeLog((char*) g_errorLogPath, "File resources limit has been exceeded.");
    }
    else
    {
        fprintf(stderr, "Unexpected signal!\n");
        exit(ERROR_CODE);
    }
    exit(SUCCESS_CODE);
}

/*! \brief Handles handle function to interrupt signals.
 *
 *  \return Nothing
 */
void interruptHandler(int signo)
{
    if (signo == SIGINT)
    {
        puts("\nThe server is shutting down by interrupting.");
        remove(SERVER_UNIQUE_FILE_PATH);
        exit(SUCCESS_CODE);
    }
    if (signo == SIGTERM)
    {
        puts("\nThe server is shutting down by SIGTERM.");
        remove(SERVER_UNIQUE_FILE_PATH);
        exit(SUCCESS_CODE);
    }
}

/*! \brief Handles handle function to all crash signals.
 *
 *  \return Nothing
 */
void registerHandler()
{
    if (signal(SIGABRT, crashHandler) == SIG_ERR)
    {
        fprintf(stderr, "It's impossible to handle SIGABRT!\n");
        writeLog((char*) g_errorLogPath, "It's impossible to handle SIGABRT.");
        exit (ERROR_CODE);
    }
    if (signal(SIGFPE, crashHandler) == SIG_ERR)
    {
        fprintf(stderr, "It's impossible to handle SIGFPE!\n");
        writeLog((char*) g_errorLogPath, "It's impossible to handle SIGFPE.");
        exit (ERROR_CODE);
    }
    if (signal(SIGBUS, crashHandler) == SIG_ERR)
    {
        fprintf(stderr, "It's impossible to handle SIGBUS!\n");
        writeLog((char*) g_errorLogPath, "It's impossible to handle SIGBUS.");
        exit (ERROR_CODE);
    }
    if (signal(SIGILL, crashHandler) == SIG_ERR)
    {
        fprintf(stderr, "It's impossible to handle SIGILL!\n");
        writeLog((char*) g_errorLogPath, "It's impossible to handle SIGILL.");
        exit (ERROR_CODE);
    }
    if (signal(SIGSEGV, crashHandler) == SIG_ERR)
    {
        fprintf(stderr, "It's impossible to handle SIGSEGV!\n");
        writeLog((char*) g_errorLogPath, "It's impossible to handle SIGSEGV.");
        exit (ERROR_CODE);
    }
    if (signal(SIGSYS, crashHandler) == SIG_ERR)
    {
        fprintf(stderr, "It's impossible to handle SIGSYS!\n");
        writeLog((char*) g_errorLogPath, "It's impossible to handle SIGSYS.");
        exit (ERROR_CODE);
    }
    if (signal(SIGTRAP, crashHandler) == SIG_ERR)
    {
        fprintf(stderr, "It's impossible to handle SIGTRAP!\n");
        writeLog((char*) g_errorLogPath, "It's impossible to handle SIGTRAP.");
        exit (ERROR_CODE);
    }
    if (signal(SIGXCPU, crashHandler) == SIG_ERR)
    {
        fprintf(stderr, "It's impossible to handle SIGXCPU!\n");
        writeLog((char*) g_errorLogPath, "It's impossible to handle SIGXCPU.");
        exit (ERROR_CODE);
    }
    if (signal(SIGXFSZ, crashHandler) == SIG_ERR)
    {
        fprintf(stderr, "It's impossible to handle SIGXFSZ!\n");
        writeLog((char*) g_errorLogPath, "It's impossible to handle SIGXFSZ.");
        exit (ERROR_CODE);
    }
    if (signal(SIGINT, interruptHandler) == SIG_ERR)
    {
        fprintf(stderr, "It's impossible to handle SIGINT!\n");
        writeLog((char*) g_errorLogPath, "It's impossible to handle SIGINT.");
        exit (ERROR_CODE);
    }
    if (signal(SIGTERM, interruptHandler) == SIG_ERR)
    {
        fprintf(stderr, "It's impossible to handle SIGTERM!\n");
        writeLog((char*) g_errorLogPath, "It's impossible to handle SIGTERM.");
        exit (ERROR_CODE);
    }
}

/*! \brief Server timer handler.
 *
 *  \param signo The number of signal to handle
 *
 *  \return Nothing
 */
void serverExpirationHandler(int signum)
{
    remove(SERVER_UNIQUE_FILE_PATH);
    puts("Server is shutting down.");
    exit(EXPIRATION_EXIT_CODE);
}

/*! \brief Client timer handler.
 *
 *  \param signo The number of signal to handle
 *
 *  \return Nothing
 */
void clientExpirationHandler(int signum)
{
    puts("Client has stopped working.");
    exit(EXPIRATION_EXIT_CODE);
}

/*! \brief Sets a time to a server and shuts down the server after the expiration of it.
 *
 *  \param sec The time for server to survive
 *
 *  \return Nothing
 */
void setTimerServer(int sec)
{
    struct sigaction sa;
    struct itimerval timer;

    memset (&sa, 0, sizeof (sa));
    sa.sa_handler = &serverExpirationHandler;
    sigaction (SIGALRM, &sa, NULL);

    timer.it_value.tv_sec = sec;
    timer.it_value.tv_usec = SERVER_INACTIVITY_TIME_MS;

    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);
}

/*! \brief Sets a time to a client and kills him after the expiration of it.
 *
 *  \param sec The time for client to survive
 *
 *  \return Nothing
 */
void setTimerClient(int sec)
{
    struct sigaction sa;
    struct itimerval timer;

    memset (&sa, 0, sizeof (sa));
    sa.sa_handler = &clientExpirationHandler;
    sigaction (SIGALRM, &sa, NULL);

    timer.it_value.tv_sec = sec;
    timer.it_value.tv_usec = CLIENT_INACTIVITY_TIME_MS;

    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);
}
