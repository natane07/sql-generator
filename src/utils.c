#include "..\include\utils.h"
#include "..\include\parser.h"
#include "..\include\file.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void remCrlf(char *str)
{
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
}

void initMemory(char *str, int length)
{
    memset(str, '\0', length);
}

char *setString(char *destination, char *source)
{
    destination = malloc((strlen(source) + 1) * sizeof(char));
    if (destination == NULL)
        exit(-1);
    strcpy(destination, source);
    return destination;
}

char *resetString(char *destination, char *source)
{
    free(destination);
    return setString(destination, source);
}

int isStringSafe(char *str)
{
    char allowedChars[] = ALPHA_NUM;
    char *match;
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        match = strpbrk(str + i, allowedChars);
        if (match != str + i)
        {
            return 0;
        }
    }
    return 1;
}

int compareKey(char *ini, char *comparator)
{
    int ok;
    char key[MAX_SETTING_LENGTH];
    char value[MAX_SETTING_LENGTH];
    ok = parseIni(ini, key, value);
    if (ok)
    {
        return strcmp(comparator, key) == 0;
    }
    return 0;
}

void printError(const char *error)
{
    MessageBox(NULL, error, "Error!", MB_ICONERROR | MB_OK);
}

void printInfo(const char *info)
{
    MessageBox(NULL, info, "Infomation", MB_ICONINFORMATION | MB_OK);
}

int addStringToCombo(HWND hwnd, int controlId, char *content)
{
    return SendDlgItemMessage(hwnd, controlId, CB_ADDSTRING, (WPARAM)0, (LPARAM)content);
}

void addStringToComboDir(HWND combo, char *content)
{
    SendMessage(combo, CB_ADDSTRING, (WPARAM)0, (LPARAM)content);
}

int addStringToList(HWND hwnd, int controlId, char *content)
{
    return SendDlgItemMessage(hwnd, controlId, LB_ADDSTRING, (WPARAM)0, (LPARAM)content);
}

int findStringIndexInCombo(HWND hwnd, int controlId, char *content)
{
    return SendDlgItemMessage(hwnd, controlId, CB_FINDSTRING, (WPARAM)1, (LPARAM)content);
}

void setComboCursor(HWND hwnd, int controlId, int position)
{
    SendDlgItemMessage(hwnd, controlId, CB_SETCURSEL, (WPARAM)position, (LPARAM)0);
}

void setComboCursorDir(HWND combo, int position)
{
    SendMessage(combo, CB_SETCURSEL, (WPARAM)position, (LPARAM)0);
}

int getComboCursor(HWND hwnd, int controlId)
{
    return SendDlgItemMessage(hwnd, controlId, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
}

int getComboCursorDir(HWND combo)
{
    return SendMessage(combo, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
}

void sendWinText(HWND hwnd, int controlId, char *text)
{
    SendDlgItemMessage(hwnd, controlId, WM_SETTEXT, (WPARAM)0, (LPARAM)text);
}

void getStringFromCombo(HWND hwnd, int controlId, int index, char *destination)
{
    SendDlgItemMessage(hwnd, controlId, CB_GETLBTEXT, (WPARAM)index, (LPARAM)destination);
}

void getStringFromComboDir(HWND combo, int index, char *destination)
{
    SendMessage(combo, CB_GETLBTEXT, (WPARAM)index, (LPARAM)destination);
}

void getStringFromWin(HWND hwnd, int controlId, char *destination, int maxLength)
{
    SendDlgItemMessage(hwnd, controlId, WM_GETTEXT, (WPARAM)maxLength, (LPARAM)destination);
}

void getCurrentStringFromComboDir(HWND combo, char *destination)
{
    getStringFromComboDir(combo, getComboCursorDir(combo), destination);
}

void changeRadioState(HWND hwnd)
{
    int checked = SendMessage(hwnd, BM_GETCHECK, (WPARAM)0, (LPARAM)0);
    if (checked)
    {
        SendMessage(hwnd, BM_SETCHECK, (WPARAM)BST_UNCHECKED, (LPARAM)0);
    }
    else
    {
        SendMessage(hwnd, BM_SETCHECK, (WPARAM)BST_CHECKED, (LPARAM)0);
    }
}

void enableEdit(HWND edit)
{
    SendMessage(edit, EM_SETREADONLY, (WPARAM)FALSE, (LPARAM)0);
}

void disableEdit(HWND edit)
{
    SendMessage(edit, EM_SETREADONLY, (WPARAM)TRUE, (LPARAM)0);
}

void createClass(WNDCLASSEX *wc, HINSTANCE hInstance, const char *className, LRESULT(CALLBACK *wndProc)(HWND, UINT, WPARAM, LPARAM))
{
    wc->cbSize = sizeof(WNDCLASSEX);
    wc->style = 0;
    wc->lpfnWndProc = wndProc;
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

WinPosition getChildWindowPosition(HWND hwnd)
{
    RECT winCoo;
    WinPosition winPos;
    GetWindowRect(hwnd, &winCoo);
    MapWindowPoints(HWND_DESKTOP, GetParent(hwnd), (LPPOINT)&winCoo, 2);
    winPos.x = winCoo.left;
    winPos.y = winCoo.top;
    winPos.width = winCoo.right - winCoo.left;
    winPos.height = winCoo.bottom - winCoo.top;
    return winPos;
}

void moveWindowBy(HWND hwnd, int x, int y)
{
    WinPosition winPos = getChildWindowPosition(hwnd);
    MoveWindow(hwnd, winPos.x + x, winPos.y + y, winPos.width, winPos.height, TRUE);
}

void destroyMenu(HWND *controls, int size)
{
    int i;
    for (i = 0; i < size; i++)
        DestroyWindow(controls[i]);
}
