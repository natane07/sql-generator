#ifndef APP_H

#define APP_H

#include "list.h"
#include "sql.h"
#include "crtable.h"
#include <windows.h>

//app
#define APP_NAME "SQL-Generator"
#define APP_ICON ".\\..\\ico\\sql.ico"
#define MAINWIN_CLASS "WinClass"
#define DEF_SCREEN_WIDTH 1920
#define DEF_SCREEN_HEIGHT 1080

//errors
#define ERR_WIN_REG "Window Registration Failed!"
#define ERR_WIN_CR "Window Creation Failed!"
#define ERR_NAME_NOT_EXISTS "That profile name doesn't exist!"
#define ERR_NAME_TAKEN "That profile name is already in use!"
#define ERR_NAME_UNSAFE "Profile names should only use alphanumeric characters!"
#define ERR_NAME_LENGTH "Profile name too short or too long!"

//success
#define OK_PROFILE_CR "created successfully!"
#define OK_PROFILE_LD "loaded successfully!"

//styles
#define STL_BUTTON (WS_VISIBLE | WS_CHILD | BS_MULTILINE)
#define STL_COMBO (WS_VISIBLE | WS_CHILD | WS_VSCROLL | CBS_DROPDOWNLIST)
#define STL_TEXT (WS_VISIBLE | WS_CHILD)
#define STL_TEXT_RIGHT (WS_VISIBLE | WS_CHILD | SS_RIGHT)
#define STL_TEXT_CENTER (WS_VISIBLE | WS_CHILD | SS_CENTER)
#define STL_EDIT (WS_VISIBLE | WS_CHILD | WS_BORDER)
#define STL_LIST (WS_VISIBLE | WS_CHILD)
#define STL_RADIO (WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON)

//check profile name function modes
#define CREATE 0
#define LOAD 1

typedef struct AppData AppData;
struct AppData
{
    char *version;
    char *pName;
    List *existingProfiles;
    List *settings;
    SqlModel model;
    SqlRules rules;
};

void initAppdata(AppData *);
void setAppData(AppData *);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void loadIcon(HWND, const char *);
void createWindowBar(HWND, HMENU *);
void destroy(AppData *);

#endif