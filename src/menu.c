#include <windows.h>
#include ".\..\include\menu.h"
#include ".\..\include\app.h"

void createMainMenu(HWND hwnd, HWND *mainMenuControls)
{
    int buttonAppearance = WS_VISIBLE | WS_CHILD | BS_MULTILINE;
    int listAppearance = WS_VISIBLE | WS_CHILD | WS_VSCROLL | CBS_DROPDOWNLIST;
    int textAppearance = WS_VISIBLE | WS_CHILD;
    mainMenuControls[0] = CreateWindow("COMBOBOX", PROFILESEL_MSG, listAppearance, 10, 85, 150, 150, hwnd, (HMENU)PROFILESEL_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[1] = CreateWindow("STATIC", PROFILEHINT_MSG, textAppearance, 10, 10, 100, 100, hwnd, (HMENU)PROFILEHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[2] = CreateWindow("BUTTON", CRTABLE_MSG, buttonAppearance, 10, 160, 150, 30, hwnd, (HMENU)CRTABLE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[3] = CreateWindow("BUTTON", INSDATA_MSG, buttonAppearance, 170, 160, 150, 30, hwnd, (HMENU)INSDATA_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
}

void destroyMainMenu(HWND *mainMenuControls)
{
    DestroyWindow(mainMenuControls[0]);
    DestroyWindow(mainMenuControls[1]);
    DestroyWindow(mainMenuControls[2]);
    DestroyWindow(mainMenuControls[3]);
}