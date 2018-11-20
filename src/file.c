#include "..\include\file.h"
#include "..\include\list.h"
#include "..\include\app.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void initFs(AppData *appData)
{
    char path[MAXPATHLENGTH];
    List *settings = listInit();
    sprintf(path, "%s", getenv("APPDATA"));
    initFolders(path);
    initConfigFiles(path, settings);
    applySettings(settings, appData);
}

void initFolders(char *path)
{
    char dirLocation[MAXPATHLENGTH];
    sprintf(dirLocation, "%s\\%s", path, MAIN_DIR);
    CreateDirectory(dirLocation, NULL);
    sprintf(dirLocation, "%s\\%s", path, CONFIG_DIR);
    CreateDirectory(dirLocation, NULL);
    sprintf(dirLocation, "%s\\%s", path, DATA_DIR);
    CreateDirectory(dirLocation, NULL);
}

void initConfigFiles(char *path, List *settings)
{
    char fileLocation[MAXPATHLENGTH];
    FILE *config = NULL;
    sprintf(fileLocation, "%s\\%s", path, CONFIG_FILE);
    if (access(fileLocation, F_OK) != -1)
    {
        config = fopen(fileLocation, "r");
        if (config != NULL)
        {
            char buffer[MAX_SETTING_SIZE];
            while (fgets(buffer, MAX_SETTING_SIZE, config) != NULL)
            {
                push(settings, buffer);
            }
            fclose(config);
        }
    }
    else
    {
        config = fopen(fileLocation, "w");
        if (config != NULL)
        {
            fprintf(config, "%s", "version=0.1");
        }
    }
}

void applySettings(List *settings, AppData *appData)
{
    forEach(settings, applySetting, appData);
}

void applySetting(char **content, void *data)
{
    AppData *appData = data;
    char key[MAX_SETTING_SIZE];
    char value[MAX_SETTING_SIZE];
    int ok;
    ok = parseSetting(*content, key, value);
    if (ok == 0)
    {
        if (strcmp(key, "version") == 0)
        {
            strcpy(appData->version, value);
        }
        else if (strcmp(key, "something") == 0)
        {
        }
    }
}

int parseSetting(char *content, char *key, char *value)
{
    char *pch;
    pch = strchr(content, '=');
    if (pch == NULL)
    {
        return -1;
    }
    strcpy(value, pch + 1);
    strncpy(key, content, pch - content);
    key[pch - content] = '\0';
    return 0;
}