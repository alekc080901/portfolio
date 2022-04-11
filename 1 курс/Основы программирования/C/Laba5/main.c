#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <string.h>
#include <time.h>

struct filterOutput
{
    int length;
    struct tm* dateArray;
    int error;
};

// ���� ������ �����
void inputNat(int* number)
{
    while (!scanf("%d", number))
    {
        fflush(stdin);
        printf("������� ���������� ������!\n");
    }
    if (*number < 0)
    {
        printf("����� ������ ���� ����������� ��� 0!\n");
        inputNat(number);
    }
}

// ���� ������ ������������
void inputString(char** word)
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
}

// ��������� ������������ ����� ��������� �����������
char* checkStandard(char* standard)
{
    int timezoneUTC = 0;

    standard = strlwr(standard);
    // ��������  UNIX
    if (strcmp(standard, "unix") == 0)
    {
        return "unix";
    }
        // �������� UTC. ���� ��������� �� ������ "utc"
    else if (strstr(standard, "utc") != NULL && strcmp(strstr(standard, "utc"), standard) == 0)
    {
        // ������� �����
        if (strlen(standard) == 3)
            return "utc";

            // ������� ����
        else if (strlen(standard) == 6 && (standard[3] == '+' || standard[3] == '-'))
        {
            timezoneUTC = atoi(standard + 3);
            if (timezoneUTC == 0 || timezoneUTC > 12 || timezoneUTC < -12)
            {
                printf("�� ����� ������������ ������� ���� (���������� �� -12 �� 12)!\n");
                return NULL;
            }
            return standard;
        }
    }
    printf("�������� ������ ���������!\n");
    return NULL;
}

// ��������������� ��������� ����� � ��������
struct tm UTC2UTC(struct tm date, char* standard)
{
    int tempDate = 0;
    int timezoneUTC = 0;

    // ���� ����� �� �������, ������� �������� �� ��������� ����
    if (strlen(standard) > 3)
        timezoneUTC = atoi(standard + 3);

    // ��������������
    tempDate = mktime(&date);
    tempDate -= timezoneUTC * 3600 + timezone; // ���������� ���������� timezone �� ���������� time.h ������ � ����
    date = *gmtime(&tempDate);  // ������� ���������� ������� ���������� � �������

    return date;
}

// ��������������� ����� � �������� (�������� UNIX) � �������
struct tm UNIX2UTC(int seconds)
{
    struct tm date;

    date = *gmtime(&seconds);

    return date;
}

// ������� �� ������� ���� �� ����������� ������
struct tm* deleteDate(struct tm* dateBase, int length, int index)
{
    struct tm* newDateBase;
    newDateBase = (struct tm*) malloc(sizeof(struct tm) * (length-1));

    // �������� ������ ������� ��� ����� ���������� ��������
    for (int i = 0; i < length; i++)
    {
        if (i >= index)
            newDateBase[i] = dateBase[i+1];
        else
            newDateBase[i] = dateBase[i];
    }

    return newDateBase;
}

// ������� ��������� ������ ��� �� ������������� ����� �� ����������� ��� ��������
// � ������� ����� ����� ����������� ���� ��� ������� �����, ���������� �� �������� ��������� �� ���
struct tm* sortArray(struct tm* dateBase, int length, char* key, int order)
{
    struct tm temp;

    if (strcmp(key, "seconds") == 0)
    {
        // ���������� ���������
        for (int i = 0; i < length; i++)
            for (int j = i; j < length; j++)
                if (order)  // �� �����������
                {
                    if (dateBase[i].tm_sec > dateBase[j].tm_sec)
                    {
                        temp = dateBase[i];
                        dateBase[i] = dateBase[j];
                        dateBase[j] = temp;
                    }
                }
                else  // �� ��������
                if (dateBase[i].tm_sec < dateBase[j].tm_sec)
                {
                    temp = dateBase[i];
                    dateBase[i] = dateBase[j];
                    dateBase[j] = temp;
                }
    }

    else if (strcmp(key, "minutes") == 0)
    {
        for (int i = 0; i < length; i++)
            for (int j = i; j < length; j++)
                if (order)  // �� �����������
                {
                    if (dateBase[i].tm_min > dateBase[j].tm_min)
                    {
                        temp = dateBase[i];
                        dateBase[i] = dateBase[j];
                        dateBase[j] = temp;
                    }
                }
                else  // �� ��������
                if (dateBase[i].tm_min < dateBase[j].tm_min)
                {
                    temp = dateBase[i];
                    dateBase[i] = dateBase[j];
                    dateBase[j] = temp;
                }
    }

    else if (strcmp(key, "hours") == 0)
    {
        for (int i = 0; i < length; i++)
            for (int j = i; j < length; j++)
                if (order)  // �� �����������
                {
                    if (dateBase[i].tm_hour > dateBase[j].tm_hour)
                    {
                        temp = dateBase[i];
                        dateBase[i] = dateBase[j];
                        dateBase[j] = temp;
                    }
                }
                else  // �� ��������
                if (dateBase[i].tm_hour < dateBase[j].tm_hour)
                {
                    temp = dateBase[i];
                    dateBase[i] = dateBase[j];
                    dateBase[j] = temp;
                }
    }

    else if (strcmp(key, "monthday") == 0)
    {
        for (int i = 0; i < length; i++)
            for (int j = i; j < length; j++)
                if (order)  // �� �����������
                {
                    if (dateBase[i].tm_mday > dateBase[j].tm_mday)
                    {
                        temp = dateBase[i];
                        dateBase[i] = dateBase[j];
                        dateBase[j] = temp;
                    }
                }
                else  // �� ��������
                if (dateBase[i].tm_mday < dateBase[j].tm_mday)
                {
                    temp = dateBase[i];
                    dateBase[i] = dateBase[j];
                    dateBase[j] = temp;
                }
    }

    else if (strcmp(key, "weekday") == 0)
    {
        for (int i = 0; i < length; i++)
            for (int j = i; j < length; j++)
                if (order)  // �� �����������
                {
                    if (dateBase[i].tm_wday > dateBase[j].tm_wday)
                    {
                        temp = dateBase[i];
                        dateBase[i] = dateBase[j];
                        dateBase[j] = temp;
                    }
                }
                else  // �� ��������
                if (dateBase[i].tm_wday < dateBase[j].tm_wday)
                {
                    temp = dateBase[i];
                    dateBase[i] = dateBase[j];
                    dateBase[j] = temp;
                }
    }

    else if (strcmp(key, "month") == 0)
    {
        for (int i = 0; i < length; i++)
            for (int j = i; j < length; j++)
                if (order)  // �� �����������
                {
                    if (dateBase[i].tm_mon > dateBase[j].tm_mon)
                    {
                        temp = dateBase[i];
                        dateBase[i] = dateBase[j];
                        dateBase[j] = temp;
                    }
                }
                else  // �� ��������
                if (dateBase[i].tm_mon < dateBase[j].tm_mon)
                {
                    temp = dateBase[i];
                    dateBase[i] = dateBase[j];
                    dateBase[j] = temp;
                }
    }

    else if (strcmp(key, "year") == 0)
    {
        for (int i = 0; i < length; i++)
            for (int j = i; j < length; j++)
                if (order)  // �� �����������
                {
                    if (dateBase[i].tm_year > dateBase[j].tm_year)
                    {
                        temp = dateBase[i];
                        dateBase[i] = dateBase[j];
                        dateBase[j] = temp;
                    }
                }
                else  // �� ��������
        if (dateBase[i].tm_year < dateBase[j].tm_year)
        {
            temp = dateBase[i];
            dateBase[i] = dateBase[j];
            dateBase[j] = temp;
        }
    }

    else
        return NULL;

    return dateBase;
}
// �������� �������� ��� ����������, ������� ����� �������������� � ������� ����
struct filterOutput filterAlgorithm(struct tm* dateBase, int length, char* key)
{
    int number = 0;
    int keyLen = 0;
    int count = 0;
    int filterVar = 0;
    struct tm* newDateBase = NULL;

    struct filterOutput output;

    for (int j = 0; j < length; j++)
    {
        // � ���������� key �������� ���� ��� �������. ������ �������� �������� ���������� �������� ��� ������ �� �����
        if (strstr(key, "seconds") != NULL)
        {
            filterVar = dateBase[j].tm_sec;
            keyLen = strlen("seconds");
        }
        else if (strstr(key, "minutes") != NULL)
        {
            filterVar = dateBase[j].tm_min;
            keyLen = strlen("minutes");
        }
        else if (strstr(key, "hours") != NULL)
        {
            filterVar = dateBase[j].tm_hour;
            keyLen = strlen("hours");
        }
        else if (strstr(key, "weekday") != NULL)
        {
            filterVar = dateBase[j].tm_wday + 1;
            keyLen = strlen("weekday");
        }
        else if (strstr(key, "monthday") != NULL)
        {
            filterVar = dateBase[j].tm_mday;
            keyLen = strlen("monthday");
        }
        else if (strstr(key, "month") != NULL)
        {
            filterVar = dateBase[j].tm_mon + 1;
            keyLen = strlen("month");
        }
        else if (strstr(key, "year") != NULL)
        {
            filterVar = dateBase[j].tm_year + 1900; // ��������������� ���������� � 1900 ����
            keyLen = strlen("year");
        }

        number = atoi(key + keyLen + 1);

        if (number == 0)
        {
            output.length = 0;
            output.dateArray = NULL;
            output.error = 1;
            return output;
        }

        if (key[keyLen] == '>')
        {
            if (filterVar > number)
            {
                newDateBase = realloc(newDateBase, sizeof(struct tm) * (count + 1));
                newDateBase[count] = dateBase[j];
                count++;
            }
        }

        if (key[keyLen] == '<')
        {
            if (filterVar < number)
            {
                newDateBase = realloc(newDateBase, sizeof(struct tm) * (count + 1));
                newDateBase[count] = dateBase[j];
                count++;
            }
        }

        if (key[keyLen] == '=')
        {
            if (filterVar == number)
            {
                newDateBase = realloc(newDateBase, sizeof(struct tm) * (count + 1));
                newDateBase[count] = dateBase[j];
                count++;
            }
        }
    }

    output.length = count;
    output.dateArray = newDateBase;
    output.error = 0;
    return output;
}

// ������� ������� ����������
struct filterOutput filter(struct tm* dateBase, int length, char* key)
{
    int count = 0;
    int keysNumber = 0;
    int keyLen = 0;
    int checker = 0;
    char *correctKey = NULL;
    char **keys = NULL;

    struct filterOutput output;

    // ���� ���� ������� ������ �� ��������
    if (strspn(key, " ") == strlen(key))
    {
        output.dateArray = NULL;
        output.length = 0;
        output.error = 1;
        return output;
    }

    // �������� �������� �� �������
    for (int i = 0; i < strlen(key); i++)
        if (key[i] != ' ')
        {
            count++;
            correctKey = realloc(correctKey, sizeof(char) * (count));
            correctKey[count - 1] = key[i];
        }
    correctKey[count] = '\0';
    // ���������� ������ �� �������
    keys = (char **) malloc(sizeof(char *));
    keys[0] = strtok(correctKey, ",");

    while (keys[keysNumber] != NULL)
    {
        keysNumber++;
        keys = realloc(keys, sizeof(char *) * (keysNumber + 1));
        keys[keysNumber] = strtok(NULL, ",");
    }

    // ���� ��� ������� �� �������
    for (int i = 0; i < keysNumber; i++)
    {
        keyLen = strlen("seconds");
        // ���� ���������� � seconds, ��������� ����� ���� ������� - >, < ��� =, � ����� ��� ��� ���-�� ������ ����
        if (strstr(keys[i], "seconds") != 0 &&
            (keys[i][keyLen] == '=' || keys[i][keyLen] == '>' || keys[i][keyLen] == '<')
            && strlen(keys[i]) > keyLen)
        {
            output = filterAlgorithm(dateBase, length, keys[i]);
            length = output.length;
            memcpy(dateBase, output.dateArray, sizeof(struct tm) * length);
            checker = 1;
        }

        keyLen = strlen("minutes");
        if (strstr(keys[i], "minutes") != 0 &&
            (keys[i][keyLen] == '=' || keys[i][keyLen] == '>' || keys[i][keyLen] == '<')
            && strlen(keys[i]) > keyLen)
        {
            output = filterAlgorithm(dateBase, length, keys[i]);
            if (output.error != 0)
            {
                length = output.length;
                memcpy(dateBase, output.dateArray, sizeof(struct tm) * length);
                checker = 1;
            }
        }

        keyLen = strlen("hours");
        if (strstr(keys[i], "hours") != 0 &&
            (keys[i][keyLen] == '=' || keys[i][keyLen] == '>' || keys[i][keyLen] == '<')
            && strlen(keys[i]) > keyLen)
        {
            output = filterAlgorithm(dateBase, length, keys[i]);
            if (output.error != 0)
            {
                length = output.length;
                memcpy(dateBase, output.dateArray, sizeof(struct tm) * length);
                checker = 1;
            }
        }

        keyLen = strlen("weekday");
        if (strstr(keys[i], "weekday") != 0 &&
            (keys[i][keyLen] == '=' || keys[i][keyLen] == '>' || keys[i][keyLen] == '<')
            && strlen(keys[i]) > keyLen)
        {
            output = filterAlgorithm(dateBase, length, keys[i]);
            if (output.error != 0)
            {
                length = output.length;
                memcpy(dateBase, output.dateArray, sizeof(struct tm) * length);
                checker = 1;
            }
        }

        keyLen = strlen("monthday");
        if (strstr(keys[i], "monthday") != 0 &&
            (keys[i][keyLen] == '=' || keys[i][keyLen] == '>' || keys[i][keyLen] == '<')
            && strlen(keys[i]) > keyLen)
        {
            output = filterAlgorithm(dateBase, length, keys[i]);
            if (output.error != 0)
            {
                length = output.length;
                memcpy(dateBase, output.dateArray, sizeof(struct tm) * length);
                checker = 1;
            }
        }

        keyLen = strlen("month");
        if (strstr(keys[i], "month") != 0 &&
            (keys[i][keyLen] == '=' || keys[i][keyLen] == '>' || keys[i][keyLen] == '<')
            && strlen(keys[i]) > keyLen)
        {
            output = filterAlgorithm(dateBase, length, keys[i]);
            if (output.error != 0)
            {
                length = output.length;
                memcpy(dateBase, output.dateArray, sizeof(struct tm) * length);
                checker = 1;
            }
        }

        keyLen = strlen("year");
         if (strstr(keys[i], "year") != 0 && (keys[i][keyLen] == '=' || keys[i][keyLen] == '>' || keys[i][keyLen] == '<')
            && strlen(keys[i]) > keyLen)
        {
            output = filterAlgorithm(dateBase, length, keys[i]);
            if (output.error != 0)
            {
                length = output.length;
                memcpy(dateBase, output.dateArray, sizeof(struct tm) * length);
                checker = 1;
            }
        }
    }
    if (checker == 0)
    {
        output.length = 0;
        output.dateArray = NULL;
        output.error = 1;
    }
    return output;
}

int main()
{
    int userChoice = 0;
    int objectsInArray = 0;
    long int second = 0;

    struct tm currentDate;

    struct tm* dateBase = NULL;

    char* standard = NULL;

    setlocale(LC_ALL, "");

    enum Case {dateInput = 1, transform2UTC, calculateInterval, chooseDate, dataDel, dataOutput,  sort, filterArray,
        loadData, dataSave, exitProg};

    FILE *file;

    do
    {
        printf("\n������ � �����:                                 ������ � �������� ���:                       ������ � ������:\n"
               "1. ������ ����.                           4. ������� ���� �� �������.             9. ��������� ���� �� �����.\n"
               "2. ������������� � �������� UTC.          5. ������� ���� �� �������.             10. ��������� ���� � ���� �� �������.\n"
               "3. ��������� ����������.                  6. ������� ������ ���.\n����� ����� ������.                "
               "       7. ������������� ���� � �������.\n"
               "                                          8. ������������� ���� � �������.\n\n\n"
               "                                          11. ����� �� ���������\n");
        inputNat(&userChoice);

        if (userChoice < 1 || userChoice > 11)
        {
            printf("������� �������� �� 1 �� 11!\n");
            continue;
        }

        switch (userChoice)
        {
            // ���� ���� � ����������. ���� ������������� ��������� � ������ � ������
            case(dateInput):
                {
                    char* correctStandard = NULL;
                    standard = NULL;

                    printf("������� �������� �������: UNIX, UTC ��� UTCxxx (�.�. UTC+07)\n");
                    inputString(&standard);

                    correctStandard = checkStandard(standard);
                    if (correctStandard == NULL)
                        break;

                    // ���� ���� ��������� UNIX, �.�. ����� ������������ � ���� ������, ������� � 1970 ����
                    if (strcmp(correctStandard, "unix") == 0)
                    {
                        printf("������� ���������� ������:\n");
                        inputNat(&second);

                        dateBase = realloc(dateBase, sizeof(struct tm) * (objectsInArray + 1));
                        dateBase[objectsInArray] = UNIX2UTC(second);
                        objectsInArray++;

                        printf("���� ������� �������.\n");
                        break;
                    }

                        // ���� �������� ������� ��� ���������� �������. �������: ���� ���������� � "utc"
                    else if (strcmp(strstr(standard, "utc"), standard) == 0)
                    {
                        printf("������� ����� ���:\n");
                        inputNat(&currentDate.tm_mday);
                        printf("������� ���������� ����� ��� ������:\n");
                        inputNat(&currentDate.tm_wday);
                        currentDate.tm_wday--;
                        printf("������� �����:\n");
                        inputNat(&currentDate.tm_mon);
                        currentDate.tm_mon--;
                        printf("������� ���:\n");
                        inputNat(&currentDate.tm_year);
                        currentDate.tm_year -= 1900;
                        printf("������� ���������� �����:\n");
                        inputNat(&currentDate.tm_hour);
                        printf("������� ���������� �����:\n");
                        inputNat(&currentDate.tm_min);
                        printf("������� ���������� ������:\n");
                        inputNat(&currentDate.tm_sec);

                        // ���� asctime �� ������� ��������� ���� � ������, �� ���������� NULL
                        if (!asctime(&currentDate))
                        {
                            printf("��������� ���� ���������� ��������!\n");
                            break;
                        }

                        dateBase = realloc(dateBase, sizeof(struct tm) * (objectsInArray + 1));
                        dateBase[objectsInArray] = UTC2UTC(currentDate, standard); // ������ � ������� � UTC
                        objectsInArray++;
                        break;
                    }
                }

                // ����������� ������� ���� � ������ UTC
            case (transform2UTC):
            {
                char* dateString = NULL;

                if (standard == NULL)
                {
                    printf("������� ������� ����!\n");
                    break;
                }

                    // UTC
                else if (strcmp(standard, "utc") == 0)
                {
                    printf("��������� ���� ��� � ������� UTC!\n");
                    break;
                }

                    // UNIX
                else if (strcmp(standard, "unix") == 0)
                {
                    currentDate = UNIX2UTC(second);
                    strcpy(standard, "utc");

                    // ����� ���� � ���� ��������
                    printf("UNIX: %d\n", second);
                    dateString = asctime(&currentDate);
                    printf("UTC: %s\n", dateString);
                    break;
                }

                    // UTCxxx
                else if (strlen(standard) == 6 && (standard[3] == '+' || standard[3] == '-'))
                {
                    // ������� �� ��������������
                    dateString = asctime(&currentDate);
                    printf("%s: %s\n", strupr(standard), dateString);

                    currentDate = UTC2UTC(currentDate, standard);
                    strcpy(standard, "utc");

                    //������� ����� ��������������
                    dateString = asctime(&currentDate);
                    printf("UTC: %s\n", dateString);

                    break;
                }
                else
                {
                    printf("� ��������� ���������� ���-�� �� ���...");
                    break;
                }
            }

                // ���������� �� ������� ����������� ��������� ���������� ����� ����� ������, �� � �����, ��� ����������
                // ����� ��������� ����� � ��������� �������� ����� ���������� � � ��� �� ������� �������� �������
            case(calculateInterval):
            {
                struct tm date;

                time_t currentTime = time(NULL);  // ������� �����
                time_t interval;

                int enteredTime = 0;

                if (standard == NULL)
                {
                    printf("������� ������� ����!\n");
                    break;
                }

                // ��� ���������� ����� �������� � �������
                enteredTime = (strcmp(standard, "unix") == 0) ? second  : mktime(&currentDate) - timezone;

                // Difftime �������� ����� ���� �� �����. ������, ����� ����� �� ���� �������������.
                interval = abs(difftime(enteredTime, currentTime));
                date = *gmtime(&interval);

                printf("���������� ����� ������:\n�����: %d; �����: %d; �����: %d; �����: %d; ������: %d\n",
                       date.tm_year - 70, date.tm_mday - 1, date.tm_hour, date.tm_min, date.tm_sec);
                break;
            }

                // ������� ���� ��� ������ �� �������
            case (chooseDate):
            {
                int dateChoice = 0;

                if (dateBase==NULL)
                {
                    printf("������ � ������ ������!\n");
                    break;
                }

                // ����� ���� ���
                for (int i = 0; i < objectsInArray; i++)
                    printf("%d: %s\n", i + 1, asctime(&dateBase[i]));

                printf("������� ������������ ��� ����� ����:\n");
                inputNat(&dateChoice);

                // ���� ����� � ���������
                if (dateChoice >= 1 && dateChoice <= objectsInArray)
                {
                    currentDate = dateBase[dateChoice - 1];
                    standard = "utc";
                }
                else
                    printf("������� �������� � ���������� 1-%d\n", objectsInArray);
                break;
            }

                // ������� ���� �� �������. ������� ������ ���������� � ������� ����
            case (dataDel):
            {
                int dateChoice = 0;

                if (dateBase==NULL)
                {
                    printf("������ � ������ ������!\n");
                    break;
                }

                for (int i = 0; i < objectsInArray; i++)
                    printf("%d: %s\n", i + 1, asctime(&dateBase[i]));

                printf("������� ������������ ��� ����� ����:\n");
                inputNat(&dateChoice);

                if (dateChoice >= 1 && dateChoice <= objectsInArray)
                {
                    objectsInArray--;
                    memcpy(dateBase, deleteDate(dateBase, objectsInArray, dateChoice-1),
                            sizeof(struct tm) * objectsInArray);
                    printf("�������� ��������� �������\n");
                }
                else
                    printf("������� �������� � ���������� 1-%d\n", objectsInArray);
                break;
            }

                // ����� ����
            case(dataOutput):
            {
                for (int i = 0; i < objectsInArray; i++)
                    printf("%s\n", asctime(&dateBase[i]));
                break;
            }

                // ��������������� ������ �� ��������� ������������� �����
            case (sort):
            {
                int order = 0;
                char* field = NULL;
                struct tm* tempBase;

                printf("�� ������ ���� �� ������ ���������� ����������?\n"
                       "��������� ����: seconds, minutes, hours, monthday, weekday, month, year:\n");
                inputString(&field);
                printf("�� ������ ���������� ���������� �� ����������� ��� ��������?(1/0)\n");
                inputNat(&order);

                if (order != 1 && order != 0)
                {
                    printf("������� 1 ��� 0!");
                    break;
                }
                tempBase = sortArray(dateBase, objectsInArray, field, order);

                if (tempBase == NULL)
                {
                    printf("������� ���������� �������� ����!\n");
                    break;
                }

                memcpy(dateBase, tempBase, sizeof(struct tm) * objectsInArray);

                printf("������ ������� �������������.\n");
                break;
            }

                // ��������� ������ �� ������ ��� ���������� ���������
            case (filterArray):
            {
                char* keyFilterChoice = NULL;

                struct filterOutput out;

                if (dateBase==NULL)
                {
                    printf("���� ������ �����!\n");
                    break;
                }

                printf("�� ����� ����� �� ������ ���������� ����������?\n"
                       "��������� ����: seconds, minutes, hours, monthday, weekday, month, year:\n"
                       "���� ����������� ����� �������. ������ ����������: year>2000,month=3\n");
                inputString(&keyFilterChoice);

                out = filter(dateBase, objectsInArray, keyFilterChoice);
                if (out.error == 1) // �������� 100 - ������������ ���� ��� ����������
                {
                    printf("������� ���������� ������� ����������!\n");
                    break;
                }
                else if (out.dateArray == NULL) // NULL - ������� ������ �� �������������
                {
                    printf("�� ������� ������� ������ �� �������.\n");
                    break;
                }

                memcpy(dateBase, out.dateArray, sizeof(struct tm) * out.length);
                objectsInArray = out.length;
                for (int i = 0; i < objectsInArray; i++)
                    printf("%s\n", asctime(&dateBase[i]));
                break;
            }

           // ��������� ���������� �� ����� � ������
            case (loadData):
            {
                file = fopen("datebase.txt","r");

                if (file==NULL)
                {
                    printf("���� �����������. �� ����� ������ �������������. ����������, ��������� �������\n");
                    file = fopen("datebase.txt","w");
                    fclose(file);
                    break;
                }

                // ������ ��������� � ����� ����� ���������� ���������� � �������
                fread(&objectsInArray, sizeof(int), 1, file);
                dateBase = (struct tm*) malloc(sizeof(struct tm) * objectsInArray);
                fread(dateBase, sizeof(struct tm), objectsInArray, file);

                fclose(file);

                printf("������ ������� ���������.\n");
                break;
            }


                // ��������� ���������� �� ������� � ����
            case (dataSave):
                {
                    // ������ ��������� ��������� ����� �������
                    file = fopen("datebase.txt", "w");
                    fwrite(&objectsInArray, sizeof(int), 1, file);
                    fclose(file);

                    // ������ ��������� �������� ����� ��������
                    file = fopen("datebase.txt", "a");
                    fwrite(dateBase, sizeof(struct tm), objectsInArray, file);
                    fclose(file);

                    printf("���� ���� ������������� ������������� � ������ UTC � ��������� � ����.\n");
                    break;
                }

            case (exitProg):
            {
                free(dateBase);
                exit(1);
                break;
            }
        }

    }while (1);
}
