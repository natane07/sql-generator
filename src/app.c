#include "..\include\app.h"
#include "..\include\menu.h"
#include "..\include\file.h"
#include "..\include\utils.h"
#include "..\include\parser.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

AppData *init()
{
    AppData *appData = malloc(sizeof(AppData *));
    if (appData == NULL)
        exit(-1);
    appData = setAppData(appData);
    initFs(appData);
    return appData;
}

AppData *setAppData(AppData *appData)
{
    appData->version = NULL;
    appData->pName = NULL;
    appData->existingProfiles = NULL;
    return appData;
}

void mainLoop(AppData *appData)
{
    chooseProfile(appData);
}

void chooseProfile(AppData *appData)
{
    int choice = -1;
    choice = getChoice();
    while (choice != 0 && choice != 1 && choice != 2)
    {
        displayMenu(appData);
        choice = getChoice();
    }
    switch (choice)
    {
    case 0:
        createProfile(appData);
        break;
    case 1:
        useProfile(appData);
        break;
    case 2:
        break;
    }
}

void createProfile(AppData *appData)
{
    char *buffer = NULL;
    printf("Enter new profile name: ");
    buffer = getString(buffer, MAX_NAME_LENGTH);
    if (has(appData->existingProfiles, buffer))
    {
        printf(NAME_TAKEN_ERR);
        return createProfile(appData);
    }
    if (!isStringSafe(buffer))
    {
        printf(NAME_UNSAFE_ERR);
        return createProfile(appData);
    }
    if (strlen(buffer) < MIN_NAME_LENGTH)
    {
        printf(LENGTH_ERR);
        return createProfile(appData);
    }
    saveProfile(appData, buffer);
    free(buffer);
    return chooseProfile(appData);
}

void useProfile(AppData *appData)
{
    char *buffer = NULL;
    printf("Enter profile name: ");
    buffer = getString(buffer, MAX_NAME_LENGTH);
    if (has(appData->existingProfiles, buffer))
    {
        appData->pName = resetString(appData->pName, buffer);
        free(buffer);
        return loadProfile(appData);
    }
    printf(NAME_NOT_EXISTS_ERR);
    return useProfile(appData);
}

void saveProfile(AppData *appData, char *pName)
{
    int index;
    appData->pName = resetString(appData->pName, pName);
    push(appData->existingProfiles, pName);
    FILE *fp = openFile(getenv(LOCALSTORAGE), PROFILES_FILE, "a");
    if (fp != NULL)
    {
        fprintf(fp, "%s\n", pName);
        fclose(fp);
    }
    index = findIndex(appData->settings, compareKey, SETT_DEF_PRO);
    if (index != -1)
    {
        char buffer[MAX_SETTING_SIZE];
        printIniToString(buffer, SETT_DEF_PRO, pName);
        setElement(appData->settings, index, buffer);
        fp = openFile(getenv(LOCALSTORAGE), CONFIG_FILE, "w");
        if (fp != NULL)
        {
            writeListToFile(appData->settings, fp);
        }
    }
    printf("%s created successfully!\n", pName);
}

void loadProfile(AppData *appData)
{
    printf("%s loaded successfully!\n", appData->pName);
    initUserFile();
}

void destroy(AppData *appData)
{
    destroyList(appData->existingProfiles);
    destroyList(appData->settings);
    free(appData->version);
    free(appData->pName);
    free(appData);
}