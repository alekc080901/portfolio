#include <CUnit/CUnit.h>
#include "algorithm.c"

void test_checkIntTrue()
{
    CU_ASSERT(checkInt("654321") == 1);
}

void test_checkIntFalse()
{
    CU_ASSERT(checkInt("654321qwerty") == 0);
}

void test_splitFractionRight1()
{
    struct fractionParts expectedResult = {1, 3, FALSE, FALSE};
    struct fractionParts realResult = splitFraction("1/3", 1);
    CU_ASSERT(expectedResult.firstPart == realResult.firstPart);
    CU_ASSERT(expectedResult.secondPart == realResult.secondPart);
    CU_ASSERT(expectedResult.isNegative == realResult.isNegative);
    CU_ASSERT(expectedResult.isWrong == realResult.isWrong);
}

void test_splitFractionRight2()
{
    struct fractionParts expectedResult = {3, 2, TRUE, FALSE};
    struct fractionParts realResult = splitFraction("-3.2", 2);
    CU_ASSERT(expectedResult.firstPart == realResult.firstPart);
    CU_ASSERT(expectedResult.secondPart == realResult.secondPart);
    CU_ASSERT(expectedResult.isNegative == realResult.isNegative);
    CU_ASSERT(expectedResult.isWrong == realResult.isWrong);
}

void test_splitFractionWrong()
{
    struct fractionParts expectedResult;
    expectedResult.isWrong = TRUE;
    struct fractionParts realResult = splitFraction("3.3/2", 1);
    CU_ASSERT(expectedResult.isWrong == realResult.isWrong);
}

void test_makeIntoFractionCommonNormal()
{
    fractionInfo_t expectedResult = {23, 2, COMMON, FALSE, FALSE};
    fractionInfo_t realResult = makeIntoFraction("23/2");
    CU_ASSERT(expectedResult.firstPart == realResult.firstPart);
    CU_ASSERT(expectedResult.secondPart == realResult.secondPart);
    CU_ASSERT(expectedResult.type == realResult.type);
    CU_ASSERT(expectedResult.isNegative == realResult.isNegative);
    CU_ASSERT(expectedResult.isWrong == realResult.isWrong);
}

void test_makeIntoFractionCommonZeroNumerator()
{
    fractionInfo_t expectedResult = {0, 2, COMMON, FALSE, FALSE};
    fractionInfo_t realResult = makeIntoFraction("0/2");
    CU_ASSERT(expectedResult.firstPart == realResult.firstPart);
    CU_ASSERT(expectedResult.secondPart == realResult.secondPart);
    CU_ASSERT(expectedResult.type == realResult.type);
    CU_ASSERT(expectedResult.isNegative == realResult.isNegative);
    CU_ASSERT(expectedResult.isWrong == realResult.isWrong);
}

void test_makeIntoFractionCommonZeroDenominator()
{
    fractionInfo_t expectedResult;
    expectedResult.isWrong = TRUE;
    fractionInfo_t realResult = makeIntoFraction("2/0");
    CU_ASSERT(expectedResult.isWrong == realResult.isWrong);
}

void test_makeIntoFractionDecimal()
{
    fractionInfo_t expectedResult = {23, 2, DECIMAL, FALSE, FALSE};
    fractionInfo_t realResult = makeIntoFraction("23.2");
    CU_ASSERT(expectedResult.firstPart == realResult.firstPart);
    CU_ASSERT(expectedResult.secondPart == realResult.secondPart);
    CU_ASSERT(expectedResult.type == realResult.type);
    CU_ASSERT(expectedResult.isNegative == realResult.isNegative);
    CU_ASSERT(expectedResult.isWrong == realResult.isWrong);
}

void test_makeIntoFractionNegative()
{
    fractionInfo_t expectedResult = {23, 2, DECIMAL, TRUE, FALSE};
    fractionInfo_t realResult = makeIntoFraction("-23.2");
    CU_ASSERT(expectedResult.firstPart == realResult.firstPart);
    CU_ASSERT(expectedResult.secondPart == realResult.secondPart);
    CU_ASSERT(expectedResult.type == realResult.type);
    CU_ASSERT(expectedResult.isNegative == realResult.isNegative);
    CU_ASSERT(expectedResult.isWrong == realResult.isWrong);
}

void test_makeIntoFractionWrong()
{
    fractionInfo_t expectedResult;
    expectedResult.isWrong = TRUE;
    fractionInfo_t realResult = makeIntoFraction("f23/2");
    CU_ASSERT(expectedResult.isWrong == realResult.isWrong);
}

void test_calculateHighestPowerNormal1()
{
    CU_ASSERT(calculateHighestPower(12345678) == 8);
}

void test_calculateHighestPowerNormal2()
{
    CU_ASSERT(calculateHighestPower(1) == 1);
}

void test_calculateHighestPowerNegative()
{
    CU_ASSERT(calculateHighestPower(-12345678) == 8);
}

void test_calculateHighestNegativePowerNormal()
{
    CU_ASSERT(calculateHighestNegativePower(123.45) == 2);
}

void test_calculateHighestNegativePowerBordered()
{
    CU_ASSERT(calculateHighestNegativePower(123.4567890) == 3);
}

void test_calculateHighestNegativePowerNegative()
{
    CU_ASSERT(calculateHighestNegativePower(-123.42) == 2);
}

void test_checkOperationTrue()
{
    CU_ASSERT(checkOperation(">=") == TRUE);
}

void test_checkOperationFalse()
{
    CU_ASSERT(checkOperation("+-") == FALSE);
}

void test_findSimpleDividersNormal()
{
    int expectedArray[] = {2, 2, 3, 5};
    arrayInfo_t realResult = findSimpleDividers(60);
    CU_ASSERT(realResult.length = 4);
    for (int i = 0; i < 4; i++)
        CU_ASSERT(expectedArray[i] == realResult.array[i]);
}

void test_subtractArraysNormal()
{
    arrayInfo_t minuendInfo;
    int minuend[] = {4, 2, 3, 5, 2};
    minuendInfo.array = minuend;
    minuendInfo.length = 5;

    arrayInfo_t subtrahendInfo;
    int subtrahend[] = {2, 5};
    subtrahendInfo.array = subtrahend;
    subtrahendInfo.length = 2;

    int expectedArray[] = {4, 3, 2};
    arrayInfo_t realResult = subtractArrays(minuendInfo, subtrahendInfo);
    CU_ASSERT(realResult.length = 3);

    for (int i = 0; i < 3; i++)
        CU_ASSERT(expectedArray[i] == realResult.array[i]);
}

void test_subtractArraysZeroSubtrahend()
{
    arrayInfo_t minuendInfo;
    int minuend[] = {4, 2, 3, 5, 2};
    minuendInfo.array = minuend;
    minuendInfo.length = 5;

    arrayInfo_t subtrahendInfo;
    int subtrahend[] = {};
    subtrahendInfo.array = subtrahend;
    subtrahendInfo.length = 0;

    int expectedArray[] = {4, 2, 3, 5, 2};
    arrayInfo_t realResult = subtractArrays(minuendInfo, subtrahendInfo);
    CU_ASSERT(realResult.length = 5);

    for (int i = 0; i < 5; i++)
        CU_ASSERT(expectedArray[i] == realResult.array[i]);
}

void test_subtractArraysZeroMinuend()
{
    arrayInfo_t minuendInfo;
    int minuend[] = {};
    minuendInfo.array = minuend;
    minuendInfo.length = 0;

    arrayInfo_t subtrahendInfo;
    int subtrahend[] = {2, 5};
    subtrahendInfo.array = subtrahend;
    subtrahendInfo.length = 2;

    int expectedArray[] = {};
    arrayInfo_t realResult = subtractArrays(minuendInfo, subtrahendInfo);
    CU_ASSERT(realResult.length == 0);
}

void test_findLCM()
{
    CU_ASSERT(findLCM(60, 75) == 300);
}

void test_findGCD()
{
    CU_ASSERT(findGCD(60, 75) == 15);
}

void test_reduceFractionNormal1()
{
    fractionInfo_t fraction = {12, 16, COMMON, FALSE, FALSE};
    reduceFraction(&fraction);
    CU_ASSERT(fraction.firstPart == 3);
    CU_ASSERT(fraction.secondPart == 4);
    CU_ASSERT(fraction.type == COMMON);
    CU_ASSERT(fraction.isNegative == FALSE);
    CU_ASSERT(fraction.isWrong == FALSE);
}

void test_reduceFractionNormal2()
{
    fractionInfo_t fraction = {14, 2, COMMON, TRUE, FALSE};
    reduceFraction(&fraction);
    CU_ASSERT(fraction.firstPart == 7);
    CU_ASSERT(fraction.secondPart == 1);
    CU_ASSERT(fraction.type == COMMON);
    CU_ASSERT(fraction.isNegative == TRUE);
    CU_ASSERT(fraction.isWrong == FALSE);
}

void test_reduceFractionWrongType()
{
    fractionInfo_t fraction = {16, 32, DECIMAL, FALSE, FALSE};
    reduceFraction(&fraction);
    CU_ASSERT(fraction.isWrong == TRUE);
}

void test_toDoubleCommonNormal()
{
    fractionInfo_t fraction = {12, 16, COMMON, FALSE, FALSE};
    CU_ASSERT(toDouble(fraction) == 0.75);
}

void test_toDoubleCommonNegative()
{
    fractionInfo_t fraction = {12, 16, COMMON, TRUE, FALSE};
    CU_ASSERT(toDouble(fraction) == -0.75);
}

void test_toDoubleCommonZero()
{
    fractionInfo_t fraction = {0, 16, COMMON, FALSE, FALSE};
    CU_ASSERT(toDouble(fraction) == 0.0);
}

void test_toDoubleDecimalNormal()
{
    fractionInfo_t fraction = {12, 16, DECIMAL, FALSE, FALSE};
    CU_ASSERT(toDouble(fraction) == 12.16);
}

void test_toDoubleDecimalNegative()
{
    fractionInfo_t fraction = {0, 16, DECIMAL, TRUE, FALSE};
    CU_ASSERT(toDouble(fraction) == -0.16);
}

void test_toDoubleDecimalZero()
{
    fractionInfo_t fraction = {0, 0, DECIMAL, FALSE, FALSE};
    CU_ASSERT(toDouble(fraction) == 0.0);
}

void test_calculateCommonPlus()
{
    fractionInfo_t first = {23, 2, COMMON, FALSE, FALSE};
    fractionInfo_t second = {16, 35, COMMON, FALSE, FALSE};
    char* operation = "+";
    fractionInfo_t realResult = calculate(first, second, operation);
    CU_ASSERT(realResult.firstPart == 837);
    CU_ASSERT(realResult.secondPart == 70);
    CU_ASSERT(realResult.type == COMMON);
    CU_ASSERT(realResult.isNegative == FALSE);
    CU_ASSERT(realResult.isWrong == FALSE);
}

void test_calculateCommonMinus()
{
    fractionInfo_t first = {23, 2, COMMON, FALSE, FALSE};
    fractionInfo_t second = {16, 25, COMMON, TRUE, FALSE};
    char* operation = "-";
    fractionInfo_t realResult = calculate(first, second, operation);
    CU_ASSERT(realResult.firstPart == 607);
    CU_ASSERT(realResult.secondPart == 50);
    CU_ASSERT(realResult.type == COMMON);
    CU_ASSERT(realResult.isNegative == FALSE);
    CU_ASSERT(realResult.isWrong == FALSE);
}

void test_calculateCommonMultiply()
{
    fractionInfo_t first = {23, 2, COMMON, FALSE, FALSE};
    fractionInfo_t second = {16, 25, COMMON, FALSE, FALSE};
    char* operation = "*";
    fractionInfo_t realResult = calculate(first, second, operation);
    CU_ASSERT(realResult.firstPart == 184);
    CU_ASSERT(realResult.secondPart == 25);
    CU_ASSERT(realResult.type == COMMON);
    CU_ASSERT(realResult.isNegative == FALSE);
    CU_ASSERT(realResult.isWrong == FALSE);
}

void test_calculateCommonDivide()
{
    fractionInfo_t first = {23, 6, COMMON, FALSE, FALSE};
    fractionInfo_t second = {8, 76, COMMON, FALSE, FALSE};
    char* operation = "/";
    fractionInfo_t realResult = calculate(first, second, operation);
    CU_ASSERT(realResult.firstPart == 437);
    CU_ASSERT(realResult.secondPart == 12);
    CU_ASSERT(realResult.type == COMMON);
    CU_ASSERT(realResult.isNegative == FALSE);
    CU_ASSERT(realResult.isWrong == FALSE);
}

void test_calculateDecimalPlus()
{
    fractionInfo_t first = {23, 2, DECIMAL, FALSE, FALSE};
    fractionInfo_t second = {16, 95, DECIMAL, FALSE, FALSE};
    char* operation = "+";
    fractionInfo_t realResult = calculate(first, second, operation);
    CU_ASSERT(realResult.firstPart == 40);
    CU_ASSERT(realResult.secondPart == 15);
    CU_ASSERT(realResult.type == DECIMAL);
    CU_ASSERT(realResult.isNegative == FALSE);
    CU_ASSERT(realResult.isWrong == FALSE);
}

void test_calculateDecimalMinus()
{
    fractionInfo_t first = {8, 2, DECIMAL, FALSE, FALSE};
    fractionInfo_t second = {16, 95, DECIMAL, FALSE, FALSE};
    char* operation = "-";
    fractionInfo_t realResult = calculate(first, second, operation);
    CU_ASSERT(realResult.firstPart == 8);
    CU_ASSERT(realResult.secondPart == 75);
    CU_ASSERT(realResult.type == DECIMAL);
    CU_ASSERT(realResult.isNegative == TRUE);
    CU_ASSERT(realResult.isWrong == FALSE);
}

void test_calculateDecimalMultiply()
{
    fractionInfo_t first = {8, 3, DECIMAL, FALSE, FALSE};
    fractionInfo_t second = {16, 85, DECIMAL, TRUE, FALSE};
    char* operation = "*";
    fractionInfo_t realResult = calculate(first, second, operation);
    CU_ASSERT(realResult.firstPart == 139);
    CU_ASSERT(realResult.secondPart == 855);
    CU_ASSERT(realResult.type == DECIMAL);
    CU_ASSERT(realResult.isNegative == TRUE);
    CU_ASSERT(realResult.isWrong == FALSE);
}

void test_calculateDecimalDivide()
{
    fractionInfo_t first = {9, 2, DECIMAL, TRUE, FALSE};
    fractionInfo_t second = {16, 95, DECIMAL, TRUE, FALSE};
    char* operation = "/";
    fractionInfo_t realResult = calculate(first, second, operation);
    CU_ASSERT(realResult.firstPart == 0);
    CU_ASSERT(realResult.secondPart == 542);
    CU_ASSERT(realResult.type == DECIMAL);
    CU_ASSERT(realResult.isNegative == FALSE);
    CU_ASSERT(realResult.isWrong == FALSE);
}

void test_calculateBothType()
{
    fractionInfo_t first = {9, 2, COMMON, FALSE, FALSE};
    fractionInfo_t second = {16, 95, DECIMAL, FALSE, FALSE};
    char* operation = "+";
    fractionInfo_t realResult = calculate(first, second, operation);
    CU_ASSERT(realResult.firstPart == 21);
    CU_ASSERT(realResult.secondPart == 45);
    CU_ASSERT(realResult.type == DECIMAL);
    CU_ASSERT(realResult.isNegative == FALSE);
    CU_ASSERT(realResult.isWrong == FALSE);
}

void test_compareCommonLesser()
{
    fractionInfo_t first = {9, 2, COMMON, FALSE, FALSE};
    fractionInfo_t second = {16, 95, COMMON, FALSE, FALSE};
    char* operation = "<";
    CU_ASSERT(compare(first, second, operation) == FALSE);
}

void test_compareCommonGreater()
{
    fractionInfo_t first = {9, 2, COMMON, FALSE, FALSE};
    fractionInfo_t second = {16, 95, COMMON, FALSE, FALSE};
    char* operation = ">";
    CU_ASSERT(compare(first, second, operation) == TRUE);
}

void test_compareCommonEqualTrue()
{
    fractionInfo_t first = {9, 2, COMMON, FALSE, FALSE};
    fractionInfo_t second = {9, 2, COMMON, FALSE, FALSE};
    char* operation = "=";
    CU_ASSERT(compare(first, second, operation) == TRUE);
}

void test_compareCommonEqualFalse()
{
    fractionInfo_t first = {9, 2, COMMON, FALSE, FALSE};
    fractionInfo_t second = {16, 95, COMMON, FALSE, FALSE};
    char* operation = "=";
    CU_ASSERT(compare(first, second, operation) == FALSE);
}

void test_compareCommonNotEqualTrue()
{
    fractionInfo_t first = {9, 2, COMMON, FALSE, FALSE};
    fractionInfo_t second = {9, 2, COMMON, FALSE, FALSE};
    char* operation = "!=";
    CU_ASSERT(compare(first, second, operation) == FALSE);
}

void test_compareCommonNotEqualFalse()
{
    fractionInfo_t first = {9, 2, COMMON, FALSE, FALSE};
    fractionInfo_t second = {16, 95, COMMON, FALSE, FALSE};
    char* operation = "!=";
    CU_ASSERT(compare(first, second, operation) == TRUE);
}

void test_compareDecimalLesser()
{
    fractionInfo_t first = {9, 2, DECIMAL, FALSE, FALSE};
    fractionInfo_t second = {16, 95, DECIMAL, FALSE, FALSE};
    char* operation = "<";
    CU_ASSERT(compare(first, second, operation) == TRUE);
}

void test_compareDecimalGreater()
{
    fractionInfo_t first = {9, 2, DECIMAL, FALSE, FALSE};
    fractionInfo_t second = {16, 95, DECIMAL, FALSE, FALSE};
    char* operation = ">";
    CU_ASSERT(compare(first, second, operation) == FALSE);
}

void test_compareDecimalEqualTrue()
{
    fractionInfo_t first = {9, 2, DECIMAL, FALSE, FALSE};
    fractionInfo_t second = {9, 2, DECIMAL, FALSE, FALSE};
    char* operation = "=";
    CU_ASSERT(compare(first, second, operation) == TRUE);
}

void test_compareDecimalEqualFalse()
{
    fractionInfo_t first = {9, 2, DECIMAL, FALSE, FALSE};
    fractionInfo_t second = {16, 95, DECIMAL, FALSE, FALSE};
    char* operation = "=";
    CU_ASSERT(compare(first, second, operation) == FALSE);
}

void test_compareDecimalNotEqualTrue()
{
    fractionInfo_t first = {9, 2, DECIMAL, FALSE, FALSE};
    fractionInfo_t second = {9, 2, DECIMAL, FALSE, FALSE};
    char* operation = "!=";
    CU_ASSERT(compare(first, second, operation) == FALSE);
}

void test_compareDecimalNotEqualFalse()
{
    fractionInfo_t first = {9, 2, DECIMAL, FALSE, FALSE};
    fractionInfo_t second = {16, 95, DECIMAL, FALSE, FALSE};
    char* operation = "!=";
    CU_ASSERT(compare(first, second, operation) == TRUE);
}

void test_compareBothType()
{
    fractionInfo_t first = {9, 2, COMMON, FALSE, FALSE};
    fractionInfo_t second = {16, 95, DECIMAL, FALSE, FALSE};
    char* operation = "<";
    CU_ASSERT(compare(first, second, operation) == TRUE);
}

int main()
{
    CU_pSuite pSuite = NULL;
    CU_initialize_registry();

    pSuite = CU_add_suite("checkInt", NULL, NULL);
    CU_ADD_TEST(pSuite, test_checkIntTrue);
    CU_ADD_TEST(pSuite, test_checkIntFalse);

    pSuite = CU_add_suite("splitFraction", NULL, NULL);
    CU_ADD_TEST(pSuite, test_splitFractionRight1);
    CU_ADD_TEST(pSuite, test_splitFractionRight2);
    CU_ADD_TEST(pSuite, test_splitFractionWrong);

    pSuite = CU_add_suite("makeIntoFraction", NULL, NULL);
    CU_ADD_TEST(pSuite, test_makeIntoFractionCommonNormal);
    CU_ADD_TEST(pSuite, test_makeIntoFractionDecimal);
    CU_ADD_TEST(pSuite, test_makeIntoFractionNegative);
    CU_ADD_TEST(pSuite, test_makeIntoFractionCommonZeroNumerator);
    CU_ADD_TEST(pSuite, test_makeIntoFractionCommonZeroDenominator);
    CU_ADD_TEST(pSuite, test_makeIntoFractionWrong);

    pSuite = CU_add_suite("calculateHighestPower", NULL, NULL);
    CU_ADD_TEST(pSuite, test_calculateHighestPowerNormal1);
    CU_ADD_TEST(pSuite, test_calculateHighestPowerNormal2);
    CU_ADD_TEST(pSuite, test_calculateHighestPowerNegative);

    pSuite = CU_add_suite("calculateHighestNegativePower", NULL, NULL);
    CU_ADD_TEST(pSuite, test_calculateHighestNegativePowerNormal);
    CU_ADD_TEST(pSuite, test_calculateHighestNegativePowerBordered);
    CU_ADD_TEST(pSuite, test_calculateHighestNegativePowerNegative);

    pSuite = CU_add_suite("checkOperation", NULL, NULL);
    CU_ADD_TEST(pSuite, test_checkOperationTrue);
    CU_ADD_TEST(pSuite, test_checkOperationFalse);

    pSuite = CU_add_suite("findSimpleDividers", NULL, NULL);
    CU_ADD_TEST(pSuite, test_findSimpleDividersNormal);

    pSuite = CU_add_suite("subtractArrays", NULL, NULL);
    CU_ADD_TEST(pSuite, test_subtractArraysNormal);
    CU_ADD_TEST(pSuite, test_subtractArraysZeroMinuend);
    CU_ADD_TEST(pSuite, test_subtractArraysZeroSubtrahend);

    pSuite = CU_add_suite("findLCM", NULL, NULL);
    CU_ADD_TEST(pSuite, test_findLCM);

    pSuite = CU_add_suite("findGCD", NULL, NULL);
    CU_ADD_TEST(pSuite, test_findGCD);

    pSuite = CU_add_suite("reduceFraction", NULL, NULL);
    CU_ADD_TEST(pSuite, test_reduceFractionNormal1);
    CU_ADD_TEST(pSuite, test_reduceFractionNormal2);
    CU_ADD_TEST(pSuite, test_reduceFractionWrongType);

    pSuite = CU_add_suite("toDoubleCommon", NULL, NULL);
    CU_ADD_TEST(pSuite, test_toDoubleCommonNormal);
    CU_ADD_TEST(pSuite, test_toDoubleCommonNegative);
    CU_ADD_TEST(pSuite, test_toDoubleCommonZero);

    pSuite = CU_add_suite("toDoubleDecimal", NULL, NULL);
    CU_ADD_TEST(pSuite, test_toDoubleDecimalNormal);
    CU_ADD_TEST(pSuite, test_toDoubleDecimalNegative);
    CU_ADD_TEST(pSuite, test_toDoubleDecimalZero);

    pSuite = CU_add_suite("calculateCommon", NULL, NULL);
    CU_ADD_TEST(pSuite, test_calculateCommonPlus);
    CU_ADD_TEST(pSuite, test_calculateCommonMinus);
    CU_ADD_TEST(pSuite, test_calculateCommonMultiply);
    CU_ADD_TEST(pSuite, test_calculateCommonDivide);

    pSuite = CU_add_suite("calculateDecimal", NULL, NULL);
    CU_ADD_TEST(pSuite, test_calculateDecimalPlus);
    CU_ADD_TEST(pSuite, test_calculateDecimalMinus);
    CU_ADD_TEST(pSuite, test_calculateDecimalMultiply);
    CU_ADD_TEST(pSuite, test_calculateDecimalDivide);;

    pSuite = CU_add_suite("compareCommon", NULL, NULL);
    CU_ADD_TEST(pSuite, test_compareCommonLesser);
    CU_ADD_TEST(pSuite, test_compareCommonGreater);
    CU_ADD_TEST(pSuite, test_compareCommonEqualTrue);
    CU_ADD_TEST(pSuite, test_compareCommonEqualFalse);
    CU_ADD_TEST(pSuite, test_compareCommonNotEqualTrue);
    CU_ADD_TEST(pSuite, test_compareCommonNotEqualFalse);

    pSuite = CU_add_suite("compareDecimal", NULL, NULL);
    CU_ADD_TEST(pSuite, test_compareDecimalLesser);
    CU_ADD_TEST(pSuite, test_compareDecimalGreater);
    CU_ADD_TEST(pSuite, test_compareDecimalEqualTrue);
    CU_ADD_TEST(pSuite, test_compareDecimalEqualFalse);
    CU_ADD_TEST(pSuite, test_compareDecimalNotEqualTrue);
    CU_ADD_TEST(pSuite, test_compareDecimalNotEqualFalse);

    pSuite = CU_add_suite("calculateCompareBoth", NULL, NULL);
    CU_ADD_TEST(pSuite, test_calculateBothType);
    CU_ADD_TEST(pSuite, test_compareBothType);

    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
