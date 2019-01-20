#ifndef UTILS_H

#define UTILS_H

#define ALPHA_NUM "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

#include <windows.h>

typedef struct WinPosition WinPosition;
struct WinPosition {
    long x;
    long y;
    long width;
    long height;
};

void remCrlf(char *);
void initMemory(char *, int);
char *setString(char *, char *);
char *resetString(char *, char *);
int isStringSafe(char *);
int compareKey(char *, char *);
void printError(const char *);
void printInfo(const char *);
int addStringToCombo(HWND, int, char *);
void addStringToComboDir(HWND, char *);
int addStringToList(HWND, int, char *);
int findStringIndexInCombo(HWND, int, char *);
void setComboCursor(HWND, int, int);
void setComboCursorDir(HWND, int);
int getComboCursor(HWND, int);
int getComboCursorDir(HWND);
void sendWinText(HWND, int, char *);
void getStringFromCombo(HWND, int, int, char *);
void getStringFromComboDir(HWND, int, char *);
void getStringFromWin(HWND, int, char *, int);
void getCurrentStringFromComboDir(HWND, char *);
void changeRadioState(HWND);
void enableEdit(HWND);
void disableEdit(HWND);
void createClass(WNDCLASSEX *, HINSTANCE, const char *, LRESULT(CALLBACK *)(HWND, UINT, WPARAM, LPARAM));
WinPosition getChildWindowPosition(HWND);
void moveWindowBy(HWND, int, int);
void destroyMenu(HWND *, int);

#endif