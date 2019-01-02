#include <windows.h>
#include ".\..\include\menu.h"
#include ".\..\include\app.h"

void createMainMenu(HWND hwnd, HWND *mainMenuControls)
{
    int buttonAppearance = WS_VISIBLE | WS_CHILD | BS_MULTILINE;
    int listAppearance = WS_VISIBLE | WS_CHILD | WS_VSCROLL | CBS_DROPDOWNLIST;
    int textAppearance = WS_VISIBLE | WS_CHILD;
    int editAppearance = WS_VISIBLE | WS_CHILD | WS_BORDER;
    mainMenuControls[0] = CreateWindow("COMBOBOX", PROFILESEL_MSG, listAppearance, 30, 85, 300, 100, hwnd, (HMENU)PROFILESEL_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[1] = CreateWindow("STATIC", PROFILEHINT_MSG, textAppearance, 30, 10, 400, 24, hwnd, (HMENU)PROFILEHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[2] = CreateWindow("BUTTON", CRTABLE_MSG, buttonAppearance, 245, 160, 150, 24, hwnd, (HMENU)CRTABLE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[3] = CreateWindow("BUTTON", INSDATA_MSG, buttonAppearance, 405, 160, 150, 24, hwnd, (HMENU)INSDATA_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[4] = CreateWindow("STATIC", VERSIONHINT_MSG, textAppearance | SS_RIGHT, 630, 10, 300, 24, hwnd, (HMENU)VERSIONHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[5] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", PROFILECR_MSG, editAppearance, 470, 85, 300, 24, hwnd, (HMENU)PROFILECR_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[6] = CreateWindow("BUTTON", PROFILECRSUB_MSG, buttonAppearance, 780, 85, 150, 24, hwnd, (HMENU)PROFILECRSUB_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[7] = CreateWindow("STATIC", MENUHINT_MSG, textAppearance, 30, 52, 600, 24, hwnd, (HMENU)MENUHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
}

void destroyMainMenu(HWND *mainMenuControls)
{
    int i;
    for (i = 0; i < MAIN_WIN_CTRL_NUM; i++)
        DestroyWindow(mainMenuControls[i]);
}