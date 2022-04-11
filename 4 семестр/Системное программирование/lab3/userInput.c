#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "userInput.h"

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

void inputString(char** word)
{
    int count = 0;
    char inputChar = 0;

    fflush(stdin);

    *word = NULL;
    while(1)
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
            if (word == NULL)
                perror("Realloc has returned a NULL pointer");

            (*word)[count] = inputChar;
            count++;
        }
    }
    (*word)[count] = '\0';
}

bool checkName(linkedList list, char* name)
{
    for (node_t* i = list.head; i != NULL; i = i->next)
        if (strcmp(i->info.name, name) == 0)
            return true;
    return false;
}

void showAllInfo(linkedList list)
{
    for (node_t* i = list.head; i != NULL; i = i->next)
    {
        printf("The group %s has %d students and %d females.\n", i->info.name, i->info.studentsNumber,
               i->info.femalesNumber);
    }
}

void showMalesInfo(linkedList list)
{
    for (node_t* i = list.head; i != NULL; i = i->next)
    {
        if (i->info.femalesNumber == 0)
            printf("The group %s has %d students and %d females.\n", i->info.name, i->info.studentsNumber,
                   i->info.femalesNumber);
    }
}

void showFemalesInfo(linkedList list)
{
    for (node_t* i = list.head; i != NULL; i = i->next)
    {
        if (i->info.femalesNumber == i->info.studentsNumber)
            printf("The group %s has %d students and %d females.\n", i->info.name, i->info.studentsNumber,
                   i->info.femalesNumber);
    }
}

void showEqualInfo(linkedList list)
{
    for (node_t* i = list.head; i != NULL; i = i->next)
    {
        if (i->info.femalesNumber == i->info.studentsNumber - i->info.femalesNumber)
            printf("The group %s has %d students and %d females.\n", i->info.name, i->info.studentsNumber,
                   i->info.femalesNumber);
    }
}
