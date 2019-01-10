#ifndef CRTABLE_H

#define CRTABLE_H

#include <windows.h>

//view
#define CRTABLEWIN_CLASS "CrTableClass"
#define CRTABLE_NAME "Create Table"
#define CRTABLE_WIN_CTRL_NUM 42

//controls
#define LITABHINT_ID 9
#define LITABHINT_MSG "Table List"
#define TABEDHINT_ID 10
#define TABEDHINT_MSG "Table Editor"
#define TITLEHINT_ID 11
#define TITLEHINT_MSG "Enter Table Name:"
#define TITLEDIT_ID 12
#define TITLEDIT_MSG "New Table"
#define TABLIST_ID 13
#define TABLIST_MSG ""
#define ADDCOLUMN_MSG "+ Column"
#define ADDCOLUMN_ID 14
#define ADDTABLE_MSG "Add Table"
#define ADDTABLE_ID 15
#define ADDFK_ID 16
#define ADDFK_MSG "+ Foreign Key"
#define DELTABLE_MSG "Remove Table"
#define DELTABLE_ID 17
#define COLUMNEDIT_MSG ""
#define EXPORTMODEL_ID 18
#define EXPORTMODEL_MSG "Export Model"

//available range for additional controls
#define MAX_ADDITIONAL_CTRL_NUM 30
#define COL_FIRST_ASSIGNABLE_ID 19
#define COL_FIRST_ASSIGNABLE_INDEX 10
#define COL_LAST_ASSIGNABLE_INDEX COL_FIRST_ASSIGNABLE_INDEX + MAX_ADDITIONAL_CTRL_NUM - 1
#define FK_FIRST_ASSIGNABLE_INDEX COL_LAST_ASSIGNABLE_INDEX + 1
#define FK_LAST_ASSIGNABLE_INDEX FK_FIRST_ASSIGNABLE_INDEX + 1

void createCrTableMenu(HWND, HWND *);
void addColumn(HWND, HWND *);
void getTableName(HWND, char *);
void addTableToList(HWND, char *);
void destroyCrTableMenu(HWND *);

#endif