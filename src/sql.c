#include ".\..\include\sql.h"
#include ".\..\include\utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getTestModel(SqlModel *model)
{
    SqlTable tabs[2];
    SqlColumn cols[4];
    SqlForeignKey fk = setFk("id_pet", "Pet", "id");
    setTable(tabs, "Person");
    setTable(tabs + 1, "Pet");
    setDefaultPrimaryKey(cols);
    cols[1] = setColumn("VARCHAR", "nom", 20, 1, 0, 1);
    cols[2] = setColumn("VARCHAR", "prenom", 20, 1, 0, 0);
    cols[3] = setColumn("INT", "id_pet", -1, 1, 0, 0);
    addColumns(tabs, cols, 4);
    cols[1] = setColumn("VARCHAR", "nom", 30, 1, 0, 0);
    addColumns(tabs + 1, cols, 2);
    addRelations(tabs, &fk, 1);
    addTables(model, tabs, 2);
}

void setDefaultPrimaryKey(SqlColumn *col)
{
    col->pk = 1;
    col->ai = 1;
    col->nullable = 0;
    col->size = -1;
    stringCopy(col->type, "INT", SQL_TYPE_LENGTH);
    stringCopy(col->name, "id", SQL_COLUMN_NAME_MAX_LENGTH);
}

void setColumnName(SqlColumn *col, char *name)
{
    stringCopy(col->name, name, SQL_COLUMN_NAME_MAX_LENGTH);
}

SqlColumn setColumn(char *type, char *name, int size, int nullable, int ai, int pk)
{
    SqlColumn col;
    stringCopy(col.type, type, SQL_TYPE_LENGTH);
    stringCopy(col.name, name, SQL_COLUMN_NAME_MAX_LENGTH);
    col.size = size;
    col.nullable = nullable;
    col.ai = ai;
    col.pk = pk;
    return col;
}

SqlForeignKey setFk(char *columnName, char *pointedTableName, char *pointedColumnName)
{
    SqlForeignKey fk;
    stringCopy(fk.columnName, columnName, SQL_COLUMN_NAME_MAX_LENGTH);
    stringCopy(fk.pointedTableName, pointedTableName, SQL_TABLE_NAME_MAX_LENGTH);
    stringCopy(fk.pointedColumnName, pointedColumnName, SQL_COLUMN_NAME_MAX_LENGTH);
    return fk;
}

void setTable(SqlTable *tab, char *name)
{
    stringCopy(tab->name, name, SQL_TABLE_NAME_MAX_LENGTH);
    tab->columnCount = 0;
    tab->relationCount = 0;
    tab->relations = NULL;
    tab->columns = NULL;
}

void destroyTable(SqlTable *tab)
{
    if (tab->relations != NULL)
    {
        free(tab->relations);
    }
    if (tab->columns != NULL)
    {
        free(tab->columns);
    }
}

void setModel(SqlModel *model)
{
    model->tableCount = 0;
    model->tables = NULL;
}

void addColumns(SqlTable *tab, SqlColumn *cols, int colNumber)
{
    int i;
    tab->columns = malloc(colNumber * sizeof(SqlColumn));
    for (i = 0; i < colNumber; i++)
    {
        tab->columns[i] = cols[i];
    }
    tab->columnCount = colNumber;
}

void addTables(SqlModel *model, SqlTable *tabs, int tabNumber)
{
    int i;
    model->tables = malloc(tabNumber * sizeof(SqlTable));
    for (i = 0; i < tabNumber; i++)
    {
        model->tables[i] = tabs[i];
    }
    model->tableCount = tabNumber;
}

void addRelations(SqlTable *tab, SqlForeignKey *relations, int relNumber)
{
    int i;
    tab->relations = malloc(relNumber * sizeof(SqlForeignKey));
    for (i = 0; i < relNumber; i++)
    {
        tab->relations[i] = relations[i];
    }
    tab->relationCount = relNumber;
}

void printTable(SqlTable *tab)
{
    int i;
    puts(tab->name);
    for (i = 0; i < tab->columnCount; i++)
    {
        SqlColumn col = tab->columns[i];
        printf("col name %s type %s size %d ai %d null %d pk %d\n", col.name, col.type, col.size, col.ai, col.nullable, col.pk);
    }
    printf("col - number%d\n", tab->columnCount);
    for (i = 0; i < tab->relationCount; i++)
    {
        SqlForeignKey fk = tab->relations[i];
        printf("fk col %s references %s(%s)\n", fk.columnName, fk.pointedTableName, fk.pointedColumnName);
    }
    printf("fk - number %d\n", tab->relationCount);
}

void printModel(SqlModel *model)
{
    int i;
    for (i = 0; i < model->tableCount; i++)
    {
        SqlTable tab = model->tables[i];
        printf("table %d\n", i);
        printTable(&tab);
    }
}

void generateScript(SqlModel *model, FILE *fp)
{
    writeCrTablesToFile(model, fp);
}

void destroyModel(SqlModel *model)
{
    int i;
    for (i = 0; i < model->tableCount; i++)
    {
        free(model->tables[i].columns);
        free(model->tables[i].relations);
    }
    free(model->tables);
}

void writeCrTablesToFile(SqlModel *model, FILE *fp)
{
    int i, j;
    for (i = 0; i < model->tableCount; i++)
    {
        char query[SQL_QUERY_MAX_LENGTH];
        char buffer[SQL_COLUMN_MAX_LENGTH];
        query[0] = '\0';
        SqlTable tab = model->tables[i];
        for (j = 0; j < tab.columnCount; j++)
        {
            SqlColumn col = tab.columns[j];
            writeColumn(buffer, &col);
            strcat(query, buffer);
        }
        addPrimaryKey(buffer, &tab);
        strcat(query, buffer);
        for (j = 0; j < tab.relationCount; j++)
        {
            SqlForeignKey fk = tab.relations[j];
            addForeignKey(buffer, &fk);
            strcat(query, buffer);
        }
        fprintf(fp, "%s %s(%s);\n", SQL_CRTAB, tab.name, query);
    }
}

void writeColumn(char *buffer, SqlColumn *col)
{
    sprintf(buffer, "%s %s", col->name, col->type);
    if (col->size != -1)
    {
        char indicator[SQL_COLUMN_MAX_SIZE_DIGIT];
        sprintf(indicator, "(%d)", col->size);
        strcat(buffer, indicator);
    }
    if (col->ai)
    {
        strcat(buffer, SQL_SPACE);
        strcat(buffer, SQL_AI);
    }
    if (!col->nullable)
    {
        strcat(buffer, SQL_SPACE);
        strcat(buffer, SQL_NOT_NULL);
    }
    strcat(buffer, SQL_QUERY_DELIMITER);
}

void addPrimaryKey(char *buffer, SqlTable *tab)
{
    int i;
    int counter = 0;
    char pkList[SQL_COLUMN_MAX_LENGTH];
    for (i = 0; i < tab->columnCount; i++)
    {
        if (tab->columns[i].pk && !counter)
        {
            stringCopy(pkList, tab->columns[i].name, SQL_COLUMN_NAME_MAX_LENGTH);
            counter++;
        }
        else if (tab->columns[i].pk)
        {
            char inter[SQL_COLUMN_NAME_MAX_LENGTH];
            sprintf(inter, ",%s", tab->columns[i].name);
            strcat(pkList, inter);
            counter++;
        }
    }
    sprintf(buffer, "%s(%s)", SQL_PK, pkList);
}

void addForeignKey(char *buffer, SqlForeignKey *fk)
{
    sprintf(buffer, ",%s(%s) %s %s(%s)", SQL_FK, fk->columnName, SQL_REF, fk->pointedTableName, fk->pointedColumnName);
}