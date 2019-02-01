#include ".\..\include\insdata.h"
#include ".\..\include\utils.h"
#include ".\..\include\sql.h"
#include ".\..\include\sqldata.h"
#include ".\..\include\styles.h"
#include ".\..\include\file.h"
#include <windows.h>

void createInsDataMenu(HWND hwnd, InsDataControls *controls, SqlRules *rules, SqlInsertQuery *query)
{
    controls->staticControls[0] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", INS_TAB_NAME_MSG, STL_EDIT, 250, 98, 150, 24, hwnd, (HMENU)INS_TAB_NAME_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    controls->staticControls[1] = CreateWindow("STATIC", INS_TITLEHINT_MSG, STL_TEXT, 100, 100, 150, 24, hwnd, (HMENU)INS_TITLEHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    controls->staticControls[2] = CreateWindow("BUTTON", INS_ADDCOLUMN_MSG, STL_BUTTON, 250, 300, 150, 24, hwnd, (HMENU)INS_ADDCOLUMN_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    controls->staticControls[3] = CreateWindow("BUTTON", INS_REMOVECOL_MSG, STL_BUTTON, 250, 350, 150, 24, hwnd, (HMENU)INS_REMOVECOL_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    controls->staticControls[4] = CreateWindow("BUTTON", INS_EXPORTMODEL_MSG, STL_BUTTON, 250, 600, 150, 24, hwnd, (HMENU)INS_EXPORTMODEL_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    controls->staticControls[5] = CreateWindow("STATIC", INS_TITLECOLUMN_MSG, STL_TEXT, 700, 60, 150, 24, hwnd, (HMENU)INS_TITLECOLUMN_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    controls->staticControls[6] = CreateWindow("STATIC", INS_TITLETYPE_MSG, STL_TEXT, 900, 60, 150, 24, hwnd, (HMENU)INS_TITLETYPE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    controls->staticControls[7] = CreateWindow("STATIC", INS_TITLELENGTH_MSG, STL_TEXT, 1075, 60, 150, 24, hwnd, (HMENU)INS_TITLELENGTH_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    controls->staticControls[8] = CreateWindow("STATIC", INS_TABEDHINT_MSG, STL_TEXT, 830, 10, 100, 24, hwnd, (HMENU)INS_TABEDHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    controls->colNum = 0;
    getSubtypes(rules);
    addInsertColumn(hwnd, controls, rules);
    setQuery(query);
}

void destroyInsDataMenu(InsDataControls *controls)
{
    destroyMenu(controls->staticControls, INSDATA_WIN_CTRL_NUM);
    destroyMenu(controls->colControls, INS_MAX_ADD_CTRL_NUM);
}

void addInsertColumn(HWND hwnd, InsDataControls *controls, SqlRules *rules)
{
    if (SQL_DATA_MAX_COL_NUM > controls->colNum)
    {
        int index = INS_COL_CTRL_NUM * controls->colNum;
        int space = INS_COL_SPACE * controls->colNum;
        controls->colControls[index] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", INS_COLUMN_NAME_MSG, STL_EDIT, 650, 98 + space, 150, 24, hwnd, (HMENU)INS_COLUMN_NAME_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        controls->colControls[index + 1] = CreateWindow("COMBOBOX", INS_COLUMNEDIT_MSG, STL_COMBO, 850, 98 + space, 150, 100, hwnd, (HMENU)INS_COLUMNEDIT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        controls->colControls[index + 2] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", INS_LENGTH_MSG, STL_EDIT, 1050, 98 + space, 100, 24, hwnd, (HMENU)INS_LENGTH_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        addSubTypes(rules->subTypes, controls->colControls[index + 1]);
        controls->colNum++;
    }
}

void removeInsertColumn(InsDataControls *controls)
{
    if (controls->colNum > 1)
    {
        int index = INS_COL_CTRL_NUM * (controls->colNum - 1);
        DestroyWindow(controls->colControls[index]);
        DestroyWindow(controls->colControls[index + 1]);
        DestroyWindow(controls->colControls[index + 2]);
        controls->colNum--;
    }
}

void getSubtypes(SqlRules *rules)
{
    rules->subTypes = listInit();
    push(rules->subTypes, SQL_DATA_TYPE_1);
    push(rules->subTypes, SQL_DATA_TYPE_2);
    push(rules->subTypes, SQL_DATA_TYPE_3);
    push(rules->subTypes, SQL_DATA_TYPE_4);
    push(rules->subTypes, SQL_DATA_TYPE_5);
    push(rules->subTypes, SQL_DATA_TYPE_6);
    push(rules->subTypes, SQL_DATA_TYPE_7);
    push(rules->subTypes, SQL_DATA_TYPE_8);
    push(rules->subTypes, SQL_DATA_TYPE_9);
    push(rules->subTypes, SQL_DATA_TYPE_10);
}

void addSubTypes(List *list, HWND hwnd)
{
    Element *current = list->first;
    while (current != NULL)
    {
        addStringToComboDir(hwnd, current->content);
        current = current->next;
    }
    setComboCursorDir(hwnd, 0);
}

void exportInsData(HWND hwnd, SqlInsertQuery *query, InsDataControls *controls)
{
    OPENFILENAME ofn;
    char file[MAX_PATH_LENGTH];
    SqlInsertQuery temp = saveInsData(hwnd, controls);
    if (checkInsData(&temp))
    {
        copyInsQuery(query, &temp);
        setOfn(hwnd, &ofn, file);
        if (GetSaveFileName(&ofn))
        {
            FILE *fp = fopen(file, "w");
            if (fp != NULL)
            {
                WriteInsDataToFile(fp, query);
            }
            fclose(fp);
        }
    }
}

SqlInsertQuery saveInsData(HWND hwnd, InsDataControls *controls)
{
    int i;
    int ctrlPerCol = INS_COL_CTRL_NUM;
    char digit[MAX_DIGIT_LENGTH];
    SqlInsertQuery query;
    getQueryTableName(hwnd, query.tabName);
    query.colNumber = controls->colNum;
    for (i = 0; i < query.colNumber; i++)
    {
        getStringFromWinDir(controls->colControls[i * ctrlPerCol + INS_COL_NAME_INDEX], query.cols[i].colName, SQL_COLUMN_NAME_MAX_LENGTH);
        getStringFromWinDir(controls->colControls[i * ctrlPerCol + INS_LENGTH_INDEX], digit, MAX_DIGIT_LENGTH);
        query.cols[i].colLength = strlen(digit) > 0 ? atoi(digit) : -1;
        getCurrentStringFromComboDir(controls->colControls[i * ctrlPerCol + INS_TYPE_INDEX], query.cols[i].typeName);
    }
    return query;
}

int checkInsData(SqlInsertQuery *query)
{
    int i;
    List *cols = listInit();
    for (i = 0; i < query->colNumber; i++)
    {
        push(cols, query->cols[i].colName);
    }
    if (!isStringSafe(query->tabName))
    {
        printError(INS_ERR_TAB_NAME_UNSAFE);
        return 0;
    }
    if (strlen(query->tabName) > SQL_TABLE_NAME_MAX_LENGTH || strlen(query->tabName) < SQL_TABLE_NAME_MIN_LENGTH)
    {
        printError(INS_ERR_TAB_NAME_LENGTH);
        return 0;
    }
    for (i = 0; i < query->colNumber; i++)
    {
        if (!isStringSafe(query->cols[i].colName))
        {
            printError(INS_ERR_COL_NAME_UNSAFE);
            return 0;
        }
        if (strlen(query->cols[i].colName) > SQL_COLUMN_NAME_MAX_LENGTH || strlen(query->cols[i].colName) < SQL_COLUMN_NAME_MIN_LENGTH)
        {
            printError(INS_ERR_COL_NAME_LENGTH);
            return 0;
        }
        if (hasClone(cols))
        {
            printError(INS_ERR_COL_NAME_EXISTS);
            return 0;
        }
        if ((query->cols[i].colLength > MAX_VAR_LENGTH || query->cols[i].colLength < MIN_VAR_LENGTH) && query->cols[i].colLength != -1)
        {
            printError(INS_ERR_COL_LENGTH);
            return 0;
        }
    }
    destroyList(cols);
    return 1;
}

void getQueryTableName(HWND hwnd, char *buffer)
{
    getStringFromWin(hwnd, INS_TAB_NAME_ID, buffer, SQL_TABLE_NAME_MAX_LENGTH);
}

void copyInsQuery(SqlInsertQuery *destination, SqlInsertQuery *source)
{
    strcpy(destination->tabName, source->tabName);
    destination->colNumber = source->colNumber;
    for (int i = 0; i < source->colNumber; i++)
    {
        strcpy(destination->cols[i].colName, source->cols[i].colName);
        strcpy(destination->cols[i].typeName, source->cols[i].typeName);
        destination->cols[i].colLength = source->cols[i].colLength;
    }
}