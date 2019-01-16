#include "..\include\app.h"
#include "..\include\file.h"
#include "..\include\utils.h"
#include "..\include\parser.h"
#include "..\include\menu.h"
#include "..\include\crtable.h"
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
    static CrTableControls crTableMenuControls;
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
            destroyCrTableMenu(&crTableMenuControls);
            createMainMenu(hwnd, mainMenuControls);
            setExistingProfiles(hwnd, &appData);
            setVersion(hwnd, &appData);
            break;
        case CRTABLE_ID:
        {
            int ok = loadProfile(&appData);
            if (ok)
            {
                destroyMainMenu(mainMenuControls);
                createCrTableMenu(hwnd, &crTableMenuControls, &appData.rules);
                EnableMenuItem(hMenu, GTMENU_ID, MF_ENABLED);
            }
            break;
        }
        case INSDATA_ID:
            break;
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
        case RADIO_BTN_ID:
            changeRadioState((HWND)lParam);
            break;
        case ADDCOLUMN_ID:
            addColumn(hwnd, &crTableMenuControls, COL_ADD, &appData.rules);
            break;
        case ADDFK_ID:
            addColumn(hwnd, &crTableMenuControls, FK_ADD, &appData.rules);
            break;
        case REMOVEFK_ID:
            removeColumn(hwnd, &crTableMenuControls, FK_DEL, &appData.rules);
            break;
        case REMOVECOL_ID:
            removeColumn(hwnd, &crTableMenuControls, COL_DEL, &appData.rules);
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