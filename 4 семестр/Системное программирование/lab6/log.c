/*! \file    log.c
 *  \brief   Working with log files.
 *
 *  \details Writes the information into log files.
 *
 *  \author Nikitin Alexander, KI19-17/1Á
 */

#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

/*! \brief Writes the information into the log file adding current time.
 *
 *  \param[in] logPath Path to the file to write
 *  \param[in] info Information to be written
 *
 *  \return Is the operation successful.
 */
void writeLog(char* logPath, char* info)
{
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    char* timeStr = asctime (timeinfo);
    timeStr[strlen(timeStr) - 1] = ':';

    int fd = open(logPath, O_WRONLY | O_CREAT | O_APPEND, 0660);
    write(fd, timeStr, strlen(timeStr));
    write(fd, "\n", 1);
    write(fd, info, strlen(info));
    write(fd, "\n", 1);
    fsync(fd);
    close(fd);
}