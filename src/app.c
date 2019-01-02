#include "..\include\app.h"
#include "..\include\file.h"
#include "..\include\utils.h"
#include "..\include\parser.h"
#include "..\include\menu.h"
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
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND mainMenuControls[MAIN_WIN_CTRL_NUM];
    static AppData appData;
    switch (msg)
    {
    case WM_CREATE:
        loadIcon(hwnd, APP_ICON);
        createWindowBar(hwnd);
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
        case CRTABLE_ID:
            destroyMainMenu(mainMenuControls);
            break;
        case PROFILESEL_ID:
            switch (HIWORD(wParam))
            {
            case CBN_SELCHANGE:
            {
                int index;
                char buffer[MAX_SENT_LENGTH];
                index = getComboCursor(hwnd, PROFILESEL_ID);
                appData.pName = updateField(appData.pName, hwnd, PROFILESEL_ID, index);
                setMessage(buffer, appData.pName);
                sendWinText(hwnd, PROFILEHINT_ID, buffer);
            }
            break;
            }
            break;
        case PROFILECRSUB_ID:
            createProfile(hwnd, &appData);
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

void createClass(WNDCLASSEX *wc, HINSTANCE hInstance, const char *className)
{
    wc->cbSize = sizeof(WNDCLASSEX);
    wc->style = 0;
    wc->lpfnWndProc = WndProc;
    wc->cbClsExtra = 0;
    wc->cbWndExtra = 0;
    wc->hInstance = hInstance;
    wc->hIcon = NULL;
    wc->hCursor = LoadCursor(NULL, IDC_ARROW);
    wc->hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wc->lpszMenuName = NULL;
    wc->lpszClassName = className;
    wc->hIconSm = NULL;
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

void createWindowBar(HWND hwnd)
{
    HMENU hMenu, hSubMenu;
    hMenu = CreateMenu();
    hSubMenu = CreatePopupMenu();
    AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT_PTR)hSubMenu, "Menu");
    AppendMenu(hSubMenu, MF_STRING, EXIT_ID, EXIT_MSG);
    SetMenu(hwnd, hMenu);
}

void setVersion(HWND hwnd, AppData *appData)
{
    char buffer[MAX_SENT_LENGTH];
    sprintf(buffer, "%s [%s]", VERSIONHINT_MSG, appData->version);
    sendWinText(hwnd, VERSIONHINT_ID, buffer);
}

void setExistingProfiles(HWND hwnd, AppData *appData)
{
    Element *current = appData->existingProfiles->first;
    int index;
    char buffer[MAX_SENT_LENGTH];
    while (current != NULL)
    {
        addStringToCombo(hwnd, PROFILESEL_ID, current->content);
        current = current->next;
    }
    index = findStringIndexInCombo(hwnd, PROFILESEL_ID, appData->pName);
    if (index == CB_ERR)
        index = 0;
    setComboCursor(hwnd, PROFILESEL_ID, index);
    appData->pName = updateField(appData->pName, hwnd, PROFILESEL_ID, index);
    setMessage(buffer, appData->pName);
    sendWinText(hwnd, PROFILEHINT_ID, buffer);
}

void setMessage(char *message, char *pName)
{
    sprintf(message, "%s %s!", PROFILEHINT_MSG, pName);
}

char *updateField(char *destination, HWND hwnd, int controlId, int idString)
{
    char buffer[MAX_NAME_LENGTH];
    initMemory(buffer, MAX_NAME_LENGTH);
    getStringFromCombo(hwnd, controlId, idString, buffer);
    return resetString(destination, buffer);
}

void createProfile(HWND hwnd, AppData *appData)
{
    char buffer[MAX_NAME_LENGTH];
    initMemory(buffer, MAX_NAME_LENGTH);
    getStringFromWin(hwnd, PROFILECR_ID, buffer, MAX_NAME_LENGTH);
    int ok = checkProfileName(appData->existingProfiles, buffer);
    if (ok)
    {
        saveProfile(hwnd, appData, buffer);
    }
}

void saveProfile(HWND hwnd, AppData *appData, char *pName)
{
    int index;
    char buffer[MAX_SENT_LENGTH];
    appData->pName = resetString(appData->pName, pName);
    push(appData->existingProfiles, pName);
    index = addStringToCombo(hwnd, PROFILESEL_ID, pName);
    setComboCursor(hwnd, PROFILESEL_ID, index);
    setMessage(buffer, appData->pName);
    sendWinText(hwnd, PROFILEHINT_ID, buffer);
    FILE *fp = openFile(getenv(LOCALSTORAGE), PROFILES_FILE, "a");
    if (fp != NULL)
    {
        fprintf(fp, "%s\n", pName);
        fclose(fp);
    }
    index = findIndex(appData->settings, compareKey, SETT_DEF_PRO);
    if (index != -1)
    {
        char buffer[MAX_SETTING_LENGTH];
        printIniToString(buffer, SETT_DEF_PRO, pName);
        setElement(appData->settings, index, buffer);
        fp = openFile(getenv(LOCALSTORAGE), CONFIG_FILE, "w");
        if (fp != NULL)
        {
            writeListToFile(appData->settings, fp);
        }
    }
    sprintf(buffer, "%s created successfully!", pName);
    printInfo(buffer);
}

void loadProfile(AppData *appData)
{
    // printf("%s loaded successfully!\n", appData->pName);
    // initUserFile();
}

int checkProfileName(List *profiles, char *profile)
{
    if (has(profiles, profile))
    {
        printError(ERR_NAME_TAKEN);
        return 0;
    }
    if (!isStringSafe(profile))
    {
        printError(ERR_NAME_UNSAFE);
        return 0;
    }
    if (strlen(profile) < MIN_NAME_LENGTH || strlen(profile) >= MAX_NAME_LENGTH)
    {
        printError(ERR_NAME_LENGTH);
        return 0;
    }
    return 1;
}

void destroy(AppData *appData)
{
    destroyList(appData->existingProfiles);
    destroyList(appData->settings);
    free(appData->version);
    free(appData->pName);
}