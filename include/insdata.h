#ifndef INSDATA_H

#define INSDATA_H

#include <windows.h>
#include "sql.h"
#include "sqldata.h"

//controls
#define INSDATA_WIN_CTRL_NUM 9
#define INS_TAB_NAME_ID 400
#define INS_TAB_NAME_MSG ""
#define INS_TITLEHINT_ID 401
#define INS_TITLEHINT_MSG "Enter Table Name:"
#define INS_ADDCOLUMN_ID 402
#define INS_ADDCOLUMN_MSG "+ Column"
#define INS_REMOVECOL_ID 403
#define INS_REMOVECOL_MSG "- Column"
#define INS_EXPORTMODEL_ID 404
#define INS_EXPORTMODEL_MSG "Export Data"
#define INS_TITLECOLUMN_ID 405
#define INS_TITLECOLUMN_MSG "Column"
#define INS_TITLELENGTH_ID 406
#define INS_TITLELENGTH_MSG "Length"
#define INS_LENGTH_ID 407
#define INS_LENGTH_MSG ""
#define INS_TABEDHINT_ID 408
#define INS_TABEDHINT_MSG "Generate Data"

//available range for additional controls
#define INS_COLUMN_NAME_ID 1300
#define INS_COLUMN_NAME_MSG ""
#define INS_COLUMNEDIT_ID 1301
#define INS_COLUMNEDIT_MSG ""
#define INS_TITLETYPE_ID 1302
#define INS_TITLETYPE_MSG "Type"

#define INS_MAX_ADD_CTRL_NUM 99
#define INS_COL_CTRL_NUM 3
#define INS_COL_SPACE 30
#define INS_COL_NAME_INDEX 0
#define INS_TYPE_INDEX 1
#define INS_LENGTH_INDEX 2

//errors
#define INS_ERR_TAB_NAME_UNSAFE "Table name should only use alphanumeric characters!"
#define INS_ERR_TAB_NAME_LENGTH "Table name too short or too long!"
#define INS_ERR_COL_NAME_UNSAFE "Column name should only use alphanumeric characters!"
#define INS_ERR_COL_NAME_LENGTH "Column name too short or too long!"
#define INS_ERR_COL_NAME_EXISTS "Column name already exists in table!"
#define INS_ERR_COL_LENGTH "Length must have valid integer!"

struct InsDataControls
{
    HWND staticControls[INSDATA_WIN_CTRL_NUM];
    HWND colControls[INS_MAX_ADD_CTRL_NUM];
    int colNum;
};
typedef struct InsDataControls InsDataControls;

void createInsDataMenu(HWND, InsDataControls *, SqlRules *, SqlInsertQuery *);
void destroyInsDataMenu(InsDataControls *);
void addInsertColumn(HWND, InsDataControls *, SqlRules *);
void removeInsertColumn(InsDataControls *);
void getSubtypes(SqlRules *);
void addSubTypes(List *, HWND);
void exportInsData(HWND, SqlInsertQuery *, InsDataControls *, SqlRules *, char *);
SqlInsertQuery saveInsData(HWND, InsDataControls *);
int checkInsData(SqlInsertQuery *);
void getQueryTableName(HWND, char *);
void copyInsQuery(SqlInsertQuery *, SqlInsertQuery *);

#endif