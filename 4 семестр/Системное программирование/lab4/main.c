#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "userInput.h"
#include "fileFunctions.h"

/*! \brief The main function.
 *
 *  \return Nothing
 */
int main()
{
    int userChoice;

    enum Case
    {
        addGroup = 1, editGroup, deleteGroup, fileDelete, viewGroups, onlyMales, malesEqualFemales,
        saveFile, loadFile, exitProg
    };

    do
    {
        printf("Input your choice:\n"
               "1. Add a new group.\n"
               "2. Change group info.\n"
               "3. Delete group.\n"
               "4. Delete groups file.\n"
               "5. View all the groups.\n"
               "6. View only the groups with males.\n"
               "7. View only the groups with females.\n"
               "8. Save into file.\n"
               "9. Load from file.\n"
               "10. Exit\n");
        inputNat(&userChoice);

        switch (userChoice)
        {

        case (addGroup):
        {
            int fd = open("groups", O_CREAT | O_APPEND | O_WRONLY);
            groupWrite(fd);
            break;
        }

        case (editGroup):
        {
            int fd = open("groups", O_CREAT | O_RDWR);
            if (checkFileExists("groups") != 0 || checkFileEmpty(fd) != 0)
                break;

            groupEdit(fd);
            break;
        }

        case (deleteGroup):
        {
            int fd = open("groups", O_RDONLY);
            if (checkFileExists("groups") != 0 || checkFileEmpty(fd) != 0)
                break;

            groupDelete(fd);
            break;
        }

        case (fileDelete):
        {
            deleteFile("groups");
            puts("The file has been successfully deleted.\n");
            break;
        }

        case (viewGroups):
        {
            int fd = open("groups", O_RDONLY);
            if (checkFileExists("groups") != 0 || checkFileEmpty(fd) != 0)
                break;

            showAll(fd);
            break;
        }

        case (onlyMales):
        {
            int fd = open("groups", O_RDONLY);
            if (checkFileExists("groups") != 0 || checkFileEmpty(fd) != 0)
                break;

            showOnlyMales(fd);
            break;
        }

        case (malesEqualFemales):
        {
            int fd = open("groups", O_RDONLY);
            if (checkFileExists("groups") != 0 || checkFileEmpty(fd) != 0)
                break;

            showMalesEqualFemales(fd);
            break;
        }

        case (saveFile):
        {
            save();
            break;
        }

        case (loadFile):
        {
            load();
            break;
        }

        case (exitProg):
        {
            exit(0);
            break;
        }

        default:
        {
            printf("Input the choice from 1 to 10!\n");
            continue;
        }

        }

    } while (1);
    return 0;
}