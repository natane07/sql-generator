#ifndef SQLDATA_H

#define SQLDATA_H

#include "list.h"

//default sql types
#define SQL_DATA_TYPE_1 "INTEGER"
#define SQL_DATA_TYPE_2 "STRING"
#define SQL_DATA_TYPE_3 "FLOAT"
#define SQL_DATA_TYPE_4 "DATE"
#define SQL_DATA_TYPE_5 "CITY"
#define SQL_DATA_TYPE_6 "NAME"
#define SQL_DATA_TYPE_7 "GENDER"
#define SQL_DATA_TYPE_8 "PHONE"
#define SQL_DATA_TYPE_9 "EMAIL"
#define SQL_DATA_TYPE_10 "GUID"

#define SQL_DATA_INSERT "INSERT INTO"
#define SQL_DATA_VALUES "VALUES"
#define SQL_DATA_DATE "TO_DATE"
#define SQL_DATA_FORMAT "'DD/MM/YYYY'"
#define SQL_DATA_SPACE " "
#define SQL_DATA_QUERY_DELIMITER_1 ","
#define SQL_DATA_QUERY_DELIMITER_2 ";"

#define SQL_DATA_MAX_COL_NAME 30
#define SQL_DATA_MAX_TAB_NAME 30
#define SQL_DATA_MAX_TYPE_NAME 30
#define SQL_DATA_MAX_COL_NUM 15
#define SQL_DATA_MAX_VALUE_LENGTH 259
#define SQL_DATA_MIN_VALUE_LENGTH 2
#define SQL_DATA_MAX_COLS_NAME (SQL_DATA_MAX_COL_NAME * SQL_DATA_MAX_COL_NUM)
#define SQL_DATA_MAX_COLS_VALUE (SQL_DATA_MAX_VALUE_LENGTH * SQL_DATA_MAX_COL_NUM)
#define SQL_DATA_MAX_QUERY_LENGTH 6144

struct SqlData
{
    char colName[SQL_DATA_MAX_COL_NAME];
    char typeName[SQL_DATA_MAX_TYPE_NAME];
    char value[SQL_DATA_MAX_VALUE_LENGTH];
    int colLength;
};
typedef struct SqlData SqlData;
struct SqlInsertQuery
{
    char tabName[SQL_DATA_MAX_TAB_NAME];
    SqlData cols[SQL_DATA_MAX_COL_NUM];
    int colNumber;
};
typedef struct SqlInsertQuery SqlInsertQuery;

int generateDataInteger(int, int);
int generateGender();
void generateGUID(char *);
float generateDataDouble();
void generateDataDate(char *);
void generateDataText(char *, int);
void generateCity(char *);
void generateName(char *);
void generatePhoneNumber(char *);
void generateMail(char *);
void setQuery(SqlInsertQuery *);
void WriteInsDataToFile(FILE *, SqlInsertQuery *);
void addColumnName(char *, char *, int, int);
void addColumnValue(char *, char *, int, int);
void processColumn(SqlData *);

#endif