#ifndef FILE_H

#define FILE_H

#include "app.h"
#include "list.h"
#include <stdio.h>

//MAX SIZES
#define MAX_SETTING_SIZE 60
#define MAX_NAME_LENGTH 30
#define MAXPATHLENGTH 260

//DEFAULT VALUES
#define DEFAULT_PROFILE "default"
#define DEFAULT_VERSION "0.2"

//PATHS
#define MAIN_DIR "sql-generator"
#define CONFIG_DIR "sql-generator\\config"
#define DATA_DIR "sql-generator\\data"
#define CONFIG_FILE "sql-generator\\config\\config.ini"
#define PROFILES_FILE "sql-generator\\config\\profiles.txt"

void initFs(AppData *);
void initFolders(char *);
void initConfigFile(char *, List *);
void initProfilesFile(char *, AppData *);
int fileExists(char *, char *);
FILE *openFile(char *, char *, char *);
void applySettings(List *, AppData *);
void applySetting(char *, void *);
int parseSetting(char *, char *, char *);
void setDefaultData(AppData *);

#endif