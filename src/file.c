#include "..\include\file.h"
#include "..\include\list.h"
#include "..\include\app.h"
#include "..\include\utils.h"
#include "..\include\parser.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

void initFs(AppData *appData)
{
    char path[MAX_PATH_LENGTH];
    appData->settings = listInit();
    appData->existingProfiles = listInit();
    sprintf(path, "%s", getenv(LOCALSTORAGE));
    setDefaultData(appData);
    initFolders(path);
    initConfigFile(path, appData->settings);
    initProfilesFile(path, appData);
    applySettings(appData->settings, appData);
}

void initFolders(char *path)
{
    char dirLocation[MAX_PATH_LENGTH];
    sprintf(dirLocation, "%s\\%s", path, MAIN_DIR);
    CreateDirectory(dirLocation, NULL);
    sprintf(dirLocation, "%s\\%s", path, CONFIG_DIR);
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
            getFileContent(settings, MAX_SETTING_LENGTH, MIN_SETTING_LENGTH, config);
        }
    }
    else
    {
        config = openFile(path, CONFIG_FILE, "w");
        if (config != NULL)
        {
            printConfigFile(config);
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
            getFileContent(appData->existingProfiles, MAX_NAME_LENGTH, MIN_NAME_LENGTH, profiles);
            if (appData->existingProfiles->length > 1)
            {
                shift(appData->existingProfiles);
            }
        }
    }
    else
    {
        profiles = openFile(path, PROFILES_FILE, "w");
        if (profiles != NULL)
        {
            fprintf(profiles, "%s\n", DEFAULT_PROFILE);
            fclose(profiles);
        }
    }
}

int fileExists(char *basePath, char *filePath)
{
    char fileLocation[MAX_PATH_LENGTH];
    sprintf(fileLocation, "%s\\%s", basePath, filePath);
    if (_access(fileLocation, 0) != -1)
        return 1;
    return 0;
}

FILE *openFile(char *basePath, char *filePath, char *mode)
{
    char fileLocation[MAX_PATH_LENGTH];
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
    char key[MAX_SETTING_LENGTH];
    char value[MAX_SETTING_LENGTH];
    int ok;
    ok = parseIni(content, key, value);
    if (ok)
    {
        if (strcmp(key, SETT_VER) == 0)
        {
            appData->version = resetString(appData->version, value);
        }
        else if (strcmp(key, SETT_DEF_PRO) == 0)
        {
            appData->pName = resetString(appData->pName, value);
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

void getFileContent(List *storage, int bufferSize, int minLength, FILE *fp)
{
    char *buffer = malloc(bufferSize * sizeof(char));
    if (buffer == NULL)
        exit(-1);
    while (fgets(buffer, bufferSize, fp) != NULL)
    {
        remCrlf(buffer);
        if (strlen(buffer) > minLength)
            push(storage, buffer);
    }
    fclose(fp);
    free(buffer);
}

void printConfigFile(FILE *fp)
{
    printIniToFile(fp, SETT_VER, DEFAULT_VERSION);
    printIniToFile(fp, SETT_DEF_PRO, DEFAULT_PROFILE);
    fclose(fp);
}