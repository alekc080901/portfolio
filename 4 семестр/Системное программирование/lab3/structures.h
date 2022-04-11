//
// Created by alekc on 24.03.2021.
//

#ifndef LAB3_STRUCTURE_H
typedef struct _metaVariable
{
    char* metadata;
    char* var;
} metaVariable;

typedef struct _group
{
    char* name;
    int studentsNumber;
    int femalesNumber;
} group_t;

typedef struct _node
{
    group_t info;
    struct _node* next;
} node_t;

typedef struct _list
{
    node_t* head;
    node_t* tail;
} linkedList;
#define LAB3_STRUCTURE_H

#endif //LAB3_STRUCTURE_H
