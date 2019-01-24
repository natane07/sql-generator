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

#define SQL_DATA_INSERT "INSERT INTO"
#define SQL_DATA_VALUES "VALUES"
#define SQL_DATA_DATE "TO_DATE"
#define SQL_DATA_FORMAT "'DD/MM/YYYY'"
#define SQL_DATA_SPACE " "
#define SQL_DATA_QUERY_DELIMITER_1 ","
#define SQL_DATA_QUERY_DELIMITER_2 ";"

#define SQL_DATA_MAX_COL_NAME 30
#define SQL_DATA_MAX_TYPE_NAME 30

struct SqlData {
    char colName[SQL_DATA_MAX_COL_NAME];
    char typeName[SQL_DATA_MAX_TYPE_NAME];
    int colLength;
};
typedef struct SqlData SqlData;

char *generateDataText(char *, int);
int generateDataInteger(int, int);
float generateDataDouble();
void generateDataDate(char *);