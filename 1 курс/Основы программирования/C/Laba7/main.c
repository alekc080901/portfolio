#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// ��� �������� ���������� � �����
typedef struct
{
    char* login;
    char* password;
    char* name;
}userInfo;

// � ��� � ������������
typedef struct
{
    char* name;
    int size;
    int date;
}fileInfo;

// ������� ������ ���� ������
typedef struct _list1
{
    fileInfo data;
    struct _list1* next;
    struct _list1* prev;
    struct _list2** connection; // ������ ������
    int connectionLen;  // ��� �����
} ListFile;

// ������� ������ ���� �������������
typedef struct _list2
{
    userInfo data;
    struct _list2* next;
    struct _list2* prev;
    struct _list1** connection;
    int connectionLen;
} ListUser;

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

// ���� ������ ������������ �����
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

// ���������� ������ �������� � ���������� ������
void addFile(ListFile** head, ListFile** tail, fileInfo data)
{
    ListFile* array = (ListFile*)malloc(sizeof(ListFile));
    array->next = NULL;
    array->prev = NULL;
    array->connection = NULL;
    array->connectionLen = 0;
    array->data = data;

    if(*head == NULL)
        *head = *tail = array;
    else {
        (*tail)->next = array;
        array->prev = *tail;
        *tail  = array;
    }
}

void addUser(ListUser** head, ListUser** tail, userInfo data)
{
    ListUser* array = (ListUser*)malloc(sizeof(ListUser));
    array->next = NULL;
    array->prev = NULL;
    array->connection = NULL;
    array->connectionLen = 0;
    array->data = data;

    if(*head == NULL)
        *head = *tail = array;
    else {
        (*tail)->next = array;
        array->prev = *tail;
        *tail  = array;
    }
}

// ������� ���������� ������� ������ �� ��� ����������� ������
ListFile* extractFile(ListFile* head, int position)
{
    int count = 0;

    if (position < 0)
        return NULL;

    if (head == NULL)
        return NULL;

    while (1)
    {
        count++;
        if (count == position)
            break;
        head = head->next;
    }
    return head;
}

// ������� ���������� ������� ������ �� ��� ����������� ������
ListUser* extractUser(ListUser* head, int position)
{
    int count = 0;
    ListUser* temp = head;

    if (position < 0)
        return NULL;

    if (head == NULL)
        return NULL;

    while (1)
    {
        count++;
        if (count == position)
            break;
        temp = temp->next;
    }
    return temp;
}

int knowNumberFile(ListFile* head, ListFile* node)
{
    int position = 0;

    for (ListFile* i = head; i != NULL; i = i->next)
    {
        position++;
        if (i == node)
            return position;
    }

    return 0;
}

int knowNumberUser(ListUser* head, ListUser* node)
{
    int position = 0;

    for (ListUser* i = head; i != NULL; i = i->next)
    {
        position++;
        if (i == node)
            return position;
    }

    return 0;
}

// ������� ����������, ���������� � ������ ������
void fileOutput(ListFile* head)
{
    int count = 0;
    fileInfo data;
    for(ListFile* i = head; i != NULL; i = i->next)
    {
        data = i->data;
        count++;
        printf("%d:  ��������: %s; ������: %d ��; ���� ��������: %d\n",
               count, data.name, data.size, data.date);
    }
}

// ������� ����������, ���������� � ������ �������������
void userOutput(ListUser* head)
{
    int count = 0;
    userInfo data;
    for(ListUser* i = head; i != NULL; i = i->next)
    {
        data = i->data;
        count++;
        printf("%d:  �����: %s; ������: %s; �������� ���: %s\n",
               count, data.login, data.password, data.name);
    }
}

// ����������� ����� ������
int lenFile(ListFile* head)
{
    int count = 0;
    for(ListFile* i = head; i != NULL; i = i->next)
        count++;
    return count;
}

int lenUser(ListUser* head)
{
    int count = 0;
    for(ListUser* i = head; i != NULL; i = i->next)
        count++;
    return count;
}

// ������������ ������ �������
void listFileFree(ListFile** head, ListFile** tail) {
    ListFile* tmp, *nextElem = *head;
    while(nextElem != NULL) {
        tmp = nextElem;
        nextElem = nextElem->next;
        free(tmp);
    }
    *head = *tail = NULL;
}

void listUserFree(ListUser** head, ListUser** tail) {
    ListUser* tmp, *nextElem = *head;
    while(nextElem != NULL) {
        tmp = nextElem;
        nextElem = nextElem->next;
        free(tmp);
    }
    *head = *tail = NULL;
}

// �������� ������� �� �������
void deleteFile(ListFile** head, ListFile** tail, int index)
{
    ListFile* elem4Delete;

    elem4Delete = extractFile(*head, index);

    if (lenFile(*head) == 1)
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
    else  // �������� �� �������� ������
    {
        elem4Delete->next->prev = elem4Delete->prev;
        if(elem4Delete->next)
            elem4Delete->prev->next = elem4Delete->next;
        free(elem4Delete);
    }
}

void deleteUser(ListUser** head, ListUser** tail, int index)
{
    ListUser* elem4Delete;

    elem4Delete = extractUser(*head, index);

    if (lenUser(*head) == 1)
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
    else  // �������� �� �������� ������
    {
        elem4Delete->next->prev = elem4Delete->prev;
        if(elem4Delete->next)
            elem4Delete->prev->next = elem4Delete->next;
        free(elem4Delete);
    }
}

// ���������� ����� ����� ��������
void addConnectionFile(ListFile** src, ListUser** dest)
{
    puts("+");
    ListUser** connectionSrc = (*src)->connection;  // ������ ������ ������ ����� �����
    puts("-");
    ListFile** connectionDest = (*dest)->connection;  // ������ ������ ����� ����� �����

    int lengthSrc = (*src)->connectionLen;
    int lengthDest = (*dest)->connectionLen;

    for (int i = 0; i < lengthSrc; i++)
        if (connectionSrc[i] == *dest)
            return ;

    connectionSrc = realloc(connectionSrc, sizeof(ListUser*) * ((lengthSrc + 1)));
    connectionSrc[lengthSrc] = *dest;

    (*src)->connection = connectionSrc;
    (*src)->connectionLen++;

    connectionDest = realloc(connectionDest, sizeof(ListFile*) * ((lengthDest + 1)));
    connectionDest[lengthSrc] = *src;

    (*dest)->connection = connectionDest;
    (*dest)->connectionLen++;

    puts("end");
}

void addConnectionUser(ListUser** src, ListFile** dest)
{
    ListFile** connectionSrc = (*src)->connection;
    ListUser** connectionDest = (*dest)->connection;
    int lengthSrc = (*src)->connectionLen;
    int lengthDest = (*dest)->connectionLen;

    printf("%d\n", lengthSrc);
    puts("+");

    for (int i = 0; i < lengthSrc; i++)
        if (connectionSrc[i] == *dest)
            return ;

    connectionSrc = realloc(connectionSrc, sizeof(ListFile*) * ((lengthSrc + 1)));
    connectionSrc[lengthSrc] = *dest;

    (*src)->connection = connectionSrc;
    (*src)->connectionLen++;

    connectionDest = realloc(connectionDest, sizeof(ListUser*) * ((lengthDest + 1)));
    connectionDest[lengthSrc] = *src;

    (*dest)->connection = connectionDest;
    (*dest)->connectionLen++;

    free(connectionSrc);
    free(connectionDest);
}

// ������ ������� ���������� ����� ����� ���������
void fileSwap(ListFile** first, ListFile** second)
{
    fileInfo tempData;
    ListUser** tempConn;
    int tempLen;

    tempData = (*first)->data;
    (*first)->data = (*second)->data;
    (*second)->data = tempData;

    tempConn = (*first)->connection;
    (*first)->connection = (*second)->connection;
    (*second)->connection = tempConn;

    tempLen = (*first)->connectionLen;
    (*first)->connectionLen = (*second)->connectionLen;
    (*second)->connectionLen = tempLen;

    free(tempConn);
}

void userSwap(ListUser** first, ListUser** second)
{
    userInfo tempData;
    ListFile** tempConn;
    int tempLen;

    tempData = (*first)->data;
    (*first)->data = (*second)->data;
    (*second)->data = tempData;

    tempConn = (*first)->connection;
    (*first)->connection = (*second)->connection;
    (*second)->connection = tempConn;

    tempLen = (*first)->connectionLen;
    (*first)->connectionLen = (*second)->connectionLen;
    (*second)->connectionLen = tempLen;

    free(tempConn);
}

// ��������� ������ �� ����� �� ����� � ���������
void sortFile(ListFile** head, char* key, int order)
{
    ListFile* temp = NULL;
    if (strcmp(key, "size") == 0)
    {
        // ���������� ���������
        for (ListFile* i = (*head); i != NULL; i = i->next)
            for (ListFile* j = (*head); j != NULL; j = j->next)
                if (order)  // �� �����������
                {
                    if (i->data.size < j->data.size)
                        fileSwap(&i, &i->prev);
                }
                else  // �� ��������
                if (i->data.size > j->data.size)
                    fileSwap(&i, &i->next);

    }

    else if (strcmp(key, "date") == 0)
    {
        // ���������� ���������
        for (ListFile* i = (*head); i != NULL; i = i->next)
            for (ListFile* j = (*head); j != NULL; j = j->next)
                if (order)  // �� �����������
                {
                    if (i->data.date < j->data.date)
                        fileSwap(&i, &i->prev);
                }
                else  // �� ��������
                    if (i->data.date > j->data.date)
                        fileSwap(&i, &i->next);

    }

    else if (strcmp(key, "name") == 0)
    {
        // ���������� ���������
        for (ListFile* i = (*head); i != NULL; i = i->next)
            for (ListFile* j = i->next; j != NULL; j = j->next)
                if (order)  // �� �����������
                {
                    if (strcmp(i->data.name, j->data.name) > 0)
                        fileSwap(&i, &j);
                }
                else  // �� ��������
                    if (strcmp(i->data.name, j->data.name) < 0)
                        fileSwap(&i, &j);
    }
}

void sortUser(ListUser** head, char* key, int order)
{
    ListUser* temp = NULL;
    if (strcmp(key, "name") == 0)
    {
        // ���������� ���������
        for (ListUser* i = (*head); i != NULL; i = i->next)
            for (ListUser* j = i->next; j != NULL; j = j->next)
                if (order)  // �� �����������
                {
                    if (strcmp(i->data.name, j->data.name) > 0)
                        userSwap(&i, &j);
                }
                else  // �� ��������
                if (strcmp(i->data.name, j->data.name) < 0)
                    userSwap(&i, &j);
    }

    if (strcmp(key, "login") == 0)
    {
        // ���������� ���������
        for (ListUser* i = (*head); i != NULL; i = i->next)
            for (ListUser* j = i->next; j != NULL; j = j->next)
                if (order)  // �� �����������
                {
                    if (strcmp(i->data.login, j->data.login) > 0)
                        userSwap(&i, &j);
                }
                else  // �� ��������
                if (strcmp(i->data.login, j->data.login) < 0)
                    userSwap(&i, &j);
    }

    if (strcmp(key, "password") == 0)
    {
        // ���������� ���������
        for (ListUser* i = (*head); i != NULL; i = i->next)
            for (ListUser* j = i->next; j != NULL; j = j->next)
                if (order)  // �� �����������
                {
                    if (strcmp(i->data.password, j->data.password) > 0)
                        userSwap(&i, &j);
                }
                else  // �� ��������
                if (strcmp(i->data.password, j->data.password) < 0)
                    userSwap(&i, &j);
    }

}

void putString(char** string, FILE* file)
{
    for (int j = 0; j < strlen(*string); j++)
    {
        fputc(*string[j], file);
    }
    fputc(';', file);
}

void getString(char** string, FILE* file)
{
    int symbol = 0;
    char *word = NULL;
    int count = 0;

    while (!feof(file))
    {
        symbol = fgetc(file);
        if (symbol == -1)
        {
            *string = NULL;
            return ;
        }

        if ((char) symbol == ';')
            break;
        word = realloc(word, count + 1);
        word[count] = (char) symbol;
        count++;
    }
    *string = word;
}

void putFileNode(fileInfo data, FILE* file)
{
    fputs(data.name, file);
    fputc(';', file);
    fwrite(&data.date, sizeof(int), 1, file);
    fwrite(&data.size, sizeof(int), 1, file);
}

void putUserNode(userInfo data, FILE* file)
{
    fputs(data.name, file);
    fputc(';', file);
    fputs(data.login, file);
    fputc(';', file);
    fputs(data.password, file);
    fputc(';', file);
}

int main()
{
    FILE *dbFile;
    FILE *dbUser;
    FILE *connFile;

    int userChoice = 0;

    ListFile* headFile = NULL, *tailFile = NULL;
    ListUser* headUser = NULL, *tailUser = NULL;

    setlocale(LC_ALL, "");

    enum Case {fileInput=1, userInput, output, file2users, user2files, showConnection,
               loadData, saveData, delete,  sort, exitProg};

    do
    {
        puts("������� ��� �����:\n"
             "1. �������� ����\n"
             "2. �������� ������������\n"
             "3. ����� ���������� �� �����\n"
             "4. ������� ���� � ��������������\n"
             "5. ������� ������������ � �������\n"
             "6. ������� ����� � ���������� ��������\n"
             "7. ��������� ���������� �� �����\n"
             "8. ��������� ���������� � ����\n"
             "9. ������� ������� �� �������\n"
             "10. ������������� ������\n"
             "11. ����� �� ���������\n");
        inputNat(&userChoice);

        if (userChoice < 1 || userChoice > 13)
        {
            printf("������� �������� �� 1 �� 11!\n");
            continue;
        }

        switch (userChoice)
        {
            // ���� ������ ����� � ������������� ��� � ������
            case (fileInput):
            {
                fileInfo info;
                puts("������� ��� �����:");
                inputString(&info.name);
                puts("������� ������ �����:");
                inputNat(&info.size);
                puts("������� ���� �������� ����� (� ��������):");
                inputNat(&info.date);

                addFile(&headFile, &tailFile, info);
                break;
            }

            // ���� ������ ������������ � ������������� ��� � ������
            case (userInput):
            {
                userInfo info;
                puts("������� �����:");
                inputString(&info.login);
                puts("������� ������:");
                inputString(&info.password);
                puts("������� �������� ���:");
                inputString(&info.name);

                addUser(&headUser, &tailUser, info);
                break;
            }

            // ����� ���������� �� �������
            case (output):
            {
                puts("����� ���������� �� ������ ������� �� �����?\n");
                puts("1. ���������� � ���� ������;\n"
                          "2. ���������� � ���� �������������;\n"
                          "3. ���������� � ���� ������ � �������������.\n");
                inputNat(&userChoice);

                if (userChoice < 1 || userChoice > 3)
                {
                    printf("������� �������� �� 1 �� 3!\n");
                    break;
                }

                if (userChoice == 1)
                {
                    if (headFile != NULL)
                        fileOutput(headFile);
                    else
                        puts("���� ������ �����.");
                }
                if (userChoice == 2)
                {
                    if (headUser != NULL)
                        userOutput(headUser);
                    else
                        puts("���� ������ �����.");
                }
                if (userChoice == 3)
                {
                    puts("���������� � ������:\n");
                    if (headFile != NULL)
                        fileOutput(headFile);
                    else
                        puts("���� ������ �����.");

                    puts("���������� � �������������:\n");
                    if (headUser != NULL)
                        userOutput(headUser);
                    else
                        puts("���� ������ �����.");
                }
                break;
            }

            // �������� ������ � ���������� ����� � ��������������
            case (file2users):
            {
                ListFile* sourceFile = NULL;
                ListUser* destinationUser = NULL;

                puts("�������� ���� ��� ������:");
                fileOutput(headFile);
                inputNat(&userChoice);

                if (userChoice < 1 || userChoice > lenFile(headFile))
                {
                    printf("������� �������� �� 1 �� %d!\n", lenFile(headFile));
                    break;
                }

                sourceFile = extractFile(headFile, userChoice);
                while (userChoice != 0)
                {
                    puts("�������� ������������ ��� �������� ����� (0 ��� ������):\n");
                    userOutput(headUser);
                    inputNat(&userChoice);

                    if (userChoice == 0)
                        break;

                    if (userChoice < 1 || userChoice > lenUser(headUser))
                    {
                        printf("������� �������� �� 0 �� %d!\n", lenUser(headUser));
                        continue;
                    }

                    sourceFile = extractFile(headFile, userChoice);  // ����, �� �������� ���� �����
                    destinationUser = extractUser(headUser, userChoice);  // ����, � ������� ���� �����
                    addConnectionFile(&sourceFile, &destinationUser);
                }
                break;
            }

            // �������� ������ � ���������� ������������ � �������
            case (user2files):
            {
                ListUser* sourceUser = NULL;
                ListFile* destinationFile = NULL;

                puts("�������� ������������ ��� ������:");
                userOutput(headUser);
                inputNat(&userChoice);

                if (userChoice < 1 || userChoice > lenUser(headUser))
                {
                    printf("������� �������� �� 1 �� %d!\n", lenUser(headUser));
                    break;
                }

                while (userChoice != 0)
                {
                    puts("�������� ���� ��� �������� ����� (0 ��� ������):\n");
                    fileOutput(headFile);
                    inputNat(&userChoice);

                    if (!userChoice)
                        break;

                    if (userChoice < 1 || userChoice > lenFile(headFile))
                    {
                        printf("������� �������� �� 0 �� %d!\n", lenFile(headFile));
                        continue;
                    }

                    sourceUser = extractUser(headUser, userChoice);
                    destinationFile = extractFile(headFile, userChoice);
                    addConnectionUser(&sourceUser, &destinationFile);
                }
                break;
            }

            // ����� ������ � ��������� ������� ������
            case (showConnection):
            {
                int length = 0;
                puts("�� ������ �������� � ������� (1) ��� �������������� (0)?");
                inputNat(&userChoice);

                if (userChoice == 1)
                {
                    userInfo info;
                    ListUser** connections = NULL;
                    ListFile* currentFile = NULL;

                    puts("������� ����� �����:\n");
                    fileOutput(headFile);
                    inputNat(&userChoice);

                    if (userChoice < 1 || userChoice > lenFile(headFile))
                    {
                        printf("������� �������� �� 1 �� %d!\n", lenFile(headFile));
                        break;
                    }

                    // ��������� ���������� � ����� ���������� ������
                    currentFile = extractFile(headFile, userChoice);
                    connections = currentFile->connection;
                    length = currentFile->connectionLen;

                    if (length == 0)
                    {
                        puts("������� ������ ���.");
                        break;
                    }

                    for (int i = 0; i < length; i++)
                    {
                        info = connections[i]->data;
                        printf("%s\n", info.name);
                    }
                    free(connections);
                }

                else if (userChoice == 0)
                {
                    fileInfo info;
                    ListFile** connections = NULL;
                    ListUser* currentUser = NULL;

                    puts("������� ����� ������������:\n");
                    userOutput(headUser);
                    inputNat(&userChoice);

                    if (userChoice < 1 || userChoice > lenUser(headUser))
                    {
                        printf("������� �������� �� 1 �� %d!\n", lenUser(headUser));
                        break;
                    }

                    // ��������� ���������� � ������������ ���������� ������
                    currentUser = extractUser(headUser, userChoice);
                    connections = currentUser->connection;
                    length = currentUser->connectionLen;

                    if (length == 0)
                    {
                        puts("������� ������ ���.");
                        break;
                    }

                    for (int i = 0; i < length; i++)
                    {
                        info = connections[i]->data;
                        printf("%s\n", info.name);
                    }
                    free(connections);
                }
                else
                    puts("������� 1 ��� 0!");
                break;
            }

            // ��������� ���������� �� ����� � ������
            case (loadData):
            {
                fileInfo info1;
                info1.name = NULL;
                userInfo info2;
                info2.name = NULL;
                int length = 0;
                int count = 0;
                int position;
                int nextSymbol;
                ListUser* connectedUser;
                ListFile* connectedFile;

                dbFile = fopen("databaseFile.txt", "r");

                if (dbFile == NULL)
                {
                    printf("���� ������ �����������. ��� ����� ������� �������������.\n");
                    dbFile = fopen("databaseFile.txt", "w");
                    fclose(dbFile);
                    break;
                }

                listFileFree(&headFile, &tailFile); // ������� ������� ��� �������� �����

                while (!feof(dbFile))
                {
                    getString(&info1.name, dbFile);
                    if (info1.name == NULL)
                        break;

                    fread(&info1.date, sizeof(int), 1, dbFile);
                    fread(&info1.size, sizeof(int), 1, dbFile);

                    addFile(&headFile, &tailFile, info1);  // ���������� ������ ������
                }

                fclose(dbFile);

                dbUser = fopen("databaseUser.txt", "r");

                if (dbUser == NULL)
                {
                    printf("���� ������ �����������. ��� ����� ������� �������������.\n");
                    dbUser = fopen("databaseUser.txt", "w");
                    fclose(dbUser);
                    break;
                }

                listUserFree(&headUser, &tailUser); // ������� ������� ��� �������� �����

                while (!feof(dbUser))
                {
                    getString(&info2.name, dbUser);
                    if (info2.name == NULL)
                        break;

                    getString(&info2.login, dbUser);
                    getString(&info2.password, dbUser);

                    addUser(&headUser, &tailUser, info2);  // ���������� ������ ������
                }

                fclose(dbUser);


                // ������ ������
                connFile = fopen("connections.txt", "r");
                while(!feof(connFile))
                {
                    nextSymbol = getc(connFile);
                    fseek(connFile, -1, SEEK_CUR);
                    if (nextSymbol == '.')
                        break;

                    count++;
                    connectedFile = extractFile(headFile, count);
                    fread(&length, sizeof(int), 1, connFile);

                    if (length == 0)
                        break;

                    if (length == -1)
                    {
                        connectedFile->connection = NULL;
                        connectedFile->connectionLen = 0;
                    }

                    for (int j = 0; j < length; j++)
                    {
                        fread(&position, sizeof(int), 1, connFile);
                        connectedUser = extractUser(headUser, position);
                        addConnectionFile(&connectedFile, &connectedUser);
                    }
                }

                fclose(connFile);
                break;
            }

            // ��������� ���������� �� ������ � ����
            case (saveData):
            {
                fileInfo info1;
                userInfo info2;
                int number = 0;
                int length = 0;

                if (headFile == NULL && headUser == NULL)
                {
                    puts("������� ��������� ������!");
                    break;
                }

                dbFile = fopen("databaseFile.txt", "w");
                connFile = fopen("connections.txt", "w");
                for (ListFile* i = headFile; i != NULL; i = i->next)
                {
                    info1 = i->data;
                    putFileNode(info1, dbFile);

                    // �������� ������
                    length = i->connectionLen;
                    if (length == 0)
                        length = -1;
                    fwrite(&length, sizeof(int), 1, connFile);

                    for (int j = 0; j < i->connectionLen; j++)
                    {
                        number = knowNumberUser(headUser, i->connection[j]);
                        fwrite(&number, sizeof(int), 1, connFile);
                    }
                }
                putc('.', connFile);

                fclose(dbFile);
                fclose(connFile);

                dbUser = fopen("databaseUser.txt", "w");
                for (ListUser* i = headUser; i != NULL; i = i->next)
                {
                    info2 = i->data;
                    putUserNode(info2, dbUser);
                }

                fclose(dbUser);

                printf("������ ���� ��������� � ����.\n");
                break;
            }

            // �������� ����� ������� �� ������
            case (delete):
            {
                puts("�� ������ �������� � ������� (1) ��� �������������� (0)?");
                inputNat(&userChoice);

                if (userChoice == 1)
                {
                    puts("������� ����� �����:\n");
                    fileOutput(headFile);
                    inputNat(&userChoice);

                    if (userChoice < 1 || userChoice > lenFile(headFile))
                    {
                        printf("������� �������� �� 1 �� %d!\n", lenFile(headFile));
                        break;
                    }

                    deleteFile(&headFile, &tailFile, userChoice);
                }
                else if (userChoice == 0)
                {
                    puts("������� ����� ������������:\n");
                    userOutput(headUser);
                    inputNat(&userChoice);

                    if (userChoice < 1 || userChoice > lenUser(headUser))
                    {
                        printf("������� �������� �� 1 �� %d!\n", lenUser(headUser));
                        break;
                    }

                    deleteUser(&headUser, &tailUser, userChoice);
                } else
                    puts("������� 1 ��� 0!");
                break;
            }

            // ���������� ������ �� ������ �� �����
            case (sort):
            {
                int order = 0;
                char* field = NULL;

                puts("�� ������ ����������� ������ ������ (1) ��� ������������� (0)?");
                inputNat(&userChoice);

                if (userChoice != 1 && userChoice != 0)
                {
                    printf("������� 1 ��� 0!");
                    break;
                }

                if (userChoice == 1)
                {
                    printf("�� ������ ���� �� ������ ���������� ����������?\n"
                           "��������� ����: name, size, date:\n");
                    inputString(&field);
                    printf("�� ������ ���������� ���������� �� ����������� ��� ��������?(1/0)\n");
                    inputNat(&order);

                    if (order != 1 && order != 0)
                    {
                        printf("������� 1 ��� 0!");
                        break;
                    }

                    sortFile(&headFile, field, order);
                }
                else if (userChoice == 0)
                {
                    printf("�� ������ ���� �� ������ ���������� ����������?\n"
                           "��������� ����: login, password, name:\n");
                    inputString(&field);
                    printf("�� ������ ���������� ���������� �� ����������� ��� ��������?(1/0)\n");
                    inputNat(&order);

                    if (order != 1 && order != 0)
                    {
                        printf("������� 1 ��� 0!");
                        break;
                    }

                    sortUser(&headUser, field, order);
                }
                break;
            }

            // �����
            case (exitProg):
            {
                listFileFree(&headFile, &tailFile);
                exit(1);
                break;
            }
        }
    }while (1);
}
