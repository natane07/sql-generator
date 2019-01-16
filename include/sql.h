#ifndef SQL_H

#define SQL_H

#include "list.h"

//default sql types
#define SQL_TYPE_1 "INT"
#define SQL_TYPE_2 "CHAR"
#define SQL_TYPE_3 "VARCHAR"
#define SQL_TYPE_4 "TEXT"
#define SQL_TYPE_5 "DATE"
#define SQL_TYPE_6 "DECIMAL"
#define SQL_TYPE_1_REQ_NUM NOT_REQ_NUM
#define SQL_TYPE_2_REQ_NUM REQ_NUM
#define SQL_TYPE_3_REQ_NUM REQ_NUM
#define SQL_TYPE_4_REQ_NUM NOT_REQ_NUM
#define SQL_TYPE_5_REQ_NUM NOT_REQ_NUM
#define SQL_TYPE_6_REQ_NUM NOT_REQ_NUM
#define REQ_NUM "1"
#define NOT_REQ_NUM "0"


#define SQL_CRTAB "CREATE TABLE"
#define SQL_PK "PRIMARY KEY"
#define SQL_FK "FOREIGN KEY"
#define SQL_REF "REFERENCES"
#define SQL_AI "AUTO_INCREMENT"
#define SQL_NOT_NULL "NOT NULL"
#define SQL_SPACE " "
#define SQL_QUERY_DELIMITER ","
#define SQL_QUERY_MAX_LENGTH 4096
#define SQL_COLUMN_MAX_LENGTH 128
#define SQL_COLUMN_NAME_MAX_LENGTH 30
#define SQL_COLUMN_MAX_SIZE_DIGIT 10
#define SQL_TABLE_NAME_MAX_LENGTH 30
#define ITOA_SIZE 33

struct SqlColumn
{
    char *type;
    char *name;
    int size;
    int nullable;
    int ai;
    int pk;
};
typedef struct SqlColumn SqlColumn;

struct SqlForeignKey
{
    char *columnName;
    char *pointedTableName;
    char *pointedColumnName;
};
typedef struct SqlForeignKey SqlForeignKey;

struct SqlTable
{
    char *name;
    int columnCount;
    SqlColumn *columns;
    int relationCount;
    SqlForeignKey *relations;
};
typedef struct SqlTable SqlTable;

struct SqlModel
{
    SqlTable *tables;
    int tableCount;
};
typedef struct SqlModel SqlModel;

typedef struct SqlRules SqlRules;
struct SqlRules
{
    int maxCol;
    int maxFk;
    List *types;
    List *numReqTypes;
};

void getTestModel(SqlModel *);
void setDefaultPrimaryKey(SqlColumn *);
void setColumnName(SqlColumn *, char *);
SqlColumn setColumn(char *, char *, int, int, int, int);
SqlForeignKey setFk(char *, char *, char *);
void setTable(SqlTable *, char *);
void setModel(SqlModel *);
void addColumns(SqlTable *, SqlColumn *, int);
void addTables(SqlModel *, SqlTable *, int);
void addRelations(SqlTable *, SqlForeignKey *, int);
void printTable(SqlTable *);
void printModel(SqlModel *);
void generateScript(SqlModel *);
void destroyModel(SqlModel *);
void writeCrTablesToFile(SqlModel *);
void writeColumn(char *, SqlColumn *);
void addPrimaryKey(char *, SqlTable *);
void addForeignKey(char *, SqlForeignKey *);

#endif