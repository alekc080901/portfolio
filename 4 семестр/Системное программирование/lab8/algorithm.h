#ifndef INC_1_ALGORITHM_H
#define COMMON 1
#define DECIMAL 0
#define MAX_DECIMAL_PART_LENGTH 2

typedef struct arrayInfo
{
    int* array;
    int length;
} arrayInfo_t;

struct fractionParts
{
    int firstPart;
    int secondPart;
    int isNegative;
    int isWrong;
};

typedef struct fractionInfo
{
    int firstPart;
    int secondPart;
    int type;
    int isNegative;
    int isWrong;
} fractionInfo_t;

bool checkInt(char* string);

struct fractionParts splitFraction(char* string, int pos);

fractionInfo_t makeIntoFraction(char* fractionString);

int calculateHighestPower(int number);

int calculateHighestNegativePower(double number);

arrayInfo_t findSimpleDividers(int number);

arrayInfo_t subtractArrays(arrayInfo_t minuend, arrayInfo_t subtrahend);

int findLCM(int number1, int number2);

int findGCD(int number1, int number2);

void reduceFraction(fractionInfo_t* fraction);

double toDouble(fractionInfo_t fraction);

fractionInfo_t calculate(fractionInfo_t fraction1, fractionInfo_t fraction2, char* operation);

int compare(fractionInfo_t fraction1, fractionInfo_t fraction2, char* operation);

#define INC_1_ALGORITHM_H

#endif //INC_1_ALGORITHM_H
