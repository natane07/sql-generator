#ifndef SQL_H

#define SQL_H

typedef SqlColumn SqlColumn;
struct SqlColumn
{
    char *type;
    char *name;
    int size;
    int nullable;
    int autoIncrement;
};

typedef struct SqlTable SqlTable;
struct SqlTable
{
    char *name;
    int columnCount;
    SqlColumn *columns;
};

typedef struct SqlModel SqlModel;
struct SqlModel
{
    SqlTable *tables;
    int tableCount;
};

#endif