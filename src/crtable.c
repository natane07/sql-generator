#include ".\..\include\crtable.h"
#include ".\..\include\app.h"
#include ".\..\include\utils.h"
#include <windows.h>

void createCrTableMenu(HWND hwnd, HWND *crTableMenuControls)
{
    crTableMenuControls[0] = CreateWindow("STATIC", LITABHINT_MSG, STL_TEXT, 30, 10, 100, 24, hwnd, (HMENU)LITABHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls[1] = CreateWindow("STATIC", TABEDHINT_MSG, STL_TEXT, 830, 10, 100, 24, hwnd, (HMENU)TABEDHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls[2] = CreateWindow("STATIC", TITLEHINT_MSG, STL_TEXT, 690, 40, 150, 24, hwnd, (HMENU)TITLEHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls[3] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", TITLEDIT_MSG, STL_EDIT, 830, 40, 150, 24, hwnd, (HMENU)TITLEDIT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls[4] = CreateWindow("LISTBOX", TABLIST_MSG, STL_LIST, 30, 30, 400, 400, hwnd, (HMENU)TABLIST_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls[5] = CreateWindow("BUTTON", ADDCOLUMN_MSG, STL_BUTTON, 830, 160, 150, 24, hwnd, (HMENU)ADDCOLUMN_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls[6] = CreateWindow("BUTTON", ADDTABLE_MSG, STL_BUTTON, 830, 460, 150, 24, hwnd, (HMENU)ADDTABLE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    addColumn(hwnd, crTableMenuControls);
}

void addColumn(HWND hwnd, HWND *crTableMenuControls)
{
    crTableMenuControls[7] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", COLUMNEDIT_MSG, STL_EDIT, 530, 75, 150, 24, hwnd, (HMENU)16, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls[8] = CreateWindow("COMBOBOX", COLUMNEDIT_MSG, STL_COMBO, 690, 75, 150, 100, hwnd, (HMENU)17, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
}