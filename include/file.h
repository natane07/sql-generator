#ifndef FILE_H

#define FILE_H

#include "app.h"
#include "list.h"
#include <stdio.h>

//MAX SIZES
#define MAX_SETTING_LENGTH 60
#define MIN_SETTING_LENGTH 2
#define MAX_NAME_LENGTH 30
#define MIN_NAME_LENGTH 2
#define MAX_TYPE_LENGTH 30
#define MIN_TYPE_LENGTH 2
#define MAX_SENT_LENGTH 80
#define MAX_PATH_LENGTH MAX_PATH
#define MAX_DIGIT_LENGTH 5
#define MAX_FILE_LENGTH 80
#define MIN_FILE_LENGTH 2

//SETTINGS
#define SETT_DEF_PRO "defaultProfile"
#define SETT_VER "version"
#define SETT_MAX_COL "maxColumnNum"
#define SETT_MAX_FK "maxFkNum"
#define SETT_MAX_TAB "maxTabNum"
#define SETT_INS_NUM "insertNumber"

//DEFAULT VALUES
#define DEFAULT_PROFILE "default"
#define DEFAULT_VERSION "1.0"
#define DEFAULT_MAXCOL "15"
#define DEFAULT_MAXFK "4"
#define DEFAULT_INSNUM "8"
#define DEFAULT_MAXTAB "15"

//PATHS
#define LOCALSTORAGE "APPDATA"
#define MAIN_DIR "sql-generator"
#define CONFIG_DIR "sql-generator\\config"
#define DATA_DIR "sql-generator\\data"
#define CONFIG_FILE "sql-generator\\config\\config.ini"
#define PROFILES_FILE "sql-generator\\config\\profiles.ini"
#define TYPES_FILE "sql-generator\\config\\types.ini"
#define CITY_FILE "sql-generator\\config\\cities.txt"
#define NAME_FILE "sql-generator\\config\\names.txt"
#define MAIL_FILE "sql-generator\\config\\mails.txt"

void initFs(AppData *);
void initFolders(char *);
void initConfigFile(char *, List *);
void initProfilesFile(char *, AppData *);
void initTypesFile(char *, AppData *);
void initDataFiles(char *);
void getTypes(char *, void *);
void getNumReqTypes(char *, void *);
void getAiTypes(char *, void *);
int fileExists(char *, char *);
FILE *openFile(char *, char *, char *);
void applySettings(List *, AppData *);
void applySetting(char *, void *);
void setDefaultData(AppData *);
void getFileContent(List *, int, int, FILE *, int);
void printTypesFile(FILE *);
void setDefaultTypes(List *);
void printConfigFile(FILE *);
void initUserDir(char *);

#endif