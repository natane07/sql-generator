#ifndef FILE_H

#define FILE_H

#include "app.h"
#include "list.h"

#define MAX_SETTING_SIZE 60
#define MAXPATHLENGTH 260
#define MAIN_DIR "sql-generator"
#define CONFIG_DIR "sql-generator\\config"
#define DATA_DIR "sql-generator\\data"
#define CONFIG_FILE "sql-generator\\config\\config.ini"

void initFs(AppData *);
void initFolders(char *);
void initConfigFiles(char *, List *);
void applySettings(List *, AppData *);
void applySetting(char **, void *);
int parseSetting(char *, char *, char *);

#endif