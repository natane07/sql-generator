#include ".\..\include\crtable.h"
#include ".\..\include\app.h"
#include ".\..\include\utils.h"
#include ".\..\include\sql.h"
#include ".\..\include\file.h"
#include <windows.h>

void createCrTableMenu(HWND hwnd, CrTableControls *crTableMenuControls, SqlRules *rules, SqlModel *model)
{
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
    crTableMenuControls->currentTableNumber = 0;
    addColumn(hwnd, crTableMenuControls, SET_MENU, rules, model);
    setModel(model);
    SqlTable current = saveTable(hwnd, crTableMenuControls, rules, model);
    updateModel(model, &current, crTableMenuControls->currentTableNumber);
    destroyTable(&current);
    updateTableList(hwnd, model);
}

void addColumn(HWND hwnd, CrTableControls *crTableMenuControls, int mode, SqlRules *rules, SqlModel *model)
{
    if (mode == SET_MENU)
    {
        crTableMenuControls->colNumber = 0;
        crTableMenuControls->fkNumber = 0;
    }
    if ((mode == COL_ADD || mode == SET_MENU) && crTableMenuControls->colNumber < rules->maxCol)
    {
        int index = crTableMenuControls->colNumber * CTRL_PER_FULL_COL;
        int columnNumber = crTableMenuControls->colNumber;
        long long id = COL_FIRST_ASSIGNABLE_ID + crTableMenuControls->colNumber * CTRL_PER_COL;
        char colName[SQL_COLUMN_NAME_MAX_LENGTH];
        sprintf(colName, "%s%d", SQL_COL_DEF_NAME, crTableMenuControls->colNumber + 1);
        crTableMenuControls->columns[index] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", colName, STL_EDIT, 530, 75 + (COLUMN_SPACE_PX * columnNumber), 150, 24, hwnd, (HMENU)id, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        crTableMenuControls->columns[index + 1] = CreateWindow("COMBOBOX", COLUMNEDIT_MSG, STL_COMBO, 690, 75 + (COLUMN_SPACE_PX * columnNumber), 150, 100, hwnd, (HMENU)COMBOS_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        ++id;
        crTableMenuControls->columns[index + 2] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", COLUMNEDIT_MSG, STL_EDIT, 850, 75 + (COLUMN_SPACE_PX * columnNumber), 75, 24, hwnd, (HMENU)id, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        crTableMenuControls->columns[index + 3] = CreateWindow("BUTTON", RD_AI, STL_RADIO, 935, 75 + (COLUMN_SPACE_PX * columnNumber), 50, 24, hwnd, (HMENU)RADIO_BTN_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        crTableMenuControls->columns[index + 4] = CreateWindow("BUTTON", RD_NULL, STL_RADIO, 995, 75 + (COLUMN_SPACE_PX * columnNumber), 50, 24, hwnd, (HMENU)RADIO_BTN_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        crTableMenuControls->columns[index + 5] = CreateWindow("BUTTON", RD_PK, STL_RADIO, 1055, 75 + (COLUMN_SPACE_PX * columnNumber), 50, 24, hwnd, (HMENU)RADIO_BTN_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        changeRadioState(crTableMenuControls->columns[index + 4]);
        addTypes(crTableMenuControls->columns[index + 1], rules);
        crTableMenuControls->colNumber++;
        checkTypeReqNum(crTableMenuControls, rules);
        checkPkNonVacuity(crTableMenuControls);
    }
    if (mode == FK_ADD && crTableMenuControls->fkNumber < rules->maxFk)
    {
        int index = crTableMenuControls->fkNumber * CTRL_PER_FK;
        int fkNumber = crTableMenuControls->fkNumber;
        crTableMenuControls->fk[index] = CreateWindow("COMBOBOX", COLUMNEDIT_MSG, STL_COMBO, 1145, 75 + (COLUMN_SPACE_PX * fkNumber), 100, 100, hwnd, (HMENU)FK_FIRST_ASSIGNABLE_ID + index, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        crTableMenuControls->fk[index + 1] = CreateWindow("COMBOBOX", COLUMNEDIT_MSG, STL_COMBO, 1255, 75 + (COLUMN_SPACE_PX * fkNumber), 100, 100, hwnd, (HMENU)FK_CMB_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        crTableMenuControls->fk[index + 2] = CreateWindow("COMBOBOX", COLUMNEDIT_MSG, STL_COMBO, 1365, 75 + (COLUMN_SPACE_PX * fkNumber), 100, 100, hwnd, (HMENU)FK_FIRST_ASSIGNABLE_ID + index + 1, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        fillColumnCombo(crTableMenuControls->fk[index], model, crTableMenuControls->currentTableNumber);
        fillTableCombo(crTableMenuControls->fk[index + 1], model);
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
        int index = (crTableMenuControls->colNumber - 1) * CTRL_PER_FULL_COL;
        for (i = 0; i < CTRL_PER_FULL_COL; i++)
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

void checkTypeReqNum(CrTableControls *controls, SqlRules *rules)
{
    int i;
    int ctrlPerCol = CTRL_PER_FULL_COL;
    int indexOfCombo = COL_TYPE_COMBO_INDEX;
    int indexOfEdit = COL_TYPE_EDIT_INDEX;
    char buffer[MAX_TYPE_LENGTH];
    HWND combo, edit;
    for (i = 0; i < controls->colNumber; i++)
    {
        combo = controls->columns[i * ctrlPerCol + indexOfCombo];
        edit = controls->columns[i * ctrlPerCol + indexOfEdit];
        getCurrentStringFromComboDir(combo, buffer);
        if (has(rules->numReqTypes, buffer))
        {
            enableEdit(edit);
        }
        else
        {
            disableEdit(edit);
        }
    }
}

void checkPkNonVacuity(CrTableControls *controls)
{
    int i;
    int ctrlPerCol = CTRL_PER_FULL_COL;
    int indexOfNull = COL_NULL_INDEX;
    int indexOfPk = COL_PK_INDEX;
    HWND null, pk;
    for (i = 0; i < controls->colNumber; i++)
    {
        null = controls->columns[i * ctrlPerCol + indexOfNull];
        pk = controls->columns[i * ctrlPerCol + indexOfPk];
        if (getRadioState(pk))
        {
            disableRadio(null);
        }
    }
}

void updateTableList(HWND hwnd, SqlModel *model)
{
    int i;
    clearTableList(hwnd);
    for (i = 0; i < model->tableCount; i++)
    {
        addTableToList(hwnd, model->tables[i].name);
    }
}

void fillColumnCombo(HWND combo, SqlModel *model, int currentTable)
{
    int i;
    SqlTable table = model->tables[currentTable];
    destroyComboContent(combo);
    for (i = 0; i < table.columnCount; i++)
    {
        addStringToComboDir(combo, table.columns[i].name);
    }
}

void fillTableCombo(HWND combo, SqlModel *model)
{
    int i;
    destroyComboContent(combo);
    for (i = 0; i < model->tableCount; i++)
    {
        addStringToComboDir(combo, model->tables[i].name);
    }
}

void fillPColumnCombo(CrTableControls *controls, SqlModel *model)
{
    int i, j, index, sindex;
    HWND tabHwnd, colHwnd;
    for (i = 0; i < controls->fkNumber; i++)
    {
        tabHwnd = controls->fk[i * CTRL_PER_FK + FK_PTAB_INDEX];
        colHwnd = controls->fk[i * CTRL_PER_FK + FK_PCOL_INDEX];
        index = getComboCursorDir(tabHwnd);
        if (index != CB_ERR)
        {
            sindex = getComboCursorDir(colHwnd);
            destroyComboContent(colHwnd);
            for (j = 0; j < model->tables[index].columnCount; j++)
            {
                addStringToComboDir(colHwnd, model->tables[index].columns[j].name);
            }
            if (sindex != CB_ERR && sindex <= j)
                setComboCursorDir(colHwnd, sindex);
        }
    }
}

void clearTableList(HWND hwnd)
{
    clearListBox(hwnd, TABLIST_ID);
}

int checkTable(SqlModel *model, SqlTable *table, int currentTableIndex, SqlRules *rules)
{
    int i;
    List *tabNames = listInit();
    List *cols = listInit();
    for (i = 0; i < model->tableCount; i++)
    {
        push(tabNames, model->tables[i].name);
    }
    for (i = 0; i < table->columnCount; i++)
    {
        push(cols, table->columns[i].name);
    }
    if (!isStringSafe(table->name))
    {
        printError(CRTAB_ERR_TAB_NAME_UNSAFE);
        return 0;
    }
    if (strlen(table->name) > SQL_TABLE_NAME_MAX_LENGTH || strlen(table->name) < SQL_TABLE_NAME_MIN_LENGTH)
    {
        printError(CRTAB_ERR_TAB_NAME_LENGTH);
        return 0;
    }
    if (has(tabNames, table->name) && findIndex(tabNames, simpleCompare, table->name) != currentTableIndex)
    {
        printError(CRTAB_ERR_TAB_NAME_EXISTS);
        return 0;
    }
    for (i = 0; i < table->columnCount; i++)
    {
        if (!isStringSafe(table->columns[i].name))
        {
            printError(CRTAB_ERR_COL_NAME_UNSAFE);
            return 0;
        }
        if (strlen(table->columns[i].name) > SQL_COLUMN_NAME_MAX_LENGTH || strlen(table->columns[i].name) < SQL_COLUMN_NAME_MIN_LENGTH)
        {
            printError(CRTAB_ERR_COL_NAME_LENGTH);
            return 0;
        }
        if (hasClone(cols))
        {
            printError(CRTAB_ERR_COL_NAME_EXISTS);
            return 0;
        }
        if (has(rules->numReqTypes, table->columns[i].type) && (table->columns[i].size > MAX_VAR_LENGTH || table->columns[i].size < MIN_VAR_LENGTH))
        {
            printError(CRTAB_ERR_COL_LENGTH);
            return 0;
        }
    }
    for (i = 0; i < table->relationCount; i++)
    {
        if (strlen(table->relations[i].columnName) == 0 || strlen(table->relations[i].pointedColumnName) == 0 || strlen(table->relations[i].pointedTableName) == 0)
        {
            printError(CRTAB_ERR_FK_EMPTY_FIELD);
            return 0;
        }
    }
    destroyList(tabNames);
    destroyList(cols);
    return 1;
}

SqlTable saveTable(HWND hwnd, CrTableControls *controls, SqlRules *rules, SqlModel *model)
{
    int i;
    SqlTable table;
    char tName[SQL_TABLE_NAME_MAX_LENGTH];
    int ctrlPerCol = CTRL_PER_FULL_COL;
    int ctrlPerFk = CTRL_PER_FK;
    getTableName(hwnd, tName);
    setTable(&table, tName);
    table.columnCount = controls->colNumber;
    SqlColumn *cols = malloc(sizeof(SqlColumn) * table.columnCount);
    for (i = 0; i < table.columnCount; i++)
    {
        getStringFromWinDir(controls->columns[i * ctrlPerCol + COL_TITLE_INDEX], cols[i].name, SQL_COLUMN_NAME_MAX_LENGTH);
        getCurrentStringFromComboDir(controls->columns[i * ctrlPerCol + COL_TYPE_COMBO_INDEX], cols[i].type);
        if (has(rules->numReqTypes, cols[i].type))
        {
            char digit[MAX_DIGIT_LENGTH];
            getStringFromWinDir(controls->columns[i * ctrlPerCol + COL_TYPE_EDIT_INDEX], digit, MAX_DIGIT_LENGTH);
            cols[i].size = atoi(digit);
        }
        else
        {
            cols[i].size = -1;
        }
        cols[i].ai = getRadioState(controls->columns[i * ctrlPerCol + COL_AI_INDEX]);
        cols[i].pk = getRadioState(controls->columns[i * ctrlPerCol + COL_PK_INDEX]);
        cols[i].nullable = getRadioState(controls->columns[i * ctrlPerCol + COL_NULL_INDEX]);
    }
    addColumns(&table, cols, table.columnCount);
    free(cols);
    SqlForeignKey *fks = malloc(sizeof(SqlForeignKey) * controls->fkNumber);
    for (i = 0; i < controls->fkNumber; i++)
    {
        getCurrentStringFromComboDir(controls->fk[i * ctrlPerFk + FK_COL_INDEX], fks[i].columnName);
        getCurrentStringFromComboDir(controls->fk[i * ctrlPerFk + FK_PTAB_INDEX], fks[i].pointedTableName);
        getCurrentStringFromComboDir(controls->fk[i * ctrlPerFk + FK_PCOL_INDEX], fks[i].pointedColumnName);
    }
    addRelations(&table, fks, controls->fkNumber);
    free(fks);
    return table;
}

SqlTable getDefaultTable(int tabNumber)
{
    SqlTable table;
    SqlColumn col;
    char buffer[SQL_TABLE_NAME_MAX_LENGTH];
    sprintf(buffer, "%s%d", DEF_TAB_NAME, tabNumber);
    setTable(&table, buffer);
    setDefaultPrimaryKey(&col);
    addColumns(&table, &col, 1);
    return table;
}

void updateModel(SqlModel *model, SqlTable *table, int tablePos)
{
    int i;
    if (table == NULL)
    {
        int counter = 0;
        int tCount = model->tableCount - 1;
        SqlTable *temp = malloc(sizeof(SqlTable) * tCount);
        for (i = 0; i < model->tableCount; i++)
        {
            if (i != tablePos)
            {
                setTable(temp + counter, model->tables[i].name);
                addColumns(temp + counter, model->tables[i].columns, model->tables[i].columnCount);
                addRelations(temp + counter, model->tables[i].relations, model->tables[i].relationCount);
                counter++;
            }
        }
        destroyModel(model);
        addTables(model, temp, tCount);
        free(temp);
    }
    else if (tablePos >= model->tableCount)
    {
        SqlTable *temp = malloc(sizeof(SqlTable) * (tablePos + 1));
        for (i = 0; i < model->tableCount; i++)
        {
            setTable(temp + i, model->tables[i].name);
            addColumns(temp + i, model->tables[i].columns, model->tables[i].columnCount);
            addRelations(temp + i, model->tables[i].relations, model->tables[i].relationCount);
        }
        setTable(temp + tablePos, table->name);
        addColumns(temp + tablePos, table->columns, table->columnCount);
        addRelations(temp + tablePos, table->relations, table->relationCount);
        destroyModel(model);
        addTables(model, temp, tablePos + 1);
        free(temp);
    }
    else
    {
        destroyTable(model->tables + tablePos);
        setTable(model->tables + tablePos, table->name);
        addColumns(model->tables + tablePos, table->columns, table->columnCount);
        addRelations(model->tables + tablePos, table->relations, table->relationCount);
    }
}

void loadFallbackTable(SqlModel *model, HWND hwnd, CrTableControls *controls, SqlRules *rules)
{
    if (model->tableCount > 0)
    {
        loadTable(model->tables, hwnd, controls, rules, model);
    }
    else
    {
        SqlTable table = getDefaultTable(0);
        loadTable(&table, hwnd, controls, rules, model);
        updateModel(model, &table, 0);
        destroyTable(&table);
    }
}

void loadTable(SqlTable *table, HWND hwnd, CrTableControls *controls, SqlRules *rules, SqlModel *model)
{
    int i, j, index;
    int ctrlPerCol = CTRL_PER_FULL_COL;
    int ctrlPerFk = CTRL_PER_FK;
    char digit[MAX_DIGIT_LENGTH];
    destroyMenu(controls->columns, CRTABLE_WIN_COL_CTRL_NUM);
    destroyMenu(controls->fk, CRTABLE_WIN_FK_CTRL_NUM);
    controls->fkNumber = 0;
    controls->colNumber = 0;
    setTableName(hwnd, table->name);
    for (i = 0; i < table->columnCount; i++)
    {
        addColumn(hwnd, controls, COL_ADD, rules, model);
        sendWinTextDir(controls->columns[i * ctrlPerCol + COL_TITLE_INDEX], table->columns[i].name);
        index = findStringIndexInComboDir(controls->columns[i * ctrlPerCol + COL_TYPE_COMBO_INDEX], table->columns[i].type);
        if (index == CB_ERR)
            index = 0;
        setComboCursorDir(controls->columns[i * ctrlPerCol + COL_TYPE_COMBO_INDEX], index);
        if (table->columns[i].size != -1)
        {
            sprintf(digit, "%d", table->columns[i].size);
            sendWinTextDir(controls->columns[i * ctrlPerCol + COL_TYPE_EDIT_INDEX], digit);
        }
        setRadioState(controls->columns[i * ctrlPerCol + COL_AI_INDEX], table->columns[i].ai);
        setRadioState(controls->columns[i * ctrlPerCol + COL_PK_INDEX], table->columns[i].pk);
        setRadioState(controls->columns[i * ctrlPerCol + COL_NULL_INDEX], table->columns[i].nullable);
    }
    for (i = 0; i < table->relationCount; i++)
    {
        addColumn(hwnd, controls, FK_ADD, rules, model);
        index = findStringIndexInComboDir(controls->fk[i * ctrlPerFk + FK_COL_INDEX], table->relations[i].columnName);
        if (index != CB_ERR)
            setComboCursorDir(controls->fk[i * ctrlPerFk + FK_COL_INDEX], index);
        index = findStringIndexInComboDir(controls->fk[i * ctrlPerFk + FK_PTAB_INDEX], table->relations[i].pointedTableName);
        if (index != CB_ERR)
        {
            setComboCursorDir(controls->fk[i * ctrlPerFk + FK_PTAB_INDEX], index);
            for (j = 0; j < model->tables[index].columnCount; j++)
            {
                addStringToComboDir(controls->fk[i * ctrlPerFk + FK_PCOL_INDEX], model->tables[index].columns[j].name);
            }
            index = findStringIndexInComboDir(controls->fk[i * ctrlPerFk + FK_PCOL_INDEX], table->relations[i].pointedColumnName);
            if (index != CB_ERR)
                setComboCursorDir(controls->fk[i * ctrlPerFk + FK_PCOL_INDEX], index);
        }
    }
    checkTypeReqNum(controls, rules);
    checkPkNonVacuity(controls);
}

void getTableName(HWND hwnd, char *buffer)
{
    getStringFromWin(hwnd, TITLEDIT_ID, buffer, SQL_TABLE_NAME_MAX_LENGTH);
}

int getTableListCursor(HWND hwnd)
{
    return getListCursor(hwnd, TABLIST_ID);
}

void setTableName(HWND hwnd, char *buffer)
{
    sendWinText(hwnd, TITLEDIT_ID, buffer);
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

void exportModel(HWND hwnd, SqlModel *model)
{
    OPENFILENAME ofn;
    char file[MAX_PATH_LENGTH];
    setOfn(hwnd, &ofn, file);
    if (GetSaveFileNameA(&ofn))
    {
        FILE *fp = fopen(file, "w");
        if (fp != NULL)
        {
            generateScript(model , fp);
        }
        fclose(fp);
    }
}

void setOfn(HWND hwnd, OPENFILENAME *ofn, char *file)
{
    ofn->lStructSize = sizeof(OPENFILENAME);
    ofn->hwndOwner = hwnd;
    ofn->hInstance = NULL;
    ofn->lpstrFilter = "SQL Scripts (*.sql)\0*.sql\0";
    ofn->lpstrCustomFilter = NULL;
    ofn->nMaxCustFilter = 0;
    ofn->nFilterIndex = 1;
    ofn->lpstrFile = file;
    ofn->nMaxFile = MAX_PATH_LENGTH;
    ofn->lpstrFileTitle = NULL;
    ofn->nMaxFileTitle = 0;
    ofn->lpstrInitialDir = NULL;
    ofn->lpstrTitle = NULL;
    ofn->Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
    ofn->nFileOffset = 0;
    ofn->nFileExtension = 0;
    ofn->lpstrDefExt = "sql";
    ofn->lCustData = 0;
    ofn->lpfnHook = NULL;
    ofn->lpTemplateName = NULL;
}