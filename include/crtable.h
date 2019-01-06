#ifndef CRTABLE_H

#define CRTABLE_H

#include <windows.h>

//view
#define CRTABLEWIN_CLASS "CrTableClass"
#define CRTABLE_NAME "Create Table"

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

void createCrTableMenu(HWND, HWND *);
void addColumn(HWND, HWND *);
void getTableName(HWND, char *);
void addTableToList(HWND, char *);

#endif