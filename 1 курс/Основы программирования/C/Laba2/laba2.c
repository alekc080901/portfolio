#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define NUMBER_SYSTEM 10

// �������� ����� �����; ����� ������ ���� ����������� ��� 0
int input_nat()
{
    int temp = 0;
    while (!scanf("%d", &temp))
    {
        fflush(stdin);
        printf("������� ���������� ������!\n");
    }
    if (temp < 0)
    {
        printf("����� ������ ���� ����������� ��� 0!\n");
        input_nat();
    }
    return temp;
}

// ����� �����
int quantity_number(number)
{
    int quantity = 0;
    do
        {
            number = number/10;
            quantity++;
        }
    while (number > 0);
    return quantity;
}

// �������� ���������� ������ � ������� �����
int string_in_array(int len, char** array, char* element)
{
    for (int i = 0; i < len; i++)
        if (strcmp(array[i], element) == 0)
            return 1;
    return 0;
}

// ������������ ��������
char** combine_arrays(char** array1, int len1, char** array2, int len2)
{
    if (array1 == NULL)
        return array2;
    else if (array2 == NULL)
        return array1;

    char** array3 = NULL;
    int count = 0;
    array3 = (char**) malloc((len1 + len2) * sizeof(char*));
    for (; count < len1; count++)
    {
        array3[count] = array1[count];
    }

    for (int i = 0; i < len2; i++, count++)
    {
        array3[count] = array2[i];
    }

    return array3;
}

int main()
{
    int user_choice = 0;
    int cols = -1, rows = -1;
    int count_coord = 0;
    char coordinate[24];
    int **field = NULL;
    char **list_points = NULL;

    enum Case {main_array = 1, point_array, show, exit_cycle};

    setlocale(LC_ALL, "");  // ����������� ������������� �������� ����� � �������
    do
    {
        printf("%s", "\n������� ����� � ��������� (1-4):\n1. ������� ������� ������;\n"
                        "2. ������� ������ ���������������;\n3. ���������� �����;\n"
                        "4. ���������.\n");

        user_choice = input_nat();

        if (!(user_choice == 1 || user_choice == 2 || user_choice == 3 || user_choice == 4))
        {
            printf("������� �������� �� 1 �� 4!\n");
            continue;
        }

        switch (user_choice)
        {
            // �������� �������� �������
            case main_array:
            {
                printf("������� ���������� ������� �������� �������:\n");
                rows = input_nat();
                printf("������� ���������� �������� �������� �������:\n");
                cols = input_nat();
                field = (int **) malloc(rows * sizeof(int*));
                for (int i = 0; i < rows; i++)
                    field[i] = (int *) calloc(cols, sizeof(int));
                break;
            }

            // �������� ������� �����
            case point_array:
            {
                int x1, y1, x2, y2;
                int rectanglesNumber;
                int temp_x = 0;
                int temp_y = 0;
                int count_coord1 = 0;
                char** list_points1 = NULL;
                char string_temp_x[20];
                char string_temp_y[20];

                free(list_points);

                if (field == NULL)
                {
                    printf("������� ������� ������� ������!\n");
                    break;
                }

                // �������� ������� ���������������
                printf("������� ��������������� �� ���������� ������?\n");
                rectanglesNumber = input_nat();

                // ���������� ����� �������
                for (int i = 0; i < rectanglesNumber; i++, count_coord1 = 0)
                {
                    printf("������� ��������� ���������� %d ��������������\n", i + 1);
                    printf("x = ");
                    x1 = input_nat();
                    printf("\ny = ");
                    y1 = input_nat();
                    printf("������� �������� ���������� %d ��������������\n", i + 1);
                    printf("x = ");
                    x2 = input_nat();
                    printf("\ny = ");
                    y2 = input_nat();

                    if (x2 <= x1 || y2 <= y1)
                    {
                        printf("�������� ���������� �� ����� ���� ������ ���������!\n");
                        i--;
                        continue;
                    }

                    if ((x2 - 1) > cols && (y2 - 1) > rows)
                    {
                        printf("��������� ������������� ������� �� ������� �������� �������!");
                        break;
                    }

                    // ��������  ������� ���� �����, ���������� ����� ���������������
                    list_points1 = (char**) malloc(rectanglesNumber * (y2-y1) * (x2-x1) * sizeof(char*));

                    temp_x = x1;
                    for (int x = 0; x < (x2-x1); x++, temp_x++)
                    {
                        temp_y = y1;

                        for (int y = 0; y < (y2 - y1); y++, temp_y++)
                        {
                            list_points1[count_coord1] = (char *) malloc((6 + quantity_number(temp_x) +
                                                                          quantity_number(temp_y)) * sizeof(char));

                            itoa(temp_x, string_temp_x, NUMBER_SYSTEM);
                            itoa(temp_y, string_temp_y, NUMBER_SYSTEM);

                            // ���������� ���� (x, y)
                            sprintf(coordinate, "(%d, %d)", temp_x, temp_y);

                            if (!string_in_array(count_coord, list_points, coordinate))
                            {
                                sprintf(list_points1[count_coord1], "%s", coordinate);
                                count_coord1++;
                            }
                        }
                    }

                    // ������ ����� ���� ���������������
                    list_points = combine_arrays(list_points, count_coord, list_points1, count_coord1);
                    // ���������� �����, ���������� ����� ����������������
                    count_coord = count_coord + count_coord1;
                }
                free(list_points1);
                break;
            }

            // ����� ����������
            case show:
            {
                if (list_points == NULL || cols < 0 || rows < 0)
                {
                   printf("������� ������� �������!\n");
                   break;
                }
                for (int i = 0; i < rows; i++)
                    for (int j = 0; j < cols; j++)
                    {
                        sprintf(coordinate, "(%d, %d)",  i, j);

                        if (string_in_array(count_coord, list_points, coordinate))
                            printf("|#");
                        else
                            printf("|_");

                        if (j == cols - 1)
                            printf("|\n");
                    }

                printf("������� ���������� ����� ���� � %d", (rows * cols - count_coord));
                break;
            }

            // ����� �� �����
            case exit_cycle:
                free(list_points);
                free(field);
                exit(EXIT_SUCCESS);
                break;
                
        }
    } while (1);
}