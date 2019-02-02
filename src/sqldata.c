#include ".\..\include\sqldata.h"
#include ".\..\include\sql.h"
#include ".\..\include\file.h"
#include ".\..\include\list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int generateDataInteger(int min, int max)
{
    return rand() % ((max + 1) - min) + min;
}

int generateGender()
{
    return generateDataInteger(0, 1);
}

void generateGUID(char *guid)
{
    int i, j;
    char pc[] = "0123456789abcdef";
    char buffer[30];
    for (i = 0; i < 8; i++)
    {
        buffer[i] = pc[generateDataInteger(0, 15)];
    }
    buffer[8] = '\0';
    strcpy(guid, buffer);
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 4; j++)
        {
            buffer[j] = pc[generateDataInteger(0, 15)];
        }
        buffer[4] = '\0';
        strcat(guid, "-");
        strcat(guid, buffer);
    }
    for (i = 0; i < 12; i++)
    {
        buffer[i] = pc[generateDataInteger(0, 15)];
    }
    strcat(guid, "-");
    buffer[12] = '\0';
    strcat(guid, buffer);
}

float generateDataDouble()
{
    int max = 90;
    int min = 10;
    int bigratio;
    float proba;
    bigratio = generateDataInteger(min, max);
    proba = bigratio / 10.0;
    return proba;
}

void generateDataDate(char *date)
{
    int day = generateDataInteger(1, 25);
    int month = generateDataInteger(1, 12);
    int year = generateDataInteger(2000, 2018);
    if (day < 10)
    {
        if (month < 10)
        {
            sprintf(date, "0%d/0%d/%d", day, month, year);
        }
        else
        {
            sprintf(date, "0%d/%d/%d", day, month, year);
        }
    }
    else
    {
        if (month < 10)
        {
            sprintf(date, "%d/0%d/%d", day, month, year);
        }
        else
        {
            sprintf(date, "%d/%d/%d", day, month, year);
        }
    }
}

void generateDataText(char *text, int size)
{
    int i;
    char pc[] = "abcdefghijklmnopqrstuvwxyz";
    for (i = 0; i < size; i++)
    {
        text[i] = pc[generateDataInteger(0, 25)];
    }
    text[size] = '\0';
}

void generateCity(char *city)
{
    List *cities = listInit();
    FILE *fp = openFile(getenv(LOCALSTORAGE), CITY_FILE, "r");
    if (fp != NULL)
    {
        getFileContent(cities, SQL_DATA_MAX_VALUE_LENGTH, SQL_DATA_MIN_VALUE_LENGTH, fp, 1);
    }
    if (cities->length > 0)
        strcpy(city, getElement(cities, generateDataInteger(0, cities->length))->content);
    destroyList(cities);
}

void generateName(char *name)
{
    List *names = listInit();
    FILE *fp = openFile(getenv(LOCALSTORAGE), NAME_FILE, "r");
    if (fp != NULL)
    {
        getFileContent(names, SQL_DATA_MAX_VALUE_LENGTH, SQL_DATA_MIN_VALUE_LENGTH, fp, 1);
    }
    if (names->length > 0)
        strcpy(name, getElement(names, generateDataInteger(0, names->length))->content);
    destroyList(names);
}

void generatePhoneNumber(char *phoneNumber)
{
    int i;
    char pc[] = "0123456789";
    strcpy(phoneNumber, "0");
    for (i = 1; i < 10; i++)
    {
        phoneNumber[i] = pc[generateDataInteger(0, 9)];
    }
    phoneNumber[10] = '\0';
}

void generateMail(char *mail)
{
    char name[SQL_DATA_MAX_VALUE_LENGTH];
    List *mails = listInit();
    FILE *fp = openFile(getenv(LOCALSTORAGE), MAIL_FILE, "r");
    if (fp != NULL)
    {
        getFileContent(mails, SQL_DATA_MAX_VALUE_LENGTH, SQL_DATA_MIN_VALUE_LENGTH, fp, 1);
    }
    generateName(name);
    strcpy(mail, name);
    strcat(mail, "@");
    if (mails->length > 0)
        strcat(mail, getElement(mails, generateDataInteger(0, mails->length))->content);
    strcat(mail, ".io");
    destroyList(mails);
}

void setQuery(SqlInsertQuery *query)
{
    query->colNumber = 0;
}

void WriteInsDataToFile(FILE *fp, SqlInsertQuery *query, SqlRules *rules)
{
    int i, j;
    char queryString[SQL_DATA_MAX_QUERY_LENGTH];
    char columns[SQL_DATA_MAX_COLS_NAME];
    char values[SQL_DATA_MAX_COLS_VALUE];
    for (i = 0; i < rules->insNum; i++)
    {
        strcpy(queryString, SQL_DATA_INSERT);
        strcat(queryString, SQL_DATA_SPACE);
        strcat(queryString, query->tabName);
        strcpy(columns, "(");
        strcpy(values, "(");
        for (j = 0; j < query->colNumber; j++)
        {
            processColumn(&query->cols[j]);
            addColumnName(columns, query->cols[j].colName, j, query->colNumber);
            addColumnValue(values, query->cols[j].value, j, query->colNumber);
        }
        strcat(columns, ")");
        strcat(values, ")");
        strcat(queryString, columns);
        strcat(queryString, SQL_DATA_SPACE);
        strcat(queryString, SQL_DATA_VALUES);
        strcat(queryString, SQL_DATA_SPACE);
        strcat(queryString, values);
        strcat(queryString, SQL_DATA_QUERY_DELIMITER_2);
        fprintf(fp, "%s\n", queryString);
    }
}

void addColumnName(char *columnsName, char *columnName, int index, int colNumber)
{
    if (index < colNumber - 1)
    {
        strcat(columnsName, columnName);
        strcat(columnsName, SQL_DATA_QUERY_DELIMITER_1);
    }
    else
    {
        strcat(columnsName, columnName);
    }
}

void addColumnValue(char *columnsValue, char *columnValue, int index, int colNumber)
{
    if (index < colNumber - 1)
    {
        strcat(columnsValue, columnValue);
        strcat(columnsValue, SQL_DATA_QUERY_DELIMITER_1);
    }
    else
    {
        strcat(columnsValue, columnValue);
    }
}

void processColumn(SqlData *column)
{
    if (strcmp(column->typeName, SQL_DATA_TYPE_1) == 0)
    {
        sprintf(column->value, "%d", generateDataInteger(0, 100));
    }
    else if (strcmp(column->typeName, SQL_DATA_TYPE_2) == 0)
    {
        char buffer[SQL_DATA_MAX_VALUE_LENGTH];
        if (column->colLength == -1)
            column->colLength = SQL_DEF_STRING_LENGTH;
        generateDataText(buffer, column->colLength);
        sprintf(column->value, "'%s'", buffer);
    }
    else if (strcmp(column->typeName, SQL_DATA_TYPE_3) == 0)
    {
        sprintf(column->value, "%f", generateDataDouble());
    }
    else if (strcmp(column->typeName, SQL_DATA_TYPE_4) == 0)
    {
        char buffer[SQL_DATA_MAX_VALUE_LENGTH];
        generateDataDate(buffer);
        sprintf(column->value, "%s('%s', %s)", SQL_DATA_DATE, buffer, SQL_DATA_FORMAT);
    }
    else if (strcmp(column->typeName, SQL_DATA_TYPE_5) == 0)
    {
        char buffer[SQL_DATA_MAX_VALUE_LENGTH];
        generateCity(buffer);
        sprintf(column->value, "'%s'", buffer);
    }
    else if (strcmp(column->typeName, SQL_DATA_TYPE_6) == 0)
    {
        char buffer[SQL_DATA_MAX_VALUE_LENGTH];
        generateName(buffer);
        sprintf(column->value, "'%s'", buffer);
    }
    else if (strcmp(column->typeName, SQL_DATA_TYPE_7) == 0)
    {
        sprintf(column->value, "%d", generateGender());
    }
    else if (strcmp(column->typeName, SQL_DATA_TYPE_8) == 0)
    {
        char buffer[SQL_DATA_MAX_VALUE_LENGTH];
        generatePhoneNumber(buffer);
        sprintf(column->value, "'%s'", buffer);
    }
    else if (strcmp(column->typeName, SQL_DATA_TYPE_9) == 0)
    {
        char buffer[SQL_DATA_MAX_VALUE_LENGTH];
        generateMail(buffer);
        sprintf(column->value, "'%s'", buffer);
    }
    else if (strcmp(column->typeName, SQL_DATA_TYPE_10) == 0)
    {
        char buffer[SQL_DATA_MAX_VALUE_LENGTH];
        generateGUID(buffer);
        sprintf(column->value, "'%s'", buffer);
    }
}