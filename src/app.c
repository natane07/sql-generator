#include "..\include\app.h"
#include "..\include\menu.h"
#include "..\include\file.h"
#include "..\include\utils.h"
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
        exit(0);
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
    printf("%s created successfully!\n", buffer);
}

void useProfile(AppData *appData)
{
}

void destroy(AppData *appData)
{
    destroyList(appData->existingProfiles);
    free(appData->version);
    free(appData->pName);
    free(appData);
}