#include "..\include\file.h"
#include "..\include\list.h"
#include "..\include\app.h"
#include "..\include\utils.h"
#include "..\include\parser.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void initFs(AppData *appData)
{
    char path[MAXPATHLENGTH];
    List *settings = listInit();
    appData->existingProfiles = listInit();
    sprintf(path, "%s", getenv("APPDATA"));
    setDefaultData(appData);
    initFolders(path);
    initConfigFile(path, settings);
    initProfilesFile(path, appData);
    applySettings(settings, appData);
    destroyList(settings);
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

void initConfigFile(char *path, List *settings)
{
    FILE *config = NULL;
    if (fileExists(path, CONFIG_FILE) == 1)
    {
        config = openFile(path, CONFIG_FILE, "r");
        if (config != NULL)
        {
            getFileContent(settings, MAX_SETTING_SIZE, config);
        }
    }
    else
    {
        config = openFile(path, CONFIG_FILE, "w");
        if (config != NULL)
        {
            fprintf(config, "version=%s\n", DEFAULT_VERSION);
            fprintf(config, "defaultProfile=%s\n", DEFAULT_PROFILE);
            fclose(config);
        }
    }
}

void initProfilesFile(char *path, AppData *appData)
{
    FILE *profiles = NULL;
    if (fileExists(path, PROFILES_FILE) == 1)
    {
        profiles = openFile(path, PROFILES_FILE, "r");
        if (profiles != NULL)
        {
            getFileContent(appData->existingProfiles, MAX_NAME_LENGTH, profiles);
        }
    }
    else
    {
        profiles = openFile(path, PROFILES_FILE, "w");
        if (profiles != NULL)
        {
            fprintf(profiles, "%s=1\n", DEFAULT_PROFILE);
            fclose(profiles);
        }
    }
}

int fileExists(char *basePath, char *filePath)
{
    char fileLocation[MAXPATHLENGTH];
    sprintf(fileLocation, "%s\\%s", basePath, filePath);
    if (access(fileLocation, F_OK) != -1)
        return 1;
    return 0;
}

FILE *openFile(char *basePath, char *filePath, char *mode)
{
    char fileLocation[MAXPATHLENGTH];
    FILE *file = NULL;
    sprintf(fileLocation, "%s\\%s", basePath, filePath);
    file = fopen(fileLocation, mode);
    return file;
}

void applySettings(List *settings, AppData *appData)
{
    forEach(settings, applySetting, appData);
}

void applySetting(char *content, void *data)
{
    AppData *appData = data;
    char key[MAX_SETTING_SIZE];
    char value[MAX_SETTING_SIZE];
    int ok;
    ok = parseIni(content, key, value);
    if (ok)
    {
        if (strcmp(key, "version") == 0)
        {
            appData->version = resetString(appData->version, value);
        }
        else if (strcmp(key, "something") == 0)
        {
        }
    }
}

void setDefaultData(AppData *appData)
{
    char version[] = DEFAULT_VERSION;
    char profile[] = DEFAULT_PROFILE;
    appData->version = setString(appData->version, version);
    appData->pName = setString(appData->pName, profile);
    push(appData->existingProfiles, DEFAULT_PROFILE);
}

void getFileContent(List *storage, int bufferSize, FILE *fp)
{
    char *buffer = malloc(bufferSize * sizeof(char));
    while (fgets(buffer, bufferSize, fp) != NULL)
    {
        remCrlf(buffer);
        push(storage, buffer);
    }
    fclose(fp);
    free(buffer);
}