#ifndef LAB3_USERINPUT_H

void inputNat(int* number);

void inputNat0(int* number);

void inputString(char** word);

int checkNat(char* string);

int checkNat0(char* string);

void groupWrite(int fd);

void groupDelete(int fd);

void groupEdit(int fd);

void showAll(int fd);

void showOnlyMales(int fd);

void showMalesEqualFemales(int fd);

void save();

void load();

#define LAB3_USERINPUT_H

#endif //LAB3_USERINPUT_H
