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
int findStringIndexInCombo(HWND, int, char *);
void setComboCursor(HWND, int, int);
int getComboCursor(HWND, int);
void sendWinText(HWND, int, char *);
void getStringFromCombo(HWND, int, int, char *);
void getStringFromWin(HWND, int, char *, int);
void createClass(WNDCLASSEX *, HINSTANCE, const char *, LRESULT(CALLBACK *)(HWND, UINT, WPARAM, LPARAM));
WinPosition getChildWindowPosition(HWND hwnd);
void moveWindowBy(HWND hwnd, int x, int y);

#endif