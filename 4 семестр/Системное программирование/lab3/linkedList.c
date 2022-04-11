#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "linkedList.h"

bool checkNat(char* string)
{
    for (int i = 0; string[i] != '\0'; i++)
        if (!isdigit(string[i]))
            return false;

    if (strtol(string, NULL, 10) <= 0)
        return false;

    return true;
}

bool checkNat0(char* string)
{
    for (int i = 0; string[i] != '\0'; i++)
        if (!isdigit(string[i]))
            return false;

    if (strtol(string, NULL, 10) < 0)
        return false;

    return true;
}

void push(linkedList* list, group_t info)
{
    node_t* node = (node_t*) malloc(sizeof(node_t));
    if (node == NULL)
        perror("Malloc has returned a NULL pointer");

    node->next = NULL;

    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {

        list->tail->next = node;
        list->tail = node;
    }

    node->info = info;
}

bool editGroupField(linkedList* list, char* name, metaVariable newField)
{
    if (strcmp(newField.var, "-") == 0)
    {
        return true;
    }

    for (node_t* i = list->head; i != NULL; i = i->next)
    {
        if (strcmp(i->info.name, name) == 0)
            if (strcmp(newField.metadata, "name") == 0)
                i->info.name = newField.var;
            else if ((strcmp(newField.metadata, "studentsNumber") == 0) && (checkNat(newField.var)))
            {
                i->info.studentsNumber = strtol(newField.var, NULL, 10);
            }
            else if ((strcmp(newField.metadata, "femalesNumber") == 0) && (checkNat0(newField.var))
                     && (strtol(newField.var, NULL, 10) <= i->info.studentsNumber))
            {
                i->info.femalesNumber = strtol(newField.var, NULL, 10);
            }
            else
                return false;
    }
    return true;
}

void delete(linkedList* list, char* name)
{
    if (list->head == NULL)
        return;

    if (list->head == list->tail)
    {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        return;
    }

    node_t* tmp = NULL;
    if (strcmp(list->head->info.name, name) == 0)
    {
        tmp = list->head;
        list->head = list->head->next;
    }
    else
    {
        for (node_t* i = list->head; i->next != NULL; i = i->next)
            if (strcmp(i->next->info.name, name) == 0)
            {
                tmp = i->next;
                i->next = i->next->next;

                break;
            }
    }
    free(tmp->info.name);
    free(tmp);
}

void freeList(linkedList* list)
{
    node_t* tmp = NULL;
    while (list->head != NULL)
    {
        tmp = list->head;
        list->head = list->head->next;
        free(tmp);
    }
}
