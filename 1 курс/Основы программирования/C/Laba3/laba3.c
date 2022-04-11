#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define NUMBERS_IN_ALPHABET 53
#define MAX_FILE_STRING_NUMBER 1000
#define CHAR_A 65
#define CHAR_a 97
#define CHAR_Z 90

// Ввод только натурального числа
void inputNat(int* number)
{
    while (!scanf("%d", number))
    {
        fflush(stdin);
        printf("Введите корректные данные!\n");
    }
    if (*number < 0)
    {
        printf("Число должно быть натуральным или 0!\n");
        inputNat(number);
    }
}

// Функция оставляет в строке только символы английского алфавита и пробел
void correctString(char* string)
{
    char* correctString = NULL; // Строка, вбирающая в себя все правильные символы
    int count = 0;
    int checker = 0;

    for (int i = 0; i < strlen(string); i++)
		// a-z, A-Z, ' '
        if ((string[i] >= 65 && string[i] <= 90) || (string[i] >= 97 && string[i] <= 122) || (string[i] == 32))
        {
            correctString = realloc(correctString, count + 1);
            correctString[count] = string[i];
            count++;
            checker = 1;
        }
    if (checker)
    {
        strcpy(string, correctString);
        free(correctString);
    }
    else
    {
        printf("Ваше сообщение целиком состоит из неанглийских символов!\n");
    }
}

// Ввод пользователем строки произвольной длины и ее корректировка предыдущей функцией
void inputCorrectString(char** word)
{
    int count = 0;
    char inputChar = 0;

    fflush(stdin);

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

    correctString(*word);
}

// Создание массива всех символов алфавита
int* alphabet()
{
    int* alphabetNum = NULL;
    int count = 0;
    int ansiChar = CHAR_A;

    alphabetNum = (int*) malloc(NUMBERS_IN_ALPHABET * sizeof(int));
    for (; count < NUMBERS_IN_ALPHABET - 1; count++, ansiChar++)
    {
		// Переход из символа Z к символу a
        if (ansiChar == CHAR_Z + 1)
            ansiChar = CHAR_a;

        alphabetNum[count] = ansiChar;

    }
    alphabetNum[count] = ' ';

    for (int i = 0; i < NUMBERS_IN_ALPHABET; i++)
    {
        printf("%d  ", i);
        printf("%c\n", alphabetNum[i]);
    }
    return alphabetNum;

}

// "Подгон" длины ключа к длине сообщения. Пример: Hello world
//                                                 keykeykeyke
char* keyLengthen(char* key, int length)
{
    int lenKey = strlen(key);
    int count = 0;
    char* newKey = NULL;
	
    newKey = (char*) malloc(length * sizeof(char));
    // Ключ меньше текста
    if (strlen(key) < length)
    {
        for (int i = 0; i < length; i++, count++)
        {
            // Обнуление счетчика для повторного запуска ключа по кругу
            if (count == lenKey)
                count = 0;

            newKey[i] = key[count];
        }
    }
    // Ключ больше либо равен тексту
    else if (strlen(key) >= length)
    {
        strncpy(newKey, key, length);
        return newKey;
    }
    return newKey;
}

// Ставит соответствие между номером символа из ANSI и ее порядковым номером в алфавите. Пример: 'b'(98 символ) = 1
int ansi2alphabet(int ansiCode)
{
    int* allCharsNumbers = alphabet();
    int alphabetCode = 0;
	
    for (int i = 0; i < NUMBERS_IN_ALPHABET; i++)
        if (allCharsNumbers[i] == ansiCode)
        {
            alphabetCode = i;
            break;
        }
    return alphabetCode; // Возвращает номер символа в алфавите 
}

// Кодирование сообщений шифром Вернама
char* encode(char* text, char* key)
{
    int* allCharsNumbers = alphabet();
    int length = 0;
    char* longKey = NULL;
    int* encryptedTextNum = NULL;
    char* encryptedTextStr = NULL;

    length = strlen(text);
    longKey = keyLengthen(key, length);
	
    encryptedTextNum = (int*) malloc(length * sizeof(int));
    encryptedTextStr = (char*) malloc(length * sizeof(char));

    for (int i = 0; i < length; i++)
    {
        // Остаток от деления суммы кодов двух символов
        encryptedTextNum[i] = (ansi2alphabet((int) text[i]) + ansi2alphabet((int) longKey[i])) % NUMBERS_IN_ALPHABET;

        // Преобразование остатка в символ
        encryptedTextStr[i] = (char) allCharsNumbers[encryptedTextNum[i]];
    }
	free(encryptedTextNum);
    return encryptedTextStr;
}

// Декодирование сообщений шифром Виженера
char* decode(char* text, char* key)
{
    int* allCharsNumbers = alphabet();;
    int length = 0;
    char* longKey = NULL;
    int* decryptedTextNum = NULL;
    char* decryptedTextStr = NULL;

    length = strlen(text);
    longKey = keyLengthen(key, length);
	
    decryptedTextNum = (int*) malloc(length * sizeof(int));
    decryptedTextStr = (char*) malloc(length * sizeof(char));

    for (int i = 0; i < length; i++)
    {
		// Формула для дешифровки
        decryptedTextNum[i] = (ansi2alphabet((int) text[i]) + NUMBERS_IN_ALPHABET -
                               ansi2alphabet((int) longKey[i])) % NUMBERS_IN_ALPHABET;
							   
        decryptedTextStr[i] = (char) allCharsNumbers[decryptedTextNum[i]];
    }
	free(decryptedTextNum);
    return decryptedTextStr;
}

int main()
{
    char* message = NULL;
    char* key = NULL;
    int userChoice = 0;
    int fileChoice = 0;

    setlocale(LC_ALL, "");

    enum Case {textInput = 1, keyInput, encrypt, decrypt, exitProg};

    do
    {
        printf("Введите ваш выбор:\n"
               "1. Ввести текст.\n"
               "2. Ввести ключ.\n"
               "3. Произвести шифровку\n"
               "4. Произвести дешифровку\n"
               "5. Выход\n");
        inputNat(&userChoice);

        if (userChoice < 1 || userChoice > 5)
        {
            printf("Введите значение от 1 до 5!\n");
            continue;
        }

        switch (userChoice)
        {
            // Ввод сообщения
            case (textInput):
            {
                printf("Хотите ли вы считать сообщение с консоли или с файла?(1/0)\n");
                inputNat(&fileChoice);

                if (fileChoice == 1)
                {
                    printf("Введите текст для шифрования:\n");
                    inputCorrectString(&message);
                }
                else if (fileChoice == 0)
                {
					// Работа с текстовым файлом
                    FILE *fileMessage;

                    message = (char*) malloc(MAX_FILE_STRING_NUMBER * sizeof(char));

                    fileMessage = fopen("C:\\Users\\alekc\\Desktop\\Learning\\OP2\\Laba3\\message.txt", "r");
                    fgets(message, MAX_FILE_STRING_NUMBER, fileMessage);
                    fclose(fileMessage);

                    correctString(message);
                }
                else
                    printf("Вы должны были ввести 1 или 0(\n");
                break;
            }
			// Ввод ключа
            case (keyInput):
            {
                printf("Хотите ли вы считать сообщение с консоли или с файла?(1/0)\n");
                inputNat(&fileChoice);

                if (fileChoice == 1)
                {
                    printf("Введите ключ:\n");
                    inputCorrectString(&key);
                }
                else if (fileChoice == 0)
                {
                    FILE *fileMessage;
                    key = (char*) malloc(MAX_FILE_STRING_NUMBER * sizeof(char));

                    fileMessage = fopen("C:\\Users\\alekc\\Desktop\\Learning\\OP2\\Laba3\\key.txt", "r");
                    fgets(key, MAX_FILE_STRING_NUMBER, fileMessage);
                    fclose(fileMessage);

                    correctString(key);
                }
                else
                    printf("Вы должны были ввести 1 или 0(\n");
                break;
            }
			// Шифрование
            case (encrypt):
            {
                char* encodeMessage;

                if (message == NULL || key == NULL)
                {
                    printf("Сначала введите сообщение и ключ!\n");
                    continue;
                }

                encodeMessage = encode(message, key);
                puts(encodeMessage);
                break;
            }
			// Дешифровка
            case (decrypt):
            {
                char* decodeMessage;

                if (strlen(message) == 0 || strlen(key) == 0)
                {
                    printf("Сначала введите сообщение и ключ!\n");
                    continue;
                }

                decodeMessage = decode(message, key);
                puts(decodeMessage);
                break;
            }
			// Выход
            case (exitProg):
            {
                free(message);
                free(key);
                exit(1);
                break;
            }

        }

    }while (1);
}