#include ".\include\app.h"
#include ".\include\utils.h"
#include <windows.h>
#include <string.h>
#include <time.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;
    srand(time(NULL));

    //debug
    // AllocConsole();
    // freopen("CONOUT$", "w", stdout);

    createClass(&wc, hInstance, MAINWIN_CLASS, WndProc);
    if (!RegisterClassEx(&wc))
    {
        printError(ERR_WIN_REG);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        MAINWIN_CLASS,
        APP_NAME,
        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX),
        0, 0, DEF_SCREEN_WIDTH, DEF_SCREEN_HEIGHT,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        printError(ERR_WIN_CR);
        return 0;
    }

    ShowWindow(hwnd, SW_MAXIMIZE);
    UpdateWindow(hwnd);

    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return (int)Msg.wParam;
}