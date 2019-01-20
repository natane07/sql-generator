#ifndef CRTABLE_H

#define CRTABLE_H

#include <windows.h>
#include "sql.h"

//view
#define CRTABLE_NAME "Create Table"
#define CRTABLE_WIN_MAIN_CTRL_NUM 13
#define CRTABLE_WIN_COL_CTRL_NUM 120
#define CRTABLE_WIN_FK_CTRL_NUM 18
#define COLUMN_SPACE_PX 30
#define CTRL_PER_COL 2
#define CTRL_PER_FK 3

//controls
#define LITABHINT_ID 10
#define LITABHINT_MSG "Table List"
#define TABEDHINT_ID 11
#define TABEDHINT_MSG "Table Editor"
#define TITLEHINT_ID 12
#define TITLEHINT_MSG "Enter Table Name:"
#define TITLEDIT_ID 13
#define TITLEDIT_MSG "New Table"
#define TABLIST_ID 14
#define TABLIST_MSG ""
#define ADDCOLUMN_ID 15
#define ADDCOLUMN_MSG "+ Column"
#define ADDTABLE_ID 16
#define ADDTABLE_MSG "Add Table"
#define ADDFK_ID 17
#define ADDFK_MSG "+ Foreign Key"
#define DELTABLE_ID 18
#define DELTABLE_MSG "Remove Table"
#define EXPORTMODEL_ID 19
#define EXPORTMODEL_MSG "Export Model"
#define SAVETABLE_ID 20
#define SAVETABLE_MSG "Save Table"
#define REMOVECOL_ID 21
#define REMOVECOL_MSG "- Column"
#define REMOVEFK_ID 22
#define REMOVEFK_MSG "- Foreign Key"

//radio texts
#define RD_NULL "null"
#define RD_AI "a_i"
#define RD_PK "pk"

//available range for additional controls
#define COLUMNEDIT_MSG ""
#define COL_FIRST_ASSIGNABLE_ID 100
#define FK_FIRST_ASSIGNABLE_ID 300
#define RADIO_BTN_ID 1100
#define COMBOS_ID 1101

//column type for addColumn and removeColumn function
#define FK_ADD 0
#define COL_ADD 1
#define SET_MENU 2
#define FK_DEL 0
#define COL_DEL 1

typedef struct CrTableControls CrTableControls;
struct CrTableControls
{
    HWND mainControls[CRTABLE_WIN_MAIN_CTRL_NUM];
    HWND fk[CRTABLE_WIN_FK_CTRL_NUM];
    HWND columns[CRTABLE_WIN_COL_CTRL_NUM];
    int fkNumber;
    int colNumber;
};

void createCrTableMenu(HWND, CrTableControls *, SqlRules *);
void addColumn(HWND, CrTableControls *, int, SqlRules *);
void removeColumn(HWND, CrTableControls *, int, SqlRules *);
void getTableName(HWND, char *);
void addTypes(HWND, SqlRules *);
void checkTypeReqNum(HWND, HWND, SqlRules *);
void addTableToList(HWND, char *);
void destroyCrTableMenu(CrTableControls *);

#endif