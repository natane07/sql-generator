#ifndef CRTABLE_H

#define CRTABLE_H

#include <windows.h>
#include "sql.h"

//view
#define DEF_TAB_NAME "Table"
#define CRTABLE_WIN_MAIN_CTRL_NUM 13
#define CRTABLE_WIN_COL_CTRL_NUM 120
#define CRTABLE_WIN_FK_CTRL_NUM 18
#define COLUMN_SPACE_PX 30
#define CTRL_PER_COL 2
#define CTRL_PER_FK 3
#define CTRL_PER_FULL_COL 6
#define COL_TITLE_INDEX 0
#define COL_TYPE_COMBO_INDEX 1
#define COL_TYPE_EDIT_INDEX 2
#define COL_AI_INDEX 3
#define COL_NULL_INDEX 4
#define COL_PK_INDEX 5
#define FK_COL_INDEX 0
#define FK_PTAB_INDEX 1
#define FK_PCOL_INDEX 2

//controls
#define LITABHINT_ID 10
#define LITABHINT_MSG "Table List"
#define TABEDHINT_ID 11
#define TABEDHINT_MSG "Table Editor"
#define TITLEHINT_ID 12
#define TITLEHINT_MSG "Enter Table Name:"
#define TITLEDIT_ID 13
#define TITLEDIT_MSG DEF_TAB_NAME
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
#define FK_CMB_ID 1102

//column type for addColumn and removeColumn function
#define FK_ADD 0
#define COL_ADD 1
#define SET_MENU 2
#define FK_DEL 0
#define COL_DEL 1

//errors
#define CRTAB_ERR_TAB_NAME_UNSAFE "Table name should only use alphanumeric characters!"
#define CRTAB_ERR_TAB_NAME_LENGTH "Table name too short or too long!"
#define CRTAB_ERR_TAB_NAME_EXISTS "Table name already exists in model!"
#define CRTAB_ERR_COL_NAME_UNSAFE "Column name should only use alphanumeric characters!"
#define CRTAB_ERR_COL_NAME_LENGTH "Column name too short or too long!"
#define CRTAB_ERR_COL_NAME_EXISTS "Column name already exists in table!"
#define CRTAB_ERR_COL_LENGTH "Type requiring length must have valid integer!"
#define CRTAB_ERR_FK_EMPTY_FIELD "Foreign Key must be composed of valid elements!"
#define CRTAB_ERR_PK_NONE "Table must contain at least one Primary Key!"
#define CRTAB_ERR_AI_TYPE_INVALID "Auto_Increment must be enabled on proper type!"

typedef struct CrTableControls CrTableControls;
struct CrTableControls
{
    HWND mainControls[CRTABLE_WIN_MAIN_CTRL_NUM];
    HWND fk[CRTABLE_WIN_FK_CTRL_NUM];
    HWND columns[CRTABLE_WIN_COL_CTRL_NUM];
    int fkNumber;
    int colNumber;
    int currentTableNumber;
};

void createCrTableMenu(HWND, CrTableControls *, SqlRules *, SqlModel *);
void addColumn(HWND, CrTableControls *, int, SqlRules *, SqlModel *);
void removeColumn(HWND, CrTableControls *, int, SqlRules *);
void getTableName(HWND, char *);
void updateTableList(HWND, SqlModel *);
void fillColumnCombo(HWND, SqlModel *, int);
void fillTableCombo(HWND, SqlModel *);
void fillPColumnCombo(CrTableControls *controls, SqlModel *model);
void clearTableList(HWND);
int checkTable(SqlModel *, SqlTable *, int, SqlRules *);
SqlTable saveTable(HWND, CrTableControls *, SqlRules *, SqlModel *);
SqlTable getDefaultTable(int);
void updateModel(SqlModel *, SqlTable *, int);
void loadFallbackTable(SqlModel *, HWND, CrTableControls *, SqlRules *);
void loadTable(SqlTable *, HWND, CrTableControls *, SqlRules *, SqlModel *);
void addTypes(HWND, SqlRules *);
void checkTypeReqNum(CrTableControls *, SqlRules *);
void checkPkNonVacuity(CrTableControls *);
void setTableName(HWND, char *);
int getTableListCursor(HWND);
void addTableToList(HWND, char *);
void destroyCrTableMenu(CrTableControls *);
void exportModel(HWND, SqlModel *, char *);

#endif