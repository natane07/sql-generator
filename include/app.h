#ifndef APP_H

#define APP_H

#include "list.h"
#include <windows.h>

#define APP_NAME "SQL-Generator"
#define APP_ICON ".\\..\\ico\\sql.ico"
#define MAINWIN_CLASS "WinClass"

//errors
#define ERR_WIN_REG "Window Registration Failed!"
#define ERR_WIN_CR "Window Creation Failed!"
#define ERR_NAME_NOT_EXISTS "That profile name doesn't exist!"
#define ERR_NAME_TAKEN "That profile name is already in use!"
#define ERR_NAME_UNSAFE "Profile names should only use alphanumeric characters!"
#define ERR_NAME_LENGTH "Profile name too short or too long!"

//controls
#define EXIT_ID 0
#define EXIT_MSG "Exit"
#define CRTABLE_ID 1
#define CRTABLE_MSG "Create SQL Model"
#define INSDATA_ID 2
#define INSDATA_MSG "Generate SQL Data"
#define PROFILESEL_ID 3
#define PROFILESEL_MSG "Choose Profile"
#define PROFILEHINT_ID 4
#define PROFILEHINT_MSG "Welcome"

typedef struct AppData AppData;
struct AppData
{
    char *version;
    char *pName;
    List *existingProfiles;
    List *settings;
};

void initAppdata(AppData *);
void setAppData(AppData *);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void createClass(WNDCLASSEX *, HINSTANCE, const char *);
void loadIcon(HWND, const char *);
void createWindowBar(HWND);
void setExistingProfiles(HWND, AppData *);
void setMessage(char *, char *);
char *updateField(char *, HWND, int, int);
void createProfile(AppData *);
void useProfile(AppData *);
void saveProfile(AppData *, char *);
void loadProfile(AppData *);
void destroy(AppData *);

#endif