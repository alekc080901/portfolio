#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int main()
{
// �����
    int user_choice, length, random_checker;
    int* numbers = NULL;
    int* temp_numbers = NULL;

    setlocale(LC_ALL, "");  // ����������� ������������� �������� ����� � �������
    do
    {
        printf("%s %s", "\n������� ����� � ��������� (1-4):\n1. ������� ������;\n2.",
               "������� ������;\n3. ���������� ������;\n4. ���������.\n");

        if (!scanf("%d", &user_choice))  // �������� �����. � ������, ����� ������� ������ 0
        {                                // (������), ���������� �������� �����
            fflush(stdin);
            printf("������� ���������� ������!\n");
            continue;
        }

        switch (user_choice)
        {
        case 1: // �������� �������
            printf("������� ����� �������:\n");
            if (!scanf("%d", &length))
            {
                fflush(stdin);
                printf("������������ ������ ����� �������!\n");
                break;
            }
            else if (length <= 0)
            {
                printf("����� ������ ���� ������ 0!\n");
                break;
            }

            numbers = (int*)malloc(length*sizeof(int));

            printf("������ �� �� ��������� ������ ���������� �������?(1/0)\n");
            if (!scanf("%d", &random_checker))
            {
                fflush(stdin);
                printf("������������ ������ ������!\n");
                break;
            }

            if (random_checker == 1) // ��������� �����
            {
               for (int i = 0;
                    i < length;
                    i++
                    )
                   numbers[i] = rand();
            }

            else if (random_checker == 0)  // ������ ����
            {
                for (int number, i = 0;
                     i < length;
                     i++
                     )
                {
                   printf("������� �������� %d ��������:\n", i+1);
                   if (!scanf("%d", &number))
                   {
                       fflush(stdin);
                       printf("������������ ������ �������� ��������!\n");
                       break;
                   }
                   numbers[i] = number;
                }
            }

            else
                printf("������� 1 ��� 0!\n");
            break;

        case 3:
            if (numbers == NULL)
            {
                printf("������� �������� ������!");
                break;
            }
            temp_numbers = (int*)malloc(length*sizeof(int)); // �������� ����� ������� ��� ���������� ������
            for (int number, i = 0;
                 i < length;
                 i++
                 )
                temp_numbers[i] = numbers[i];

            for (int i = 0;  // ��� ��������, ��������� ��������
                 i < length;
                 i++
                 )
            {
                while (temp_numbers[i] != 1)
                {
                    if (temp_numbers[i] % 2 == 0)
                        temp_numbers[i] = temp_numbers[i] / 2;
                    else
                        temp_numbers[i] = temp_numbers[i] * 3 + 1;

                    if (temp_numbers[i] != 1)  // ����� �������� �����
                        printf("%d, ", temp_numbers[i]);
                    else
                        printf("%d.", temp_numbers[i]);
                }
            printf("\n\n");
            }
            free(temp_numbers);
            break;

        case 2: // ����� ������� �� �����
            if (numbers == NULL)
            {
                printf("������� �������� ������!");
                break;
            }
            printf("\n[");
            for (int i = 0;
                 i < length;
                 i++
                 )
                if (i + 1 != length)
                    printf("%d, ", numbers[i]);
                else
                    printf("%d]\n", numbers[i]);
        break;

        case 4: // ����� �� ���������
            free(numbers);
            exit(errno);
            break;
        }
    } while (1);
    return 0;
}
