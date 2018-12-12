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
    saveProfile(appData, buffer);
}

void useProfile(AppData *appData)
{
}

void saveProfile(AppData *appData, char *pName)
{
    int index;
    push(appData->existingProfiles, pName);
    FILE *fp = openFile(getenv(LOCALSTORAGE), PROFILES_FILE, "a");
    if (fp != NULL)
    {
        printIniToFile(fp, pName, "1");
        fclose(fp);
    }
    index = findIndex(appData->settings, compareKey, SETT_DEF_PRO);
    if (index != -1)
    {
        char buffer[MAX_SETTING_SIZE];
        printIniToString(buffer, SETT_DEF_PRO, pName);
        setElement(appData->settings, index, buffer);
    }
    printList(appData->settings);
    printf("%s created successfully!\n", pName);
}

void destroy(AppData *appData)
{
    destroyList(appData->existingProfiles);
    destroyList(appData->settings);
    free(appData->version);
    free(appData->pName);
    free(appData);
}