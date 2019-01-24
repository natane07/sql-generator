#include "..\include\app.h"
#include "..\include\file.h"
#include "..\include\utils.h"
#include "..\include\parser.h"
#include "..\include\menu.h"
#include "..\include\crtable.h"
#include "..\include\insdata.h"
#include "..\include\sql.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

void initAppdata(AppData *appData)
{
    setAppData(appData);
    initFs(appData);
}

void setAppData(AppData *appData)
{
    appData->version = NULL;
    appData->pName = NULL;
    appData->existingProfiles = NULL;
    appData->settings = NULL;
    appData->rules.types = NULL;
    appData->rules.numReqTypes = NULL;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND mainMenuControls[MAIN_WIN_CTRL_NUM];
    static HWND insDataControls[INSDATA_WIN_CTRL_NUM];
    static CrTableControls crTableMenuControls;
    static int currentMenu = MAIN;
    static HMENU hMenu;
    static AppData appData;
    switch (msg)
    {
    case WM_CREATE:
        loadIcon(hwnd, APP_ICON);
        createWindowBar(hwnd, &hMenu);
        createMainMenu(hwnd, mainMenuControls);
        initAppdata(&appData);
        setExistingProfiles(hwnd, &appData);
        setVersion(hwnd, &appData);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case EXIT_ID:
            destroy(&appData);
            PostMessage(hwnd, WM_CLOSE, 0, 0);
            break;
        case GTMENU_ID:
            EnableMenuItem(hMenu, GTMENU_ID, MF_GRAYED);
            switch (currentMenu)
            {
            case CRTABLE:
                destroyCrTableMenu(&crTableMenuControls);
                destroyModel(&appData.model);
                break;
            case INSDATA:
                destroyInsDataMenu(insDataControls);
                break;
            }
            createMainMenu(hwnd, mainMenuControls);
            setExistingProfiles(hwnd, &appData);
            setVersion(hwnd, &appData);
            currentMenu = MAIN;
            break;
        case CRTABLE_ID:
        {
            if (currentMenu == MAIN)
            {
                currentMenu = CRTABLE;
                int ok = loadProfile(&appData);
                if (ok)
                {
                    destroyMainMenu(mainMenuControls);
                    createCrTableMenu(hwnd, &crTableMenuControls, &appData.rules, &appData.model);
                    EnableMenuItem(hMenu, GTMENU_ID, MF_ENABLED);
                }
                else
                {
                    currentMenu = MAIN;
                }
            }
            break;
        }
        case INSDATA_ID:
        {
            if (currentMenu == MAIN)
            {
                currentMenu = INSDATA;
                int ok = loadProfile(&appData);
                if (ok)
                {
                    destroyMainMenu(mainMenuControls);
                    createInsDataMenu(hwnd, insDataControls);
                    EnableMenuItem(hMenu, GTMENU_ID, MF_ENABLED);
                }
                else
                {
                    currentMenu = MAIN;
                }
            }
            break;
        }
        case PROFILESEL_ID:
            if (HIWORD(wParam) == CBN_SELCHANGE)
            {
                int index;
                index = getComboCursor(hwnd, PROFILESEL_ID);
                appData.pName = updateField(appData.pName, hwnd, PROFILESEL_ID, index);
                updateHint(hwnd, appData.pName);
            }
            break;
        case PROFILECRSUB_ID:
            createProfile(hwnd, &appData);
            break;
        case COMBOS_ID:
            if (HIWORD(wParam) == CBN_SELCHANGE)
            {
                checkTypeReqNum(&crTableMenuControls, &appData.rules);
            }
            break;
        case RADIO_BTN_ID:
            changeRadioState((HWND)lParam);
            checkPkNonVacuity(&crTableMenuControls);
            break;
        case ADDCOLUMN_ID:
            addColumn(hwnd, &crTableMenuControls, COL_ADD, &appData.rules, &appData.model);
            break;
        case ADDFK_ID:
            addColumn(hwnd, &crTableMenuControls, FK_ADD, &appData.rules, &appData.model);
            break;
        case ADDTABLE_ID:
        {
            SqlTable table = saveTable(hwnd, &crTableMenuControls, &appData.rules, &appData.model);
            if (checkTable(&appData.model, &table, crTableMenuControls.currentTableNumber, &appData.rules))
            {
                updateModel(&appData.model, &table, crTableMenuControls.currentTableNumber);
                crTableMenuControls.currentTableNumber = appData.model.tableCount;
                SqlTable defTab = getDefaultTable(appData.model.tableCount);
                loadTable(&defTab, hwnd, &crTableMenuControls, &appData.rules, &appData.model);
                updateModel(&appData.model, &defTab, crTableMenuControls.currentTableNumber);
                updateTableList(hwnd, &appData.model);
                destroyTable(&defTab);
            }
            destroyTable(&table);
        }
        break;
        case SAVETABLE_ID:
        {
            SqlTable table = saveTable(hwnd, &crTableMenuControls, &appData.rules, &appData.model);
            if (checkTable(&appData.model, &table, crTableMenuControls.currentTableNumber, &appData.rules))
            {
                updateModel(&appData.model, &table, crTableMenuControls.currentTableNumber);
                updateTableList(hwnd, &appData.model);
                loadTable(&table, hwnd, &crTableMenuControls, &appData.rules, &appData.model);
            }
            destroyTable(&table);
        }
        break;
        case DELTABLE_ID:
            updateModel(&appData.model, NULL, crTableMenuControls.currentTableNumber);
            crTableMenuControls.currentTableNumber = 0;
            loadFallbackTable(&appData.model, hwnd, &crTableMenuControls, &appData.rules);
            updateTableList(hwnd, &appData.model);
            break;
        case TABLIST_ID:
        {
            if (HIWORD(wParam) == LBN_SELCHANGE)
            {
                SqlTable table = saveTable(hwnd, &crTableMenuControls, &appData.rules, &appData.model);
                if (checkTable(&appData.model, &table, crTableMenuControls.currentTableNumber, &appData.rules))
                {
                    updateModel(&appData.model, &table, crTableMenuControls.currentTableNumber);
                    int index = getTableListCursor(hwnd);
                    if (index >= 0 && index < appData.model.tableCount)
                    {
                        crTableMenuControls.currentTableNumber = index;
                        loadTable(appData.model.tables + index, hwnd, &crTableMenuControls, &appData.rules, &appData.model);
                    }
                    updateTableList(hwnd, &appData.model);
                }
                destroyTable(&table);
            }
        }
        break;
        case FK_CMB_ID:
            if (HIWORD(wParam) == CBN_SELCHANGE)
            {
                fillPColumnCombo(&crTableMenuControls, &appData.model);
            }
            break;
        case REMOVEFK_ID:
            removeColumn(hwnd, &crTableMenuControls, FK_DEL, &appData.rules);
            break;
        case REMOVECOL_ID:
            removeColumn(hwnd, &crTableMenuControls, COL_DEL, &appData.rules);
            break;
        case EXPORTMODEL_ID:
            exportModel(hwnd, &appData.model);
            break;
        default:
            break;
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void loadIcon(HWND hwnd, const char *icon)
{
    HICON hIcon, hIconSm;
    hIcon = (HICON)LoadImage(NULL, icon, IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
    if (hIcon)
    {
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    }
    hIconSm = (HICON)LoadImage(NULL, icon, IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
    if (hIconSm)
    {
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSm);
    }
}

void createWindowBar(HWND hwnd, HMENU *hMenu)
{
    HMENU hSubMenu;
    *hMenu = CreateMenu();
    hSubMenu = CreatePopupMenu();
    AppendMenu(*hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, "Menu");
    AppendMenu(hSubMenu, MF_STRING, GTMENU_ID, GTMENU_MSG);
    EnableMenuItem(*hMenu, GTMENU_ID, MF_GRAYED);
    AppendMenu(hSubMenu, MF_STRING, EXIT_ID, EXIT_MSG);
    SetMenu(hwnd, *hMenu);
}

void destroy(AppData *appData)
{
    destroyList(appData->existingProfiles);
    destroyList(appData->settings);
    destroyList(appData->rules.types);
    destroyList(appData->rules.numReqTypes);
    free(appData->version);
    free(appData->pName);
}