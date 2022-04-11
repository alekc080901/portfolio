//
// Created by alekc on 24.03.2021.
//

#include "structures.h"

#ifndef LAB3_USERINPUT_H
/*! \brief Input validation for natural number
 *
 * \param number Int pointer where the appropriate number will be loaded
 *
 *  \return Nothing
 */
void inputNat(int* number);

/*! \brief Input validation for natural number with zero
 *
 * \param number Int pointer where the appropriate number will be loaded
 *
 *  \return Nothing
 */
void inputNat0(int* number);

/*! \brief User string input of arbitrary length
 *
 * \param word The destination word where information will be putted
 *
 *  \return Nothing
 */
void inputString(char** word);

/*! \brief Checks if there is such name in the linked list
 *
 * \param list Linked list
 * \param name Searched name in the list
 *
 *  \return true or false
 */
bool checkName(linkedList list, char* name);

/*! \brief Displays whole linked list content.
 *
 *  \param list Linked list.
 *
 *  \return Nothing.
 */
void showAllInfo(linkedList list);

/*! \brief Displays linked list content only when the group has only males.
 *
 *  \param list Linked list.
 *
 *  \return Nothing.
 */
void showMalesInfo(linkedList list);

/*! \brief Displays linked list content only when the group has only females.
 *
 *  \param list Linked list.
 *
 *  \return Nothing.
 */
void showFemalesInfo(linkedList list);

/*! \brief Displays linked list content only when male and female number are equal.
 *
 *  \param list Linked list.
 *
 *  \return Nothing.
 */
void showEqualInfo(linkedList list);
#define LAB3_USERINPUT_H

#endif //LAB3_USERINPUT_H
