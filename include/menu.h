#ifndef MENU_H

#define MENU_H

//controls
#define MAIN_WIN_CTRL_NUM 12
#define EXIT_ID 1000
#define EXIT_MSG "Exit"
#define GTMENU_ID 1001
#define GTMENU_MSG "Go to Menu"
#define CRTABLE_ID 1
#define CRTABLE_MSG "Create SQL Model"
#define INSDATA_ID 2
#define INSDATA_MSG "Generate SQL Data"
#define PROFILESEL_ID 3
#define PROFILESEL_MSG "Choose Profile"
#define PROFILEHINT_ID 4
#define PROFILEHINT_MSG "Welcome"
#define VERSIONHINT_ID 5
#define VERSIONHINT_MSG "SQL-Generator"
#define PROFILECR_ID 6
#define PROFILECR_MSG ""
#define PROFILECRSUB_ID 7
#define PROFILECRSUB_MSG "Create new profile"
#define MENUHINT_ID 8
#define MENUHINT_MSG "Not the owner of the currently selected profile? Select another or create a new one!"
#define GTHINT_ID 9
#define GTHINT_MSG "What do you want to do today?"
#define LASTSCRMSG_ID 2000
#define LASTSCRMSG_MSG "Latest Exported Scripts"
#define LASTSCRLIST_ID 2001
#define LASTSCRLIST_MSG ""
#define LASTSCRSUB_ID 2002
#define LASTSCRSUB_MSG "Export Script"


#include <windows.h>
#include "./app.h"

void createMainMenu(HWND, HWND *);
void destroyMainMenu(HWND *);
void setVersion(HWND, AppData *);
void setExistingProfiles(HWND, AppData *);
void setMessage(char *, char *);
char *updateField(char *, HWND, int, int);
void createProfile(HWND hwnd, AppData *);
void saveProfile(HWND, AppData *, char *);
void appendNameToFile(char *);
void updateSettingFile(List *);
void updateHint(HWND, char *);
int loadProfile(AppData *);
void setDefaultProfile(List *, char *);
int checkProfileName(List *, char *, int);
void setLatestScriptsForProfile(HWND, int, char *);

#endif