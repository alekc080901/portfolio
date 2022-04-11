#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <string.h>
#include <time.h>

typedef struct _list {
    struct tm date;
    struct _list* next;
    struct _list* prev;
} Node;

struct filterOutput
{
    Node* dateHead;
    Node* dateTail;
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

// ������� ��������� ������ ��� �� ������������� ����� �� ����������� ��� ��������
// � ������� ����� ����� ����������� ���� ��� ������� �����, ���������� �� �������� ��������� �� ���
void sortArray(Node** head, char* key, int order)
{
    struct tm temp;

    if (strcmp(key, "seconds") == 0)
    {
        // ���������� ���������
        for (Node* i = (*head); i != NULL; i = i->next)
            for (Node* j = (*head); j != NULL; j = j->next)
                if (order)  // �� �����������
                {
                    if (i->date.tm_sec < j->date.tm_sec)
                    {
                        temp = i->date;  // ������ ������������ ����!
                        i->date = j->date;
                        j->date = temp;
                    }
                }
                else  // �� ��������
                if (i->date.tm_sec > j->date.tm_sec)
                {
                    temp = i->date;
                    i->date = j->date;
                    j->date = temp;
                }

    }

    else if (strcmp(key, "minutes") == 0)
    {
        for (Node* i = (*head); i != NULL; i = i->next)
            for (Node* j = (*head); j != NULL; j = j->next)
                if (order)  // �� �����������
                {
                    if (i->date.tm_min < j->date.tm_min)
                    {
                        temp = i->date;
                        i->date = j->date;
                        j->date = temp;
                    }
                }
                else  // �� ��������
                if (i->date.tm_min > j->date.tm_min)
                {
                    temp = i->date;
                    i->date = j->date;
                    j->date = temp;
                }
    }

    else if (strcmp(key, "hours") == 0)
    {
        for (Node* i = (*head); i != NULL; i = i->next)
            for (Node* j = (*head); j != NULL; j = j->next)
                if (order)  // �� �����������
                {
                    if (i->date.tm_hour < j->date.tm_hour)
                    {
                        temp = i->date;
                        i->date = j->date;
                        j->date = temp;
                    }
                }
                else  // �� ��������
                if (i->date.tm_hour > j->date.tm_hour)
                {
                    temp = i->date;
                    i->date = j->date;
                    j->date = temp;
                }
    }

    else if (strcmp(key, "monthday") == 0)
    {
        for (Node* i = (*head); i != NULL; i = i->next)
            for (Node* j = (*head); j != NULL; j = j->next)
                if (order)  // �� �����������
                {
                    if (i->date.tm_mday < j->date.tm_mday)
                    {
                        temp = i->date;
                        i->date = j->date;
                        j->date = temp;
                    }
                }
                else  // �� ��������
                if (i->date.tm_mday > j->date.tm_mday)
                {
                    temp = i->date;
                    i->date = j->date;
                    j->date = temp;
                }
    }

    else if (strcmp(key, "weekday") == 0)
    {
        for (Node* i = (*head); i != NULL; i = i->next)
            for (Node* j = (*head); j != NULL; j = j->next)
                if (order)  // �� �����������
                {
                    if (i->date.tm_wday < j->date.tm_wday)
                    {
                        temp = i->date;
                        i->date = j->date;
                        j->date = temp;
                    }
                }
                else  // �� ��������
                if (i->date.tm_wday > j->date.tm_wday)
                {
                    temp = i->date;
                    i->date = j->date;
                    j->date = temp;
                }
    }

    else if (strcmp(key, "month") == 0)
    {
        for (Node* i = (*head); i != NULL; i = i->next)
            for (Node* j = (*head); j != NULL; j = j->next)
                if (order)  // �� �����������
                {
                    if (i->date.tm_mon < j->date.tm_mon)
                    {
                        temp = i->date;
                        i->date = j->date;
                        j->date = temp;
                    }
                }
                else  // �� ��������
                if (i->date.tm_mon > j->date.tm_mon)
                {
                    temp = i->date;
                    i->date = j->date;
                    j->date = temp;
                }
    }

    else if (strcmp(key, "year") == 0)
    {
        for (Node* i = (*head); i != NULL; i = i->next)
            for (Node* j = (*head); j != NULL; j = j->next)
                if (order)  // �� �����������
                {
                    if (i->date.tm_year < j->date.tm_year)
                    {
                        temp = i->date;
                        i->date = j->date;
                        j->date = temp;
                    }
                }
                else  // �� ��������
                if (i->date.tm_year > j->date.tm_year)
                {
                    temp = i->date;
                    i->date = j->date;
                    j->date = temp;
                }
    }

    else
        puts("������� ���������� ����!");
}

// ���������� ������ �������� � ���������� ������
void add(Node** head, Node** tail, struct tm date)
{
    Node* array = (Node*)malloc(sizeof(Node));
    array->next = NULL;
    array->prev = NULL;
    array->date = date;

    if(*head == NULL)
        *head = *tail = array;
    else {
        (*tail)->next = array;
        array->prev = *tail;
        *tail  = array;
    }
}

// ������� ���������� ������� ������ �� ��� ����������� ������
Node* extract(Node* head, int position)
{
    int count = 0;

    if (position < 0)
        return NULL;

    if (head == NULL)
        return NULL;

    while (1)
    {
        if (count == position)
            break;
        head = head->next;
        count++;
    }
    return head;
}

// �������� �������� ��� ����������, ������� ����� �������������� � ������� ����
struct filterOutput filterAlgorithm(Node* head, char* key)
{
    int number = 0;
    int keyLen = 0;
    int filterVar = 0;
    Node* newHead = NULL;
    Node* newTail = NULL;

    struct filterOutput output;

    for (Node* i = head; i != NULL; i = i->next)
    {
        // � ���������� key �������� ���� ��� �������. ������ �������� �������� ���������� �������� ��� ������ �� �����
        if (strstr(key, "seconds") != NULL)
        {
            filterVar = i->date.tm_sec;
            keyLen = strlen("seconds");
        }
        else if (strstr(key, "minutes") != NULL)
        {
            filterVar = i->date.tm_min;
            keyLen = strlen("minutes");
        }
        else if (strstr(key, "hours") != NULL)
        {
            filterVar = i->date.tm_hour;
            keyLen = strlen("hours");
        }
        else if (strstr(key, "weekday") != NULL)
        {
            filterVar = i->date.tm_wday + 1;
            keyLen = strlen("weekday");
        }
        else if (strstr(key, "monthday") != NULL)
        {
            filterVar = i->date.tm_mday;
            keyLen = strlen("monthday");
        }
        else if (strstr(key, "month") != NULL)
        {
            filterVar = i->date.tm_mon + 1;
            keyLen = strlen("month");
        }
        else if (strstr(key, "year") != NULL)
        {
            filterVar = i->date.tm_year + 1900; // ��������������� ���������� � 1900 ����
            keyLen = strlen("year");
        }
        puts("2");

        number = atoi(key + keyLen + 1);

        if (number == 0)
        {
            output.dateHead = NULL;
            output.dateTail = NULL;
            output.error = 1;
            return output;
        }

        if (key[keyLen] == '>')
        {
            if (filterVar > number)
                add(&newHead, &newTail, i->date);
        }

        if (key[keyLen] == '<')
        {
            if (filterVar < number)
                add(&newHead, &newTail, i->date);
        }

        if (key[keyLen] == '=')
        {
            if (filterVar == number)
                add(&newHead, &newTail, i->date);
        }
    }

    output.dateHead = newHead;
    output.dateTail = newTail;
    output.error = 0;
    return output;
}

// ������� ������� ����������
struct filterOutput filter(Node* head, char* key)
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
        output.dateHead = NULL;
        output.dateTail = NULL;
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
            output = filterAlgorithm(head, keys[i]);
            checker = 1;
        }

        keyLen = strlen("minutes");
        if (strstr(keys[i], "minutes") != 0 &&
            (keys[i][keyLen] == '=' || keys[i][keyLen] == '>' || keys[i][keyLen] == '<')
            && strlen(keys[i]) > keyLen)
        {
            output = filterAlgorithm(head, keys[i]);
            if (output.error != 0)
                checker = 1;
        }

        keyLen = strlen("hours");
        if (strstr(keys[i], "hours") != 0 &&
            (keys[i][keyLen] == '=' || keys[i][keyLen] == '>' || keys[i][keyLen] == '<')
            && strlen(keys[i]) > keyLen)
        {
            output = filterAlgorithm(head, keys[i]);
            if (output.error != 0)
                checker = 1;
        }

        keyLen = strlen("weekday");
        if (strstr(keys[i], "weekday") != 0 &&
            (keys[i][keyLen] == '=' || keys[i][keyLen] == '>' || keys[i][keyLen] == '<')
            && strlen(keys[i]) > keyLen)
        {
            output = filterAlgorithm(head, keys[i]);
            if (output.error != 0)
                checker = 1;
        }

        keyLen = strlen("monthday");
        if (strstr(keys[i], "monthday") != 0 &&
            (keys[i][keyLen] == '=' || keys[i][keyLen] == '>' || keys[i][keyLen] == '<')
            && strlen(keys[i]) > keyLen)
        {
            output = filterAlgorithm(head, keys[i]);
            if (output.error != 0)
                checker = 1;
        }

        keyLen = strlen("month");
        if (strstr(keys[i], "month") != 0 &&
            (keys[i][keyLen] == '=' || keys[i][keyLen] == '>' || keys[i][keyLen] == '<')
            && strlen(keys[i]) > keyLen)
        {
            output = filterAlgorithm(head, keys[i]);
            if (output.error != 0)
                checker = 1;
        }

        keyLen = strlen("year");
         if (strstr(keys[i], "year") != 0 && (keys[i][keyLen] == '=' || keys[i][keyLen] == '>' || keys[i][keyLen] == '<')
            && strlen(keys[i]) > keyLen)
        {
            output = filterAlgorithm(head, keys[i]);
            if (output.error != 0)
                checker = 1;
        }
    }
    if (checker == 0)
    {
        output.dateHead = NULL;
        output.dateTail = NULL;
        output.error = 1;
    }
    return output;
}

// ������� ����, ���������� � ������
void listOutput(Node* head, int enumerate)
{
    int count = 0;
    if (enumerate)
    for(Node* i = head; i != NULL; i = i->next)
    {
        count++;
        printf("%d: %s\n", count, asctime(&i->date));
    }
    else
        for(Node* i = head; i != NULL; i = i->next)
            printf("%s\n", asctime(&i->date));
}

// ����������� ����� ������
int len(Node* head)
{
    int count = 0;
    for(Node* i = head; i != NULL; i = i->next)
        count++;
    return count;
}


void listFree(Node** head, Node** tail) {
    Node* tmp, *nextElem = *head;
    while(nextElem != NULL) {
        tmp = nextElem;
        nextElem = nextElem->next;
        free(tmp);
    }
    *head = *tail = NULL;
}

void deleteElem(Node** head, Node** tail, int index)
{
    Node* elem4Delete;

    elem4Delete = extract(*head, index);

    if (len(*head) == 1)
    {
        *head = NULL;
        *tail = NULL;
    }

    else if (elem4Delete==(*head)) // ���� ������� ��� �������� ������
    {
        (*head) = (*head)->next;
        (*head)->prev = NULL;
        free(elem4Delete);
    }
    else if (elem4Delete==(*tail)) // ���� ������� ��� �������� ���������
    {
        (*tail) = (*tail)->prev;
        (*tail)->next = NULL;
        free(elem4Delete);
    }
    else  // �������� �� ������� ������
    {
        elem4Delete->next->prev = elem4Delete->prev;
        if(elem4Delete->next)
            elem4Delete->prev->next = elem4Delete->next;
        free(elem4Delete);
    }
}

void invert(Node** head)
{
    Node* temp = NULL;
    Node* current = *head;

    while (current !=  NULL)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if(temp != NULL )
        *head = temp->prev;
}

int main()
{
    int userChoice = 0;
    long int second = 0;

    struct tm currentDate;

    Node* head = NULL, *tail = NULL;

    char* standard = NULL;

    setlocale(LC_ALL, "");

    enum Case {dateInput = 1, transform2UTC, calculateInterval, chooseDate, dataDel, dataOutput,
            sort, filterList, showLength, invertList, loadData, dataSave, exitProg};

    FILE *file;

    do
    {
        printf("\n������ � �����:                           ������ �� ������� ���:                 ������ � ������:\n"
               "1. ������ ����.                           4. ������� ���� �� ������.             11. ��������� ���� �� ����� � ������.\n"
               "2. ������������� � �������� UTC.          5. ������� ���� �� ������.             12. ��������� ���� � ���� �� ������.\n"
               "3. ��������� ����������.                  6. ������� ������ ���.\n����� ����� ������.                "
               "       7. ������������� ���� � �������.\n"
               "                                          8. ������������� ���� � ������.\n"
               "                                                   �����!!!\n"
               "                                          9. ������� ����� ������.\n"
               "                                          10 ������������� ������.\n\n\n"
               "                                          13. ����� �� ���������\n");
        inputNat(&userChoice);

        if (userChoice < 1 || userChoice > 13)
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

                        add(&head, &tail, UNIX2UTC(second));

                        printf("���� ������� �������.\n");
                        break;
                    }

                    // ���� �������� ������� ��� ���������� �������. �������: ���� ���������� � "utc"
                    else if (strcmp(strstr(standard, "utc"), standard) == 0)
                    {
                        printf("������� ����� ���:\n");
                        inputNat(&currentDate.tm_mday);
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

                        add(&head, &tail, UTC2UTC(currentDate, standard));
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
                int count = 0;

                if (head==NULL)
                {
                    printf("������ � ������ ������!\n");
                    break;
                }

                listOutput(head, 1);

                printf("������� ������������ ��� ����� ����:\n");
                inputNat(&dateChoice);

                // ���� ����� � ���������
                if (dateChoice >= 1 && dateChoice <= len(head))
                {
                    currentDate = extract(head, dateChoice - 1)->date;
                    standard = "utc";
                }
                else
                    printf("������� �������� � ���������� 1-%d\n", len(head));
                break;
            }

            // ������� ���� �� �������. ������� ������ ���������� � ������� ����
            case (dataDel):
            {
                int dateChoice = 0;

                if (head==NULL)
                {
                    printf("������ � ������ ������!\n");
                    break;
                }

                listOutput(head, 1);

                printf("������� ������������ ��� ����� ����:\n");
                inputNat(&dateChoice);

                if (dateChoice >= 1 && dateChoice <= len(head))
                {
                    deleteElem(&head, &tail, dateChoice - 1);
                    printf("�������� ��������� �������\n");
                }
                else
                    printf("������� �������� � ���������� 1-%d\n", len(head));
                break;
            }

            // ����� ����
            case(dataOutput):
            {
                listOutput(head, 0);
                break;
            }

            // ��������������� ������ �� ��������� ������������� �����
            case (sort):
            {
                int order = 0;
                char* field = NULL;

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

                sortArray(&head, field, order);
                break;
            }

            // ��������� ������ �� ������ ��� ���������� ���������
            case (filterList):
            {
                char* keyFilterChoice = NULL;

                struct filterOutput out;

                if (head == NULL)
                {
                    printf("���� ������ �����!\n");
                    break;
                }

                printf("�� ����� ����� �� ������ ���������� ����������?\n"
                       "��������� ����: seconds, minutes, hours, monthday, weekday, month, year:\n"
                       "���� ����������� ����� �������. ������ ����������: year>2000,month=3\n");
                inputString(&keyFilterChoice);

                out = filter(head, keyFilterChoice);
                if (out.error == 1) // ������������ �������
                {
                    printf("������� ���������� ������� ����������!\n");
                    break;
                }
                else if (out.dateHead == NULL) // NULL - ������� ������ �� �������������
                {
                    printf("�� ������� ������� ������ �� �������.\n");
                    break;
                }

                listFree(&head, &tail);
                head = out.dateHead;
                tail = out.dateTail;
                listOutput(head, 0);
                break;
            }

            // ������� ����� ������
            case(showLength):
            {
                printf("����� ������: %d\n", len(head));
                break;
            }

            // ����������� ������
            case(invertList):
            {
                invert(&head);
                listOutput(head, 0);
                break;

            }

            // ��������� ���������� �� ����� � ������
            case (loadData):
            {
                struct tm date;

                file = fopen("datebase.txt","r");

                if (file==NULL)
                {
                    printf("���� �����������. �� ����� ������ �������������. ����������, ��������� �������\n");
                    file = fopen("datebase.txt","w");
                    fclose(file);
                    break;
                }

                listFree(&head, &tail); // ������� ������� ��� �������� ������
                while (!feof(file))
                {
                    fread(&date, sizeof(struct tm), 1, file);
                    add(&head, &tail, date);
                }
                tail = tail->prev;
                tail->next = NULL;

                fclose(file);

                printf("������ ������� ���������.\n");
                break;
            }


            // ��������� ���������� �� ������� � ����
            case (dataSave):
                {
                    if (head == NULL)
                    {
                        puts("������� ��������� ������!");
                        break;
                    }

                    file = fopen("datebase.txt", "w");
                    for (Node* i = head; i != NULL; i = i->next)
                        fwrite(&i->date, sizeof(struct tm), 1, file);
                    fclose(file);

                    printf("���� ���� ������������� ������������� � ������ UTC � ��������� � ����.\n");
                    break;
                }

            case (exitProg):
            {
                listFree(&head, &tail);
                exit(1);
                break;
            }
        }

    }while (1);
}
