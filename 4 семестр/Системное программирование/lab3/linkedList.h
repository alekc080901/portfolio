//
// Created by alekc on 24.03.2021.
//

#include "structures.h"

#ifndef LAB3_LINKEDLIST_H

/*! \brief Checks if the string is a natural number
 *
 * \param string String that may be a number or not
 *
 *  \return true or false
 */
bool checkNat(char* string);

/*! \brief Checks if the string is a natural number or zero
 *
 * \param string String that may be a number or not
 *
 *  \return true or false
 */
bool checkNat0(char* string);

/*! \brief Pushes the node to the end of the linked list
 *
 *  \param list Linked list.
 *  \param info Information that will be loaded into the new node.
 *
 *  \return Nothing.
 */
void push(linkedList* list, group_t info);

/*! \brief Edit one field from the from the group in the list
 *
 *  \param list Linked list.
 *  \param name Name that is used for search node for change
 *  \param newField New value of one field of structure
 *
 *  \return Has the function worked properly.
 */
bool editGroupField(linkedList* list, char* name, metaVariable newField);

/*! \brief Removes the node from the linked list using its name.
 *
 *  \param list Linked list.
 *  \param name Name of group that will be deleted.
 *
 *  \return Nothing.
 */
void delete(linkedList* list, char* name);

/*! \brief Frees the memory of every node in linked list.
 *
 *  \param list Linked list.
 *
 *  \return Nothing.
 */
void freeList(linkedList* list);
#define LAB3_LINKEDLIST_H

#endif //LAB3_LINKEDLIST_H
