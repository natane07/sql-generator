#include ".\..\include\insdata.h"
#include ".\..\include\utils.h"
#include ".\..\include\sql.h"
#include ".\..\include\sqldata.h"
#include ".\..\include\styles.h"
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
    if (rules->maxCol > controls->colNum)
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