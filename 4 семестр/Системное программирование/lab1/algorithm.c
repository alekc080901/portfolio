/*! \file   algorithm.c
 *  \brief  Fraction calculation and comparison
 *  \author Nikitin Alexander, KI19-17/1Б
 */

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
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

/*! \brief Inputs the string from user console into the variable
 *
 *  \param[out] word String variable of arbitrary length
 *
 *  \return Nothing
 */

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
            break;
        else
        {
            *word = realloc(*word, count + 1);
            (*word)[count] = inputChar;
            count++;
        }
    }
    (*word)[count] = '\0';
}

/*! \brief Checks if the string contains only digits
 *
 *  \param[in] string Numeric or non-numeric string
 *
 *  \return Is the string contains only digits or not (TRUE or FALSE)
 */

int checkInt(char* string)
{
    char* intChars = "0123456789";

    for (int i = 0; i < strlen(string); i++)
    {
        // Проверка минуса перед числом
        if (i == 0 && string[i] == '-')
            continue;

        if (strchr(intChars, string[i]) == NULL)
            return FALSE;
    }

    return TRUE;
}

/*! \brief Divides fraction in two parts and returns both of the values. First part is numeric part, second part is
 *  fractional part. Both are integers.
 *
 *  \param[in] string Source fraction
 *  \param[in] pos Position of separator ('.' or '/')
 *
 *  \return First and second numbers of fraction
 */

struct fractionParts splitFraction(char* string, int pos)
{
    struct fractionParts output;

    char* firstPart = NULL;
    char* secondPart = NULL;

    int firstNumber;
    int secondNumber;

    char* pEnd = NULL;

    if (pos <= 0 || pos > strlen(string))
    {
        output.isWrong = TRUE;
        return output;
    }

    // Срез целой части
    for (int i = 0; i < pos; i++)
    {
        firstPart = realloc(firstPart, i + 1);
        firstPart[i] = string[i];
    }
    firstPart[pos] = '\0';

    // Срез дробной части
    for (int i = pos + 1, j = 0; i < strlen(string); i++, j++)
    {
        secondPart = realloc(secondPart, j + 1);
        secondPart[j] = string[i];
    }
    secondPart[strlen(string) - pos - 1] = '\0';

    if (!checkInt(firstPart) || !checkInt(secondPart))
    {
        output.isWrong = TRUE;
        return output;
    }

    if (firstPart[0] == '-')
        output.isNegative = TRUE;
    else
        output.isNegative = FALSE;

    firstNumber = abs(strtol(firstPart, &pEnd, 10));
    secondNumber = abs(strtol(secondPart, &pEnd, 10));

    output.firstPart = firstNumber;
    output.secondPart = secondNumber;
    output.isWrong = FALSE;

    return output;
}

/*! \brief Tries to transform string into fractionString.
 *
 *  \param[in] fractionString Potential fractionString (X.X or X/X)
 *
 *  \return All essential information about fraction (if fraction.isWrong == FALSE)
 */

fractionInfo_t makeIntoFraction(char* fractionString)
{
    int posSeparator;

    char fractionSeparator;
    char fractionSeparatorString[2];

    struct fractionParts fraction;
    fractionInfo_t convertedFraction;

    fractionSeparator = strpbrk(fractionString, "/,.")[0];
    fractionSeparatorString[0] = fractionSeparator;
    posSeparator = strcspn(fractionString, fractionSeparatorString) + 1;

    fraction = splitFraction(fractionString, posSeparator - 1);

    if (fraction.isWrong || fraction.secondPart == 0)
    {
        convertedFraction.isWrong = TRUE;
        return convertedFraction;
    }

    // Заполнение информации о дроби
    convertedFraction.firstPart = fraction.firstPart;
    convertedFraction.secondPart = fraction.secondPart;
    convertedFraction.isNegative = fraction.isNegative;

    switch (fractionSeparator)
    {
        case '/':
        {
            convertedFraction.type = COMMON;
            convertedFraction.isWrong = FALSE;
            return convertedFraction;
        }

        case ',':
        case '.':
        {
            convertedFraction.type = DECIMAL;
            convertedFraction.isWrong = FALSE;
            return convertedFraction;
        }
        default:
        {
            convertedFraction.isWrong = TRUE;
            return convertedFraction;
        }
    }
}

/*! \brief Calculates the highest power of the number. For example, 1274 = 1 * 10^3 + 2 * 10^2 + 7 * 10^1 + 4 * 10^0.
 * So, the highest power (10^3) is 4.
 *
 *  \param[in] number Source number
 *
 *  \return The highest power
 */

int calculateHighestPower(int number)
{
    int power = 0;

    while (abs(number) > 0)
    {
        number /= 10;
        power++;
    }
    return power;
}

/*! \brief Calculates the highest negative power of the decimal number. For example, 12.74 = 1 * 10^1 + 2 * 10^0
 * + 7 * 10^-1 + 4 * 10^-2. So, the highest negative power (10^-2) is -2.
 *
 *  \param[in] number Source number
 *
 *  \return The highest negative power. Maximum value is MAX_DECIMAL_PART_LENGTH.
 */

int calculateHighestNegativePower(double number)
{
    int power = 0;
    while ((number - (int) number) != 0 && power <= MAX_DECIMAL_PART_LENGTH)
    {
        number *= 10;
        power++;
    }

    return power;
}

/*! \brief Checks if the operation type is supportable in the program.
 * List of operations: ("+", "-", "*", "/", "<", ">", "=", "!=", ">=", "<=")
 *
 *  \param[in] operation Operation string
 *
 *  \return If the operator is appropriate (TRUE or FALSE)
 */

int checkOperation(char* operation)
{
    char allOperations[10][3] = {"+", "-", "*", "/", "<", ">", "=", "!=", ">=", "<="};

    for (int i = 0; i < sizeof(allOperations) / sizeof(*allOperations); i++)
        if (strcmp(allOperations[i], operation) == 0)
            return TRUE;
    return FALSE;
}

/*! \brief Finds and returns simple dividers of the number. For example, simple dividers of 60 are 2, 2, 3, 5.
 *
 *  \param[in] number Positive integer number
 *
 *  \return Simple dividers of a number
 */

arrayInfo_t findSimpleDividers(int number)
{
    arrayInfo_t dividers;
    int length = 0;
    int i = 2;
    int j = 0;

    int numberCopy = number;

    while (numberCopy > 1)
    {
        while (numberCopy % i == 0)
        {
            numberCopy /= i;
            length++;
        }
        i++;
    }

    int* dividersArray = (int*) malloc(length * sizeof(int));

    i = 2;
    numberCopy = number;
    while (numberCopy > 1)
    {
        while (numberCopy % i == 0)
        {
            numberCopy /= i;
            dividersArray[j] = i;
            j++;
        }
        i++;
    }
    dividers.array = dividersArray;
    dividers.length = length;

    return dividers;
}

/*! \brief Subtract one array from another and returns the result. For example, (3, 4, 2, 6, 2) - (2, 6) = (3, 4, 2)
 *
 *  \param[in] minuend The minuend array
 *  \param[in] subtrahend The subtrahend array
 *
 *  \return The residual array
 */

arrayInfo_t subtractArrays(arrayInfo_t minuend, arrayInfo_t subtrahend)
{
    arrayInfo_t residual;

    if (subtrahend.length == 0)
        return  minuend;

    if (minuend.length == 0)
    {
        residual.array = NULL;
        residual.length = 0;
        return residual;
    }

    int count = 0;

    // Вспомогательный массив для определения, какие элементы удалять
    int minuendIndexes[minuend.length];
    for (int i = 0; i < minuend.length; i++)
    {
        minuendIndexes[i] = i;
    }

    for (int i = 0; i < subtrahend.length; i++)
    {
        for (int j = 0; j < minuend.length; j++)
        {
            if ((minuend.array[j] == subtrahend.array[i]) && (minuendIndexes[j] != -1))
            {
                minuendIndexes[j] = -1;
                count++;
                break;
            }
        }
    }

    int* residualArray = (int*) malloc(count * sizeof(int));

    count = 0;
    for (int i = 0; i < minuend.length; i++)
        if (minuendIndexes[i] != -1)
        {
            residualArray[count] = minuend.array[i];
            count++;
        }

    residual.array = residualArray;
    residual.length = count;

    return residual;
}

/*! \brief Finds least common multiple of two numbers.
 *
 *  \param[in] number1 First number of LCM
 *  \param[in] number2 Second number of LCM
 *
 *  \return Least common multiple
 */

int findLCM(int number1, int number2)
{
    arrayInfo_t dividers1 = findSimpleDividers(number1);

    arrayInfo_t dividers2 = findSimpleDividers(number2);
    arrayInfo_t remainingDividers = subtractArrays(dividers2, dividers1);
    int LCM = 1;

    for (int i = 0; i < dividers1.length; i++)
        LCM *= dividers1.array[i];

    // Домножаю только неповторяющиеся значения
    for (int i = 0; i < remainingDividers.length; i++)
    {
        LCM *= remainingDividers.array[i];
    }

    return LCM;
}

/*! \brief Finds greatest common divisor of two numbers.
 *
 *  \param[in] number1 First number of GCD
 *  \param[in] number2 Second number of GCD
 *
 *  \return Greatest common divisor
 */

int findGCD(int number1, int number2)
{
    int GCD = 1;
    if (number1 == 0 || number2 == 0)
        return GCD;

    GCD = number1 * number2 / findLCM(number1, number2);
    return GCD;
}

/*! \brief Reduce fraction to a common denominator.
 *
 *  \param[in] fraction Source fraction
 *
 *  \return Nothing
 */

void reduceFraction(fractionInfo_t* fraction)
{
    if (fraction->type == DECIMAL)
    {
        fraction->isWrong = TRUE;
        return;
    }

    int GCD = findGCD(fraction->firstPart, fraction->secondPart);
    fraction->firstPart /= GCD;
    fraction->secondPart /= GCD;
}

/*! \brief Transforms fraction into decimal number.
 *
 *  \param[in] fraction Source fraction
 *
 *  \return Decimal (double) format of fraction
 */

double toDouble(fractionInfo_t fraction)
{
    double doubleFraction;
    if (fraction.type == COMMON)
        doubleFraction = (double) fraction.firstPart / (double) fraction.secondPart;
    else
        doubleFraction = (double) fraction.firstPart +
                         (double) fraction.secondPart / pow(10, calculateHighestPower(fraction.secondPart));

    if (fraction.isNegative)
        doubleFraction *= -1;

    return doubleFraction;
}

/*! \brief Performs arithmetic operations on two fractions. Possible operations are '+', '-', '*', '/'. Fractions
 * can be decimal or common. If both are common, the result is common, too. In other cases it is decimal.
 *
 *  \param[in] fraction1 First part of arithmetic operation
 *  \param[in] fraction2 Second part of arithmetic operation
 *  \param[in] operation Operation type ('+', '-', '*', or '/')
 *
 *  \return Result of arithmetic operation
 */

fractionInfo_t calculate(fractionInfo_t fraction1, fractionInfo_t fraction2, char* operation)
{
    enum Case {Plus, Minus, Multiply, Divide};

    enum Case operationCode;
    if (strcmp(operation, "+") == 0)
        operationCode = Plus;
    else if (strcmp(operation, "-") == 0)
        operationCode = Minus;
    else if (strcmp(operation, "*") == 0)
        operationCode = Multiply;
    else
        operationCode = Divide;

    fractionInfo_t result;
    if (fraction1.type == COMMON && fraction2.type == COMMON)
    {
        int LCM = findLCM(fraction1.secondPart, fraction2.secondPart);
        result.type = COMMON;

        // Учет знака
        if (fraction1.isNegative)
            fraction1.firstPart *= -1;

        if (fraction2.isNegative)
            fraction2.firstPart *= -1;

        switch (operationCode)
        {
            case Plus:
                result.firstPart = fraction1.firstPart * LCM / fraction1.secondPart +
                                   fraction2.firstPart * LCM / fraction2.secondPart;
                result.secondPart = LCM;
                break;

            case Minus:
                result.firstPart = fraction1.firstPart * LCM / fraction1.secondPart -
                                   fraction2.firstPart * LCM / fraction2.secondPart;
                result.secondPart = LCM;
                break;

            case Multiply:
                result.firstPart = fraction1.firstPart * fraction2.firstPart;
                result.secondPart = fraction1.secondPart * fraction2.secondPart;
                break;

            case Divide:
                result.firstPart = fraction1.firstPart * fraction2.secondPart;
                result.secondPart = fraction1.secondPart * fraction2.firstPart;
                break;
        }

        if ((result.firstPart < 0 && result.secondPart > 0) || (result.firstPart > 0 && result.secondPart < 0))
            result.isNegative = TRUE;
        else
            result.isNegative = FALSE;

        result.firstPart = abs(result.firstPart);
        result.secondPart = abs(result.secondPart);

        result.isWrong = FALSE;

        reduceFraction(&result);
        return result;
    } else
    {
        result.type = DECIMAL;

        double decimal1 = toDouble(fraction1);
        double decimal2 = toDouble(fraction2);
        double resultDecimal;

        switch (operationCode)
        {
            case Plus:
                resultDecimal = decimal1 + decimal2;
                break;

            case Minus:
                resultDecimal = decimal1 - decimal2;
                break;

            case Multiply:
                resultDecimal = decimal1 * decimal2;
                break;

            case Divide:
                resultDecimal = decimal1 / decimal2;
                break;
        }

        if (resultDecimal < 0)
        {
            result.isNegative = TRUE;
            resultDecimal *= -1;
        } else
            result.isNegative = FALSE;

        int negativePower = calculateHighestNegativePower(resultDecimal);

        result.firstPart = (int) resultDecimal;
        result.secondPart = (int) (resultDecimal * pow(10, negativePower) -
                                   (int) resultDecimal * pow(10, negativePower));

        result.isWrong = FALSE;
        return result;
    }
}

/*! \brief Compares two fractions. Possible comparison operations are '>', '<', '=', '!=', '>=', '<='.
 * Fractions can be decimal or common. Returns true or false.
 *
 *  \param[in] fraction1 First part of comparison
 *  \param[in] fraction2 Second part of comparison
 *  \param[in] operation Operation type ('>', '<', '=', '!=', '>=', or '<=')
 *
 *  \return Result of comparison (TRUE or FALSE)
 */

int compare(fractionInfo_t fraction1, fractionInfo_t fraction2, char* operation)
{
    enum Case {Lesser, Greater, Equal, NotEqual, GreaterEqual, LesserEqual};

    enum Case operationCode;
    if (strcmp(operation, "<") == 0)
        operationCode = Lesser;
    else if (strcmp(operation, ">") == 0)
        operationCode = Greater;
    else if (strcmp(operation, "=") == 0)
        operationCode = Equal;
    else if (strcmp(operation, "!=") == 0)
        operationCode = NotEqual;
    else if (strcmp(operation, ">=") == 0)
        operationCode = GreaterEqual;
    else
        operationCode = LesserEqual;

    double decimal1 = toDouble(fraction1);
    double decimal2 = toDouble(fraction2);

    switch (operationCode)
    {
        case Lesser:
            return decimal1 < decimal2;

        case Greater:
            return decimal1 > decimal2;

        case Equal:
            return decimal1 == decimal2;

        case NotEqual:
            return decimal1 != decimal2;

        case GreaterEqual:
            return decimal1 >= decimal2;

        case LesserEqual:
            return decimal1 <= decimal2;
    }
}

int userInput()
{
    char* firstFraction;
    char* secondFraction;
    char* operation;

    fractionInfo_t fraction1;
    fractionInfo_t fraction2;
    fractionInfo_t result;

    setlocale(LC_ALL, "C");

    do
    {
        puts("Input first fraction:");
        inputString(&firstFraction);
        fraction1 = makeIntoFraction(firstFraction);
    } while (fraction1.isWrong);
	
	do
    {
        puts("Input operation:");
        inputString(&operation);
    } while (checkOperation(operation) == 0);

    do
    {
        puts("Input second fraction:");
        inputString(&secondFraction);
        fraction2 = makeIntoFraction(secondFraction);
    } while (fraction2.isWrong);

    if (strcmp(operation, "+") == 0 || strcmp(operation, "-") == 0 ||
        strcmp(operation, "/") == 0 || strcmp(operation, "*") == 0 )
    {
        result = calculate(fraction1, fraction2, operation);

        if (result.isNegative)
            printf("-");
        if (result.type == COMMON)
            printf("%d/%d\n", result.firstPart, result.secondPart);
        else
            printf("%d.%d\n", result.firstPart, result.secondPart);
    } else
        if (compare(fraction1, fraction2, operation))
			puts("True");
		else
			puts("False");

    return 0;
}
