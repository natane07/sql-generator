#include "..\include\file.h"
#include "..\include\list.h"
#include "..\include\app.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void initFs(AppData *appData)
{
    char path[MAXPATHLENGTH];
    List *settings = listInit();
    sprintf(path, "%s", getenv("APPDATA"));
    initFolders(path);
    initConfigFiles(path, settings);
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