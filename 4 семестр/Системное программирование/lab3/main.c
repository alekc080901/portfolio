#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "userInput.h"
#include "linkedList.h"

int main()
{
    int userChoice;

    enum Case {addGroup = 1, editGroup, deleteGroup,  viewGroups, onlyMales, onlyFemales, malesEqualFemales, exitProg};

    linkedList groups = {NULL, NULL};

    do
    {
        printf("Input your choice:\n"
               "1. Add a new group.\n"
               "2. Change group info.\n"
               "3. Delete group.\n"
               "4. View all the groups.\n"
               "5. View only the groups with males.\n"
               "6. View only the groups with females.\n"
               "7. View only the groups where male number equals female number.\n"
               "8. Exit\n");
        inputNat(&userChoice);

        switch (userChoice)
        {

        case (addGroup):
        {
            group_t group;
            puts("Input the group name:");
            inputString(&group.name);
            puts("Input the number of students in group:");
            inputNat(&group.studentsNumber);
            puts("Input the number of females in group:");
            inputNat0(&group.femalesNumber);

            if (group.femalesNumber > group.studentsNumber)
            {
                puts("Number of females cannot be larger than number of students!");
                break;
            }

            push(&groups, group);
            break;
        }

        case (editGroup):
        {
            if (groups.head == NULL)
            {
                puts("The list is empty!");
                break;
            }

            char* searchName = NULL;
            metaVariable groupName;
            metaVariable groupStudentsNumber;
            metaVariable groupFemaleNumber;

            puts("Input the group name:");
            inputString(&searchName);

            if (!checkName(groups, searchName))
            {
                puts("This group does not exist!");
                break;
            }

            puts("Input new group name ('-' if remain old):");
            inputString(&groupName.var);
            groupName.metadata = "name";
            if (!editGroupField(&groups, searchName, groupName))
                puts("Recheck your input!");

            puts("Input new students number ('-' if remain old):");
            inputString(&groupStudentsNumber.var);
            groupStudentsNumber.metadata = "studentsNumber";
            if (!editGroupField(&groups, searchName, groupStudentsNumber))
                puts("Recheck your input!");

            puts("Input new females number ('-' if remain old):");
            inputString(&groupFemaleNumber.var);
            groupFemaleNumber.metadata = "femalesNumber";
            if (!editGroupField(&groups, searchName, groupFemaleNumber))
                puts("Recheck your input!");

            break;
        }

        case (deleteGroup):
        {
            char* searchName = NULL;

            if (groups.head == NULL)
            {
                puts("The list is empty.");
                break;
            }

            puts("Input the group name:");
            inputString(&searchName);

            if (!checkName(groups, searchName))
            {
                puts("This group does not exist!");
                break;
            }

            delete(&groups, searchName);
            break;
        }

        case (viewGroups):
        {
            if (groups.head == NULL)
            {
                puts("The list is empty.");
                break;
            }

            showAllInfo(groups);
            break;
        }

        case (onlyMales):
        {
            if (groups.head == NULL)
            {
                puts("The list is empty.");
                break;
            }

            showMalesInfo(groups);
            break;
        }

        case (onlyFemales):
        {
            if (groups.head == NULL)
            {
                puts("The list is empty.");
                break;
            }

            showFemalesInfo(groups);
            break;
        }

        case (malesEqualFemales):
        {
            if (groups.head == NULL)
            {
                puts("The list is empty.");
                break;
            }

            showEqualInfo(groups);
            break;
        }

        case (exitProg):
        {
            freeList(&groups);
            exit(0);
            break;
        }

        default:
        {
            printf("Input the choice from 1 to 6!\n");
            continue;
        }

        }

    }while (1);
    return 0;
}