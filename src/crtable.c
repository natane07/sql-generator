#include ".\..\include\crtable.h"
#include ".\..\include\app.h"
#include ".\..\include\utils.h"
#include ".\..\include\sql.h"
#include <windows.h>

void createCrTableMenu(HWND hwnd, HWND *crTableMenuControls)
{
    char buffer[SQL_TABLE_NAME_MAX_LENGTH];
    crTableMenuControls[0] = CreateWindow("STATIC", LITABHINT_MSG, STL_TEXT, 30, 10, 100, 24, hwnd, (HMENU)LITABHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls[1] = CreateWindow("STATIC", TABEDHINT_MSG, STL_TEXT, 830, 10, 100, 24, hwnd, (HMENU)TABEDHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls[2] = CreateWindow("STATIC", TITLEHINT_MSG, STL_TEXT, 690, 40, 150, 24, hwnd, (HMENU)TITLEHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls[3] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", TITLEDIT_MSG, STL_EDIT, 830, 40, 150, 24, hwnd, (HMENU)TITLEDIT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls[4] = CreateWindowEx(WS_EX_CLIENTEDGE, "LISTBOX", TABLIST_MSG, STL_LIST, 30, 30, 400, 400, hwnd, (HMENU)TABLIST_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls[5] = CreateWindow("BUTTON", ADDCOLUMN_MSG, STL_BUTTON, 830, 160, 150, 24, hwnd, (HMENU)ADDCOLUMN_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls[6] = CreateWindow("BUTTON", ADDTABLE_MSG, STL_BUTTON, 830, 460, 150, 24, hwnd, (HMENU)ADDTABLE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls[7] = CreateWindow("BUTTON", ADDFK_MSG, STL_BUTTON, 830, 190, 150, 24, hwnd, (HMENU)ADDFK_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls[8] = CreateWindow("BUTTON", DELTABLE_MSG, STL_BUTTON, 670, 460, 150, 24, hwnd, (HMENU)DELTABLE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls[9] = CreateWindow("BUTTON", EXPORTMODEL_MSG, STL_BUTTON, 155, 460, 150, 24, hwnd, (HMENU)EXPORTMODEL_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    addColumn(hwnd, crTableMenuControls);
    getTableName(hwnd, buffer);
    addTableToList(hwnd, buffer);
}

void addColumn(HWND hwnd, HWND *crTableMenuControls)
{
    static int counter = 0;
    crTableMenuControls[COL_FIRST_ASSIGNABLE_INDEX + counter] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", COLUMNEDIT_MSG, STL_EDIT, 530, 75, 150, 24, hwnd, (HMENU)19, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls[COL_FIRST_ASSIGNABLE_INDEX + counter + 1] = CreateWindow("COMBOBOX", COLUMNEDIT_MSG, STL_COMBO, 690, 75, 150, 100, hwnd, (HMENU)20, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    counter += 2;
}

void getTableName(HWND hwnd, char *buffer)
{
    getStringFromWin(hwnd, TITLEDIT_ID, buffer, SQL_TABLE_NAME_MAX_LENGTH);
}

void addTableToList(HWND hwnd, char *tabName)
{
    addStringToList(hwnd, TABLIST_ID, tabName);
}

void destroyCrTableMenu(HWND *controls)
{
    destroyMenu(controls, CRTABLE_WIN_CTRL_NUM);
}