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
    char key[MAX_SETTING_SIZE];
    char value[MAX_SETTING_SIZE];
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

void addStringToCombo(HWND hwnd, int controlId, char *content)
{
    SendDlgItemMessage(hwnd, controlId, CB_ADDSTRING, (WPARAM)0, (LPARAM)content);
}

int findStringIndexInCombo(HWND hwnd, int controlId, char *content)
{
    return SendDlgItemMessage(hwnd, controlId, CB_FINDSTRING, (WPARAM)1, (LPARAM)content);
}

void setComboCursor(HWND hwnd, int controlId, int position)
{
    SendDlgItemMessage(hwnd, controlId, CB_SETCURSEL, (WPARAM)position, (LPARAM)0);
}

int getComboCursor(HWND hwnd, int controlId)
{
    return SendDlgItemMessage(hwnd, controlId, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
}

void sendWinText(HWND hwnd, int controlId, char *text)
{
    SendDlgItemMessage(hwnd, controlId, WM_SETTEXT, (WPARAM)0, (LPARAM)text);
}

void getStringFromCombo(HWND hwnd, int controlId, int index, char *destination)
{
    SendDlgItemMessage(hwnd, controlId, CB_GETLBTEXT, (WPARAM)index, (LPARAM)destination);
}