#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

int main()
{
// прпрп
    int user_choice, length, random_checker;
    int* numbers = NULL;
    int* temp_numbers = NULL;

    setlocale(LC_ALL, "");  // Возможность использования русского языка в консоли
    do
    {
        printf("%s %s", "\nВведите цифры в диапазоне (1-4):\n1. Создать массив;\n2.",
               "Вывести массив;\n3. Обработать массив;\n4. Закончить.\n");

        if (!scanf("%d", &user_choice))  // Проверка ввода. В случае, когда функция выдает 0
        {                                // (ошибку), пропускает итерацию цикла
            fflush(stdin);
            printf("Введите корректные данные!\n");
            continue;
        }

        switch (user_choice)
        {
        case 1: // Создание массива
            printf("Введите длину массива:\n");
            if (!scanf("%d", &length))
            {
                fflush(stdin);
                printf("Неправильный формат длины массива!\n");
                break;
            }
            else if (length <= 0)
            {
                printf("Длина должна быть больше 0!\n");
                break;
            }

            numbers = (int*)malloc(length*sizeof(int));

            printf("Хотите ли вы заполнить массив случайными числами?(1/0)\n");
            if (!scanf("%d", &random_checker))
            {
                fflush(stdin);
                printf("Неправильный формат выбора!\n");
                break;
            }

            if (random_checker == 1) // Случайные числа
            {
               for (int i = 0;
                    i < length;
                    i++
                    )
                   numbers[i] = rand();
            }

            else if (random_checker == 0)  // Ручной ввод
            {
                for (int number, i = 0;
                     i < length;
                     i++
                     )
                {
                   printf("Введите значение %d элемента:\n", i+1);
                   if (!scanf("%d", &number))
                   {
                       fflush(stdin);
                       printf("Неправильный формат значения элемента!\n");
                       break;
                   }
                   numbers[i] = number;
                }
            }

            else
                printf("Введите 1 или 0!\n");
            break;

        case 3:
            if (numbers == NULL)
            {
                printf("Сначала создайте массив!");
                break;
            }
            temp_numbers = (int*)malloc(length*sizeof(int)); // Создание копии массива для дальнейшей работы
            for (int number, i = 0;
                 i < length;
                 i++
                 )
                temp_numbers[i] = numbers[i];

            for (int i = 0;  // Сам алгоритм, требуемый заданием
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

                    if (temp_numbers[i] != 1)  // Более красивый вывод
                        printf("%d, ", temp_numbers[i]);
                    else
                        printf("%d.", temp_numbers[i]);
                }
            printf("\n\n");
            }
            free(temp_numbers);
            break;

        case 2: // Вывод массива на экран
            if (numbers == NULL)
            {
                printf("Сначала создайте массив!");
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

        case 4: // Выход из программы
            free(numbers);
            exit(errno);
            break;
        }
    } while (1);
    return 0;
}
