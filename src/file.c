#include "..\include\file.h"
#include "..\include\list.h"
#include "..\include\app.h"
#include "..\include\utils.h"
#include "..\include\crtable.h"
#include "..\include\parser.h"
#include "..\include\sql.h"
#include "..\include\insdata.h"
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
    appData->rules.types = listInit();
    appData->rules.numReqTypes = listInit();
    appData->rules.aiTypes = listInit();
    sprintf(path, "%s", getenv(LOCALSTORAGE));
    setDefaultData(appData);
    initFolders(path);
    initConfigFile(path, appData->settings);
    initProfilesFile(path, appData);
    initTypesFile(path, appData);
    initDataFiles(path);
    getSubtypes(&appData->rules);
    applySettings(appData->settings, appData);
}

void initFolders(char *path)
{
    char dirLocation[MAX_PATH_LENGTH];
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
            getFileContent(settings, MAX_SETTING_LENGTH, MIN_SETTING_LENGTH, config, 0);
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
            getFileContent(appData->existingProfiles, MAX_NAME_LENGTH, MIN_NAME_LENGTH, profiles, 0);
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

void initTypesFile(char *path, AppData *appData)
{
    FILE *fp = NULL;
    char *file = TYPES_FILE;
    List *temp = listInit();
    int i;
    if (fileExists(path, file) == 1)
    {
        fp = openFile(path, file, "r");
        if (fp != NULL)
        {
            getFileContent(temp, MAX_TYPE_LENGTH, MIN_TYPE_LENGTH, fp, 0);
            forEach(temp, getTypes, appData->rules.types);
            forEach(temp, getNumReqTypes, appData->rules.numReqTypes);
            forEach(temp, getAiTypes, appData->rules.aiTypes);
            if (appData->rules.types->length > SQL_DEFAULT_TYPES_NUM)
                for (i = 0; i < SQL_DEFAULT_TYPES_NUM; i++)
                    shift(appData->rules.types);
        }
    }
    else
    {
        fp = openFile(path, file, "w");
        if (fp != NULL)
        {
            printTypesFile(fp);
        }
    }
    destroyList(temp);
}

void initDataFiles(char *path)
{
    FILE *fp = NULL;
    if (!fileExists(path, CITY_FILE))
    {
        fp = openFile(path, CITY_FILE, "w");
        fprintf(fp, "Paris\nMarseille\nLyon\nToulouse\nNice\nNantes\nStrasbourg\nMontpellier\nBordeaux\nLille\n");
        fclose(fp);
    }
    if (!fileExists(path, NAME_FILE))
    {
        fp = openFile(path, NAME_FILE, "w");
        fprintf(fp, "natane\nquentin\nbaptiste\njeremy\nruben\nsacha\ndan\nmarvin\ndavid\nsteven\n");
        fclose(fp);
    }
    if (!fileExists(path, MAIL_FILE))
    {
        fp = openFile(path, MAIL_FILE, "w");
        fprintf(fp, "gmail\nhotmail\nmyges\nyahoo\nsfr\norange\nfree\nesgi\nvirgine\novh\n");
        fclose(fp);
    }
}

void getTypes(char *content, void *data)
{
    List *types = data;
    char key[MAX_TYPE_LENGTH];
    char value[MAX_TYPE_LENGTH];
    int ok = parseIni(content, key, value);
    if (ok)
    {
        push(types, key);
    }
}

void getNumReqTypes(char *content, void *data)
{
    List *types = data;
    char key[MAX_TYPE_LENGTH];
    char value[MAX_TYPE_LENGTH];
    int ok = parseIni(content, key, value);
    if (ok && strcmp(value, REQ_NUM) == 0)
    {
        push(types, key);
    }
}

void getAiTypes(char *content, void *data)
{
    List *types = data;
    char key[MAX_TYPE_LENGTH];
    char value[MAX_TYPE_LENGTH];
    int ok = parseIni(content, key, value);
    if (ok && strcmp(value, AI_NUM) == 0)
    {
        push(types, key);
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
        else if (strcmp(key, SETT_MAX_COL) == 0)
        {
            appData->rules.maxCol = atoi(value);
        }
        else if (strcmp(key, SETT_MAX_FK) == 0)
        {
            appData->rules.maxFk = atoi(value);
        }
        else if (strcmp(key, SETT_MAX_TAB) == 0)
        {
            appData->rules.maxTab = atoi(value);
        }
        else if (strcmp(key, SETT_INS_NUM) == 0)
        {
            appData->rules.insNum = atoi(value);
        }
    }
}

void setDefaultData(AppData *appData)
{
    char version[] = DEFAULT_VERSION;
    char profile[] = DEFAULT_PROFILE;
    appData->version = setString(appData->version, version);
    appData->pName = setString(appData->pName, profile);
    appData->rules.maxCol = atoi(DEFAULT_MAXCOL);
    appData->rules.maxFk = atoi(DEFAULT_MAXFK);
    appData->rules.maxTab = atoi(DEFAULT_MAXTAB);
    appData->rules.insNum = atoi(DEFAULT_INSNUM);
    push(appData->existingProfiles, DEFAULT_PROFILE);
    setDefaultTypes(appData->rules.types);
}

void getFileContent(List *storage, int bufferSize, int minLength, FILE *fp, int check)
{
    char *buffer = malloc(bufferSize * sizeof(char));
    if (buffer == NULL)
        exit(-1);
    while (fgets(buffer, bufferSize, fp) != NULL)
    {
        remCrlf(buffer);
        if (strlen(buffer) > minLength)
            push(storage, buffer);
        if (check && !isStringSafe(buffer))
            pop(storage);
    }
    fclose(fp);
    free(buffer);
}

void printTypesFile(FILE *fp)
{
    printIniToFile(fp, SQL_TYPE_1, SQL_TYPE_1_REQ_NUM);
    printIniToFile(fp, SQL_TYPE_2, SQL_TYPE_2_REQ_NUM);
    printIniToFile(fp, SQL_TYPE_3, SQL_TYPE_3_REQ_NUM);
    printIniToFile(fp, SQL_TYPE_4, SQL_TYPE_4_REQ_NUM);
    printIniToFile(fp, SQL_TYPE_5, SQL_TYPE_5_REQ_NUM);
    printIniToFile(fp, SQL_TYPE_6, SQL_TYPE_6_REQ_NUM);
    fclose(fp);
}

void setDefaultTypes(List *types)
{
    push(types, SQL_TYPE_1);
    push(types, SQL_TYPE_2);
    push(types, SQL_TYPE_3);
    push(types, SQL_TYPE_4);
    push(types, SQL_TYPE_5);
    push(types, SQL_TYPE_6);
}

void printConfigFile(FILE *fp)
{
    printIniToFile(fp, SETT_VER, DEFAULT_VERSION);
    printIniToFile(fp, SETT_DEF_PRO, DEFAULT_PROFILE);
    printIniToFile(fp, SETT_MAX_COL, DEFAULT_MAXCOL);
    printIniToFile(fp, SETT_MAX_FK, DEFAULT_MAXFK);
    printIniToFile(fp, SETT_MAX_TAB, DEFAULT_MAXTAB);
    printIniToFile(fp, SETT_INS_NUM, DEFAULT_INSNUM);
    fclose(fp);
}

void initUserDir(char *name)
{
    char location[MAX_PATH_LENGTH];
    sprintf(location, "%s\\%s\\%s", getenv(LOCALSTORAGE), DATA_DIR, name);
    CreateDirectory(location, NULL);
    sprintf(location, "%s\\%s\\%s", DATA_DIR, name, name);
    if (!fileExists(getenv(LOCALSTORAGE), location))
    {
        FILE *fp = openFile(getenv(LOCALSTORAGE), location, "w");
        if (fp != NULL)
            fclose(fp);
    }
}