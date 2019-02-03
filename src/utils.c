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

void stringCopy(char *destination, char *source, int length)
{
    strncpy(destination, source, length - 1);
    remCrlf(destination);
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

int simpleCompare(char *lstr, char *comparator)
{
    return strcmp(comparator, lstr) == 0;
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

int findStringIndexInComboDir(HWND hwnd, char *content)
{
    return SendMessage(hwnd, CB_FINDSTRING, (WPARAM)1, (LPARAM)content);
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

void destroyComboContentDir(HWND combo)
{
    SendMessage(combo, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
}

void destroyComboContent(HWND hwnd, int controlId)
{
    SendDlgItemMessage(hwnd, controlId, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
}

void sendWinText(HWND hwnd, int controlId, char *text)
{
    SendDlgItemMessage(hwnd, controlId, WM_SETTEXT, (WPARAM)0, (LPARAM)text);
}

void sendWinTextDir(HWND hwnd, char *text)
{
    SendMessage(hwnd, WM_SETTEXT, (WPARAM)0, (LPARAM)text);
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

void getStringFromWinDir(HWND win, char *destination, int maxLength)
{
    SendMessage(win, WM_GETTEXT, (WPARAM)maxLength, (LPARAM)destination);
}

void getCurrentStringFromComboDir(HWND combo, char *destination)
{
    getStringFromComboDir(combo, getComboCursorDir(combo), destination);
}

void getCurrentStringFromCombo(HWND hwnd, int controlId, char *destination)
{
    getStringFromCombo(hwnd, controlId, getComboCursor(hwnd, controlId), destination);
}

void clearListBox(HWND hwnd, int controlId)
{
    SendDlgItemMessage(hwnd, controlId, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
}

int getRadioState(HWND hwnd)
{
    return SendMessage(hwnd, BM_GETCHECK, (WPARAM)0, (LPARAM)0);
}

void enableRadio(HWND hwnd)
{
    SendMessage(hwnd, BM_SETCHECK, (WPARAM)BST_CHECKED, (LPARAM)0);
}

void disableRadio(HWND hwnd)
{
    SendMessage(hwnd, BM_SETCHECK, (WPARAM)BST_UNCHECKED, (LPARAM)0);
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

void setRadioState(HWND hwnd, int checked)
{
    if (checked)
    {
        SendMessage(hwnd, BM_SETCHECK, (WPARAM)BST_CHECKED, (LPARAM)0);
    }
    else
    {
        SendMessage(hwnd, BM_SETCHECK, (WPARAM)BST_UNCHECKED, (LPARAM)0);
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

int getListCursor(HWND hwnd, int controlId)
{
    return SendDlgItemMessage(hwnd, controlId, LB_GETCARETINDEX, (WPARAM)0, (LPARAM)0);
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

void setOfn(HWND hwnd, OPENFILENAME *ofn, char *file, char *fileTitle)
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
    ofn->lpstrFileTitle = fileTitle;
    ofn->nMaxFileTitle = MAX_PATH_LENGTH;
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

void addFileToList(char *name, char *fileTitle)
{
    char file[MAX_PATH_LENGTH];
    sprintf(file, "%s\\%s\\%s\\%s", getenv(LOCALSTORAGE), DATA_DIR, name, name);
    FILE *fp = fopen(file, "a");
    if (fp != NULL)
    {
        fprintf(fp, "%s\n", fileTitle);
        fclose(fp);
    }
}
