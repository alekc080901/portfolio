#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "userInput.h"
#include "fileFunctions.h"

#define GROUP_SIZE 50

/*! \brief Input validation for natural number
 *
 * \param number Int pointer where the appropriate number will be loaded
 *
 *  \return Nothing
 */
void inputNat(int* number)
{
    while (!scanf("%d", number))
    {
        fflush(stdin);
        printf("Please, input correct information!\n");
    }
    if (*number <= 0)
    {
        printf("Please, enter natural number!\n");
        inputNat(number);
    }
}

/*! \brief Input validation for natural number with zero
 *
 * \param number Int pointer where the appropriate number will be loaded
 *
 *  \return Nothing
 */
void inputNat0(int* number)
{
    while (!scanf("%d", number))
    {
        fflush(stdin);
        printf("Please, input correct information!\n");
    }
    if (*number < 0)
    {
        printf("Please, enter natural number or 0!\n");
        inputNat(number);
    }
}

/*! \brief User string input of arbitrary length
 *
 * \param word The destination word where information will be putted
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
            if (count != 0)  // Обработка считывания единичного \n
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

/*! \brief Checks if the string is a natural number
 *
 * \param string String that may be a number or not
 *
 *  \return true or false
 */
int checkNat(char* string)
{
    for (int i = 0; string[i] != '\0'; i++)
        if (!isdigit(string[i]))
            return -1;

    if (strtol(string, NULL, 10) <= 0)
        return -1;
    return 0;
}

/*! \brief Checks if the string is a natural number or zero
 *
 * \param string String that may be a number or not
 *
 *  \return true or false
 */
int checkNat0(char* string)
{
    for (int i = 0; string[i] != '\0'; i++)
        if (!isdigit(string[i]))
            return -1;

    if (strtol(string, NULL, 10) < 0)
        return -1;

    return 0;
}

/*! \brief Inputs the group characteristics (name, students number and females number in group into file) and writes it
 * into the file
 *
 * \param fd File descriptor
 *
 *  \return Nothing
 */
void groupWrite(int fd)
{
    int studentsNumber;
    int femalesNumber;
    char* name;

    int string_size = getStringSize(GROUP_SIZE);
    char cutName[string_size];

    writeMeta(fd);

    puts("Input the group name:");
    inputString(&name);
    strncpy(cutName, name, string_size);

    puts("Input the number of students in group:");
    inputNat(&studentsNumber);

    puts("Input the number of females in group:");
    inputNat0(&femalesNumber);

    if (femalesNumber > studentsNumber)
    {
        puts("Number of females cannot be larger than number of students!");
        return;
    }

    writeInfo(fd, cutName, sizeof(char) * string_size);
    writeInfo(fd, &studentsNumber, sizeof(int));
    writeInfo(fd, &femalesNumber, sizeof(int));

    printf("Writing structure to file has been completed!\n\n");
    close(fd);
}

/*! \brief Inputs the name of group and deletes this group from the file
 *
 * \param fd File descriptor
 *
 *  \return Nothing
 */
void groupDelete(int fd)
{
    char* searchName = NULL;

    puts("Input the group name:");
    inputString(&searchName);

    int deleteGroupReturn = deleteGroup(fd, searchName);
    if (deleteGroupReturn != 0)
    {
        puts("This group does not exist!");
        return;
    }

    puts("The group has been deleted.\n");
}

/*! \brief Inputs the name of group and new characteristics ("-" if remain) and changes the information for this group
 *
 * \param fd File descriptor
 *
 *  \return Nothing
 */
void groupEdit(int fd)
{
    char* searchName = NULL;
    char* groupName;
    char* stringStudentsNumber;
    char* stringFemaleNumber;

    puts("Input the group name:");
    inputString(&searchName);

    if (seekToGroup(fd, searchName) != 0)
    {
        puts("This group does not exist!");
        return;
    }

    puts("Input new group name ('-' if remain old):");
    inputString(&groupName);
    if (strcmp(groupName, "-") != 0)
    {
        changeName(fd, searchName, groupName);
        strcpy(searchName, groupName);
    }

    puts("Input new students number ('-' if remain old):");
    inputString(&stringStudentsNumber);
    if (strcmp(stringStudentsNumber, "-") != 0 && checkNat(stringStudentsNumber) == 0)
    {
        int studentsNumber = strtol(stringStudentsNumber, NULL, 10);
        changeStudentsNumber(fd, searchName, studentsNumber);
    }

    puts("Input new females number ('-' if remain old):");
    inputString(&stringFemaleNumber);
    if (strcmp(stringFemaleNumber, "-") != 0 && checkNat0(stringFemaleNumber) == 0)
    {
        int femaleNumber = strtol(stringFemaleNumber, NULL, 10);
        if (femaleNumber > getStudentsNumber(fd, searchName))
        {
            puts("Number of females cannot be larger than number of students!");
            return;
        }

        changeFemalesNumber(fd, searchName, femaleNumber);
    }

    close(fd);
}

/*! \brief Outputs the information about all groups from the file
 *
 * \param fd File descriptor
 *
 *  \return Nothing
 */
void showAll(int fd)
{
    int meta;
    int studentsNumber;
    int femalesNumber;

    meta = readMeta(fd);
    char groupName[getStringSize(meta)];

    while (lseek(fd, 0, SEEK_CUR) < getFileSize(fd))
    {
        readInfo(fd, &groupName, sizeof(char) * getStringSize(meta));
        readInfo(fd, &studentsNumber, sizeof(int));
        readInfo(fd, &femalesNumber, sizeof(int));

        printf("The group %s has %d students and %d females\n\n", groupName, studentsNumber, femalesNumber);
    }

    close(fd);
}

/*! \brief Outputs the information about groups only with males from the file
 *
 * \param fd File descriptor
 *
 *  \return Nothing
 */
void showOnlyMales(int fd)
{
    int meta;
    int studentsNumber;
    int femalesNumber;

    meta = readMeta(fd);
    char groupName[getStringSize(meta)];

    while (lseek(fd, 0, SEEK_CUR) < getFileSize(fd))
    {
        readInfo(fd, &groupName, sizeof(char) * getStringSize(meta));
        readInfo(fd, &studentsNumber, sizeof(int));
        readInfo(fd, &femalesNumber, sizeof(int));

        if (femalesNumber == 0)
            printf("The group %s has %d students and %d females\n\n", groupName, studentsNumber, femalesNumber);
    }

    close(fd);
}

/*! \brief Outputs the information about groups only with an equal number of males and females from the file
 *
 * \param fd File descriptor
 *
 *  \return Nothing
 */
void showMalesEqualFemales(int fd)
{
    int meta;
    int studentsNumber;
    int femalesNumber;

    meta = readMeta(fd);
    char groupName[getStringSize(meta)];

    while (lseek(fd, 0, SEEK_CUR) < getFileSize(fd))
    {
        readInfo(fd, &groupName, sizeof(char) * getStringSize(meta));
        readInfo(fd, &studentsNumber, sizeof(int));
        readInfo(fd, &femalesNumber, sizeof(int));

        if (femalesNumber == studentsNumber - femalesNumber)
            printf("The group %s has %d students and %d females\n\n", groupName, studentsNumber, femalesNumber);
    }

    close(fd);
}

/*! \brief Inputs the path to the file and saves the data from the "groups" into it. If the file doesn't exist, creates
 * it
 *
 *  \return Nothing
 */
void save()
{
    char* filePath;
    puts("Input the path where the file will be saved:");
    inputString(&filePath);

    int fd1 = open("groups", O_RDONLY);
    int fd2 = open(filePath, O_CREAT | O_WRONLY);

    if (checkFileExists("groups") == 0 && checkFileEmpty(fd1) == 0)
        saveFile(fd2, fd1);
}

/*! \brief Inputs the path to the file and loads the data from this file into the "groups" file.
 *
 *  \return Nothing
 */
void load()
{
    char* filePath;
    puts("Input the path where the source file will is located:");
    inputString(&filePath);

    int fd1 = open("groups", O_CREAT | O_WRONLY);
    int fd2 = open(filePath, O_RDONLY);

    if (checkFileExists(filePath) == 0 && checkFileEmpty(fd2) == 0)
        saveFile(fd1, fd2);
}