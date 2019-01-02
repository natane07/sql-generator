#ifndef FILE_H

#define FILE_H

#include "app.h"
#include "list.h"
#include <stdio.h>

//MAX SIZES
#define MAX_SETTING_LENGTH 60
#define MIN_SETTING_LENGTH 3
#define MAX_NAME_LENGTH 30
#define MIN_NAME_LENGTH 3
#define MAX_SENT_LENGTH 80
#define MAX_PATH_LENGTH 260

//SETTINGS
#define SETT_DEF_PRO "defaultProfile"
#define SETT_VER "version"

//DEFAULT VALUES
#define DEFAULT_PROFILE "default"
#define DEFAULT_VERSION "0.2"

//PATHS
#define LOCALSTORAGE "APPDATA"
#define MAIN_DIR "sql-generator"
#define CONFIG_DIR "sql-generator\\config"
#define CONFIG_FILE "sql-generator\\config\\config.ini"
#define PROFILES_FILE "sql-generator\\config\\profiles.ini"

void initFs(AppData *);
void initFolders(char *);
void initConfigFile(char *, List *);
void initProfilesFile(char *, AppData *);
int fileExists(char *, char *);
FILE *openFile(char *, char *, char *);
void applySettings(List *, AppData *);
void applySetting(char *, void *);
void setDefaultData(AppData *);
void getFileContent(List *, int, int, FILE *);
void printConfigFile(FILE *);

#endif