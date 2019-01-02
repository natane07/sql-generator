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
        {
            int ok = loadProfile(&appData);
            if (ok)
                destroyMainMenu(mainMenuControls);
            break;
        }
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
                break;
            }
            default:
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

void destroy(AppData *appData)
{
    destroyList(appData->existingProfiles);
    destroyList(appData->settings);
    free(appData->version);
    free(appData->pName);
}