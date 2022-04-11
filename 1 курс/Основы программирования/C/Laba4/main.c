#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

// ���� ������ �����
void inputInt(int* number)
{
    while (!scanf("%d", number))
    {
        fflush(stdin);
        printf("������� ���������� ������!\n");
    }
}

// ��������� �����
int reverse(int number)
{
    int digit = floor(log10(abs(number))); // ����� ����� ����� ����

    if (abs(number) <= 9)
        return number;

    return (number % 10) * pow(10, digit) + reverse(number / 10);
}

int main()
{
    int number = 0;
    int reversedNumber = 0;
    int userChoice = 0;

    setlocale(LC_ALL, "");

    do
    {
        printf("������� �����:\n");
        inputInt(&number);

        reversedNumber = reverse(number);
        printf("%d\n", reversedNumber);

        printf("������ �� �� ��������� ��������� �����?(1/0)\n");
        while (1)
        {
            inputInt(&userChoice);
            if (userChoice == 1 || userChoice == 0)
                break;
            printf("������� 1 ��� 0!\n");
        }

    }while (userChoice);
}