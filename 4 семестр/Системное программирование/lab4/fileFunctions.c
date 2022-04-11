#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "fileFunctions.h"

#define GROUP_SIZE 50

/*! \brief Checks whether the file from the path exists or not.
 *
 * \param path Path to the file. The file can be local
 *
 *  \return 0 if exists else -1
 */
int checkFileExists(char* path)
{
    if (access(path, F_OK) != 0)
    {
        puts("The file must exist!");
        return -1;
    }

    return 0;
}

/*! \brief Checks whether the file from the path empty or not.
 *
 * \param fd File descriptor
 *
 *  \return 0 if not empty else -1
 */
int checkFileEmpty(int fd)
{
    if (getFileSize(fd) == 0)
    {
        puts("The file must not be empty!");
        return -1;
    }

    return 0;
}

/*! \brief Calculates the string size (length) that will be loaded into file
 *
 * \param groupSize The size of one group in a file
 *
 *  \return String size
 */
int getStringSize(int groupSize)
{
    return groupSize - 2 * sizeof(int);
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
        perror("Getting file info went wrong.");
    }

    return info.st_size;
}

/*! \brief Writes information in bytes from buffer into file. Similar to the function write() from <unistd.h>
 * but also outputs errors
 *
 * \param fd File descriptor
 * \param info Variable with information that will be loaded into file
 * \param size The number of bytes that will be loaded into file
 *
 *  \return -1 if something went wrong. Else the number of bytes that have been successfully loaded into file
 */
int writeInfo(int fd, void* info, size_t size)
{
    int writeReturn = write(fd, info, size);

    if (writeReturn == -1)
    {
        perror("Write into file went wrong.");
        return -1;
    }

    if (writeReturn == 0)
    {
        perror("Nothing was written.");
        return -1;
    }

    return writeReturn;
}

/*! \brief Writes meta information (size of one group) into beginning of the file (if the file is empty)
 *
 * \param fd File descriptor
 *
 *  \return Nothing
 */
void writeMeta(int fd)
{
    lseek(fd, 0, SEEK_SET);

    int size = GROUP_SIZE;

    if (getFileSize(fd) == 0)
    {
        writeInfo(fd, &size, sizeof(int));
    }
}

/*! \brief Reads information from the file. Similar to the function read() from <unistd.h>
 * but also outputs errors
 *
 * \param fd File descriptor
 * \param info Variable with information that will be loaded into file
 * \param size The number of bytes that will be loaded into file
 *
 *  \return -1 if something went wrong. Else the number of bytes that have been successfully read from file
 */
int readInfo(int fd, void* info, size_t size)
{
    int readReturn = read(fd, info, size);

    if (readReturn == -1)
    {
        perror("Read error");
        return -1;
    }

    if (readReturn == 0)
    {
        perror("Nothing has been read.");
        return -1;
    }

    return readReturn;
}

/*! \brief Reads meta information (size of one group) from the file
 *
 * \param fd File descriptor
 *
 *  \return Nothing
 */
int readMeta(int fd)
{
    lseek(fd, 0, SEEK_SET);

    int metaSize;

    readInfo(fd, &metaSize, sizeof(int));
    return metaSize;
}

/*! \brief Deletes the file from the working directory
 *
 * \param filename The name of file
 *
 *  \return Nothing
 */
void deleteFile(char* filename)
{
    int removeReturn = remove(filename);
    if (removeReturn != 0)
    {
        perror("File delete error");
        puts("");
        return;
    }
}

/*! \brief Deletes information about one group from the file. The group is identified by name
 *
 * \param fd File descriptor
 * \param groupName The name of a group
 *
 *  \return Is there such a group (0) or not (-1)
 */
int deleteGroup(int fd, char* groupName)
{
    int fd1 = open("groups1", O_CREAT | O_WRONLY);
    writeMeta(fd1);

    int meta = readMeta(fd);
    char currentGroupName[getStringSize(meta)];
    int currentStudentsNumber;
    int currentFemalesNumber;

    int isFound = -1;
    while (lseek(fd, 0, SEEK_CUR) < getFileSize(fd))
    {
        readInfo(fd, &currentGroupName, sizeof(char) * getStringSize(meta));
        readInfo(fd, &currentStudentsNumber, sizeof(int));
        readInfo(fd, &currentFemalesNumber, sizeof(int));

        if (strcmp(groupName, currentGroupName) == 0)
        {
            isFound = 0;
            continue;
        }

        writeInfo(fd1, &currentGroupName, sizeof(char) * getStringSize(meta));
        writeInfo(fd1, &currentStudentsNumber, sizeof(int));
        writeInfo(fd1, &currentFemalesNumber, sizeof(int));
    }

    close(fd);
    close(fd1);
    deleteFile("groups");
    int renameReturn = rename("groups1", "groups");
    if (renameReturn != 0)
    {
        perror("Rename error");
        puts("");
    }
    return isFound;
}

/*! \brief Moves the pointer in the file to one group
 *
 * \param fd File descriptor
 * \param groupName The name of a group
 *
 *  \return Is there such a group (0) or not (-1)
 */
int seekToGroup(int fd, char* groupName)
{
    lseek(fd, 0, SEEK_SET);

    int meta = readMeta(fd);
    char currentGroupName[getStringSize(meta)];

    while (lseek(fd, 0, SEEK_CUR) < getFileSize(fd))
    {
        readInfo(fd, &currentGroupName, sizeof(char) * getStringSize(meta));
        if (strcmp(groupName, currentGroupName) == 0)
        {
            lseek(fd, -sizeof(char) * getStringSize(meta), SEEK_CUR);
            return 0;
        }
        lseek(fd, sizeof(int) * 2, SEEK_CUR);
    }

    return -1;
}

/*! \brief Changes the name of one group in the file
 *
 * \param fd File descriptor
 * \param groupName The name of a group where a new name will be
 * \param newGroupName A new name of the group
 *
 *  \return Is there such a group (0) or not (-1)
 */
int changeName(int fd, char* groupName, char* newGroupName)
{
    int meta = readMeta(fd);
    int existError = seekToGroup(fd, groupName);
    if (existError != 0)
        return -1;

    writeInfo(fd, newGroupName, sizeof(char) * getStringSize(meta));

    return 0;
}

/*! \brief Changes the students number of one group in the file
 *
 * \param fd File descriptor
 * \param groupName The name of a group where a new students number will be
 * \param newStudentsNumber A new students number of the group
 *
 *  \return Is there such a group (0) or not (-1)
 */
int changeStudentsNumber(int fd, char* groupName, int newStudentsNumber)
{
    int meta = readMeta(fd);
    int existError = seekToGroup(fd, groupName);
    if (existError != 0)
        return -1;

    lseek(fd, sizeof(char) * getStringSize(meta), SEEK_CUR);
    writeInfo(fd, &newStudentsNumber, sizeof(int));

    return 0;
}

/*! \brief Changes the females number of one group in the file
 *
 * \param fd File descriptor
 * \param groupName The name of a group where a new females number will be
 * \param newFemalesNumber A new females number of the group
 *
 *  \return Is there such a group (0) or not (-1)
 */
int changeFemalesNumber(int fd, char* groupName, int newFemalesNumber)
{
    int meta = readMeta(fd);
    int existError = seekToGroup(fd, groupName);
    if (existError != 0)
        return -1;

    lseek(fd, sizeof(char) * getStringSize(meta) + sizeof(int), SEEK_CUR);
    writeInfo(fd, &newFemalesNumber, sizeof(int));

    return 0;
}

/*! \brief Returns a students number from the group in file
 *
 * \param fd File descriptor
 * \param groupName The name of a group with the students number
 *
 *  \return Student number of the group or -1 if there is no such group in the file
 */
int getStudentsNumber(int fd, char* groupName)
{
    lseek(fd, 0, SEEK_SET);

    int meta = readMeta(fd);
    char currentGroupName[getStringSize(meta)];

    int studentsNumber;
    while (lseek(fd, 0, SEEK_CUR) < getFileSize(fd))
    {
        readInfo(fd, &currentGroupName, sizeof(char) * getStringSize(meta));
        if (strcmp(groupName, currentGroupName) == 0)
        {
            readInfo(fd, &studentsNumber, sizeof(int));
            return studentsNumber;
        }
        lseek(fd, sizeof(int) * 2, SEEK_CUR);
    }
    return -1;
}

/*! \brief Returns a students number from the group in file
 *
 * \param fdDest File descriptor of the file where the data will be loaded
 * \param fdSource ile descriptor of the file where the data is kept
 *
 *  \return Nothing
 */
void saveFile(int fdDest, int fdSource)
{
    lseek(fdDest, 0, SEEK_SET);
    lseek(fdSource, 0, SEEK_SET);

    int meta = readMeta(fdSource);
    writeMeta(fdDest);

    char groupName[getStringSize(meta)];
    int studentsNumber;
    int femalesNumber;
    while (lseek(fdSource, 0, SEEK_CUR) < getFileSize(fdSource))
    {
        readInfo(fdSource, &groupName, sizeof(char) * getStringSize(meta));
        readInfo(fdSource, &studentsNumber, sizeof(int));
        readInfo(fdSource, &femalesNumber, sizeof(int));

        writeInfo(fdDest, &groupName, sizeof(char) * getStringSize(meta));
        writeInfo(fdDest, &studentsNumber, sizeof(int));
        writeInfo(fdDest, &femalesNumber, sizeof(int));
    }

    close(fdSource);
    close(fdDest);
}
