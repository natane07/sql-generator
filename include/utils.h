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
void stringCopy(char *, char *, int);
char *setString(char *, char *);
char *resetString(char *, char *);
int isStringSafe(char *);
int compareKey(char *, char *);
int simpleCompare(char *, char *);
void printError(const char *);
void printInfo(const char *);
int addStringToCombo(HWND, int, char *);
void addStringToComboDir(HWND, char *);
int addStringToList(HWND, int, char *);
int findStringIndexInCombo(HWND, int, char *);
int findStringIndexInComboDir(HWND, char *);
void setComboCursor(HWND, int, int);
void setComboCursorDir(HWND, int);
int getComboCursor(HWND, int);
int getComboCursorDir(HWND);
void sendWinText(HWND, int, char *);
void sendWinTextDir(HWND, char *);
void getStringFromCombo(HWND, int, int, char *);
void getStringFromComboDir(HWND, int, char *);
void getStringFromWin(HWND, int, char *, int);
void getStringFromWinDir(HWND, char *, int);
void getCurrentStringFromComboDir(HWND, char *);
void clearListBox(HWND, int);
int getRadioState(HWND);
void enableRadio(HWND);
void disableRadio(HWND);
void changeRadioState(HWND);
void setRadioState(HWND, int);
void enableEdit(HWND);
void disableEdit(HWND);
void createClass(WNDCLASSEX *, HINSTANCE, const char *, LRESULT(CALLBACK *)(HWND, UINT, WPARAM, LPARAM));
WinPosition getChildWindowPosition(HWND);
void moveWindowBy(HWND, int, int);
void destroyMenu(HWND *, int);

#endif