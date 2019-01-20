#include ".\..\include\crtable.h"
#include ".\..\include\app.h"
#include ".\..\include\utils.h"
#include ".\..\include\sql.h"
#include ".\..\include\file.h"
#include <windows.h>

void createCrTableMenu(HWND hwnd, CrTableControls *crTableMenuControls, SqlRules *rules)
{
    char buffer[SQL_TABLE_NAME_MAX_LENGTH];
    crTableMenuControls->mainControls[0] = CreateWindow("STATIC", LITABHINT_MSG, STL_TEXT, 30, 10, 100, 24, hwnd, (HMENU)LITABHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls->mainControls[1] = CreateWindow("STATIC", TABEDHINT_MSG, STL_TEXT, 830, 10, 100, 24, hwnd, (HMENU)TABEDHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls->mainControls[2] = CreateWindow("STATIC", TITLEHINT_MSG, STL_TEXT, 690, 40, 150, 24, hwnd, (HMENU)TITLEHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls->mainControls[3] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", TITLEDIT_MSG, STL_EDIT, 830, 40, 150, 24, hwnd, (HMENU)TITLEDIT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls->mainControls[4] = CreateWindowEx(WS_EX_CLIENTEDGE, "LISTBOX", TABLIST_MSG, STL_LIST, 30, 30, 400, 400, hwnd, (HMENU)TABLIST_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls->mainControls[5] = CreateWindow("BUTTON", ADDCOLUMN_MSG, STL_BUTTON, 1150, 560, 150, 24, hwnd, (HMENU)ADDCOLUMN_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls->mainControls[6] = CreateWindow("BUTTON", ADDTABLE_MSG, STL_BUTTON, 830, 700, 150, 24, hwnd, (HMENU)ADDTABLE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls->mainControls[7] = CreateWindow("BUTTON", ADDFK_MSG, STL_BUTTON, 1150, 590, 150, 24, hwnd, (HMENU)ADDFK_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls->mainControls[8] = CreateWindow("BUTTON", DELTABLE_MSG, STL_BUTTON, 670, 700, 150, 24, hwnd, (HMENU)DELTABLE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls->mainControls[9] = CreateWindow("BUTTON", EXPORTMODEL_MSG, STL_BUTTON, 155, 700, 150, 24, hwnd, (HMENU)EXPORTMODEL_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls->mainControls[10] = CreateWindow("BUTTON", SAVETABLE_MSG, STL_BUTTON, 990, 700, 150, 24, hwnd, (HMENU)SAVETABLE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls->mainControls[11] = CreateWindow("BUTTON", REMOVECOL_MSG, STL_BUTTON, 1310, 560, 150, 24, hwnd, (HMENU)REMOVECOL_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    crTableMenuControls->mainControls[12] = CreateWindow("BUTTON", REMOVEFK_MSG, STL_BUTTON, 1310, 590, 150, 24, hwnd, (HMENU)REMOVEFK_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    addColumn(hwnd, crTableMenuControls, SET_MENU, rules);
    getTableName(hwnd, buffer);
    addTableToList(hwnd, buffer);
}

void addColumn(HWND hwnd, CrTableControls *crTableMenuControls, int mode, SqlRules *rules)
{
    if (mode == SET_MENU)
    {
        crTableMenuControls->colNumber = 0;
        crTableMenuControls->fkNumber = 0;
    }
    if ((mode == COL_ADD || mode == SET_MENU) && crTableMenuControls->colNumber < rules->maxCol)
    {
        int index = crTableMenuControls->colNumber * CTRL_PER_COL;
        int columnNumber = crTableMenuControls->colNumber;
        long long id = COL_FIRST_ASSIGNABLE_ID + index;
        crTableMenuControls->columns[index] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", COLUMNEDIT_MSG, STL_EDIT, 530, 75 + (COLUMN_SPACE_PX * columnNumber), 150, 24, hwnd, (HMENU)id, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        crTableMenuControls->columns[index + 1] = CreateWindow("COMBOBOX", COLUMNEDIT_MSG, STL_COMBO, 690, 75 + (COLUMN_SPACE_PX * columnNumber), 150, 100, hwnd, (HMENU)COMBOS_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        ++id;
        crTableMenuControls->columns[index + 2] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", COLUMNEDIT_MSG, STL_EDIT, 850, 75 + (COLUMN_SPACE_PX * columnNumber), 75, 24, hwnd, (HMENU)id, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        crTableMenuControls->columns[index + 3] = CreateWindow("BUTTON", RD_AI, STL_RADIO, 935, 75 + (COLUMN_SPACE_PX * columnNumber), 50, 24, hwnd, (HMENU)RADIO_BTN_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        crTableMenuControls->columns[index + 4] = CreateWindow("BUTTON", RD_NULL, STL_RADIO, 995, 75 + (COLUMN_SPACE_PX * columnNumber), 50, 24, hwnd, (HMENU)RADIO_BTN_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        crTableMenuControls->columns[index + 5] = CreateWindow("BUTTON", RD_PK, STL_RADIO, 1055, 75 + (COLUMN_SPACE_PX * columnNumber), 50, 24, hwnd, (HMENU)RADIO_BTN_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        changeRadioState(crTableMenuControls->columns[index + 4]);
        addTypes(crTableMenuControls->columns[index + 1], rules);
        checkTypeReqNum(crTableMenuControls->columns[index + 2], crTableMenuControls->columns[index + 1], rules);
        crTableMenuControls->colNumber++;
    }
    if (mode == FK_ADD && crTableMenuControls->fkNumber < rules->maxFk)
    {
        int index = crTableMenuControls->fkNumber * CTRL_PER_FK;
        int fkNumber = crTableMenuControls->fkNumber;
        crTableMenuControls->fk[index] = CreateWindow("COMBOBOX", COLUMNEDIT_MSG, STL_COMBO, 1145, 75 + (COLUMN_SPACE_PX * fkNumber), 100, 100, hwnd, (HMENU)FK_FIRST_ASSIGNABLE_ID + index, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        crTableMenuControls->fk[index + 1] = CreateWindow("COMBOBOX", COLUMNEDIT_MSG, STL_COMBO, 1255, 75 + (COLUMN_SPACE_PX * fkNumber), 100, 100, hwnd, (HMENU)FK_FIRST_ASSIGNABLE_ID + index + 1, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        crTableMenuControls->fk[index + 2] = CreateWindow("COMBOBOX", COLUMNEDIT_MSG, STL_COMBO, 1365, 75 + (COLUMN_SPACE_PX * fkNumber), 100, 100, hwnd, (HMENU)FK_FIRST_ASSIGNABLE_ID + index + 2, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        crTableMenuControls->fkNumber++;
    }
}

void removeColumn(HWND hwnd, CrTableControls *crTableMenuControls, int mode, SqlRules *rules)
{
    if (mode == FK_DEL && crTableMenuControls->fkNumber > 0)
    {
        int i;
        int index = (crTableMenuControls->fkNumber - 1) * CTRL_PER_FK;
        for (i = 0; i < CTRL_PER_FK; i++)
        {
            DestroyWindow(crTableMenuControls->fk[index + i]);
        }
        crTableMenuControls->fkNumber--;
    }
    if (mode == COL_DEL && crTableMenuControls->colNumber > 1)
    {
        int i;
        int index = (crTableMenuControls->colNumber - 1) * CTRL_PER_COL;
        for (i = 0; i < CTRL_PER_COL; i++)
        {
            DestroyWindow(crTableMenuControls->columns[index + i]);
        }
        crTableMenuControls->colNumber--;
    }
}

void addTypes(HWND combo, SqlRules *rules)
{
    Element *current = rules->types->first;
    while (current != NULL)
    {
        addStringToComboDir(combo, current->content);
        current = current->next;
    }
    setComboCursorDir(combo, 0);
}

void checkTypeReqNum(HWND edit, HWND combo, SqlRules *rules)
{
    char buffer[MAX_TYPE_LENGTH];
    getCurrentStringFromComboDir(combo, buffer);
    if (has(rules->numReqTypes, buffer))
    {
        disableEdit(edit);
    }
    else
    {
        enableEdit(edit);
    }
}

void getTableName(HWND hwnd, char *buffer)
{
    getStringFromWin(hwnd, TITLEDIT_ID, buffer, SQL_TABLE_NAME_MAX_LENGTH);
}

void addTableToList(HWND hwnd, char *tabName)
{
    addStringToList(hwnd, TABLIST_ID, tabName);
}

void destroyCrTableMenu(CrTableControls *controls)
{
    destroyMenu(controls->mainControls, CRTABLE_WIN_MAIN_CTRL_NUM);
    destroyMenu(controls->columns, CRTABLE_WIN_COL_CTRL_NUM);
    destroyMenu(controls->fk, CRTABLE_WIN_FK_CTRL_NUM);
}