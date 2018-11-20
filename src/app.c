#include "..\include\app.h"
#include "..\include\menu.h"
#include "..\include\file.h"
#include <stdlib.h>
#include <stddef.H>
#include <stdio.h>
#include <string.h>

AppData *init()
{
    AppData *appData = malloc(sizeof(AppData *));
    if (appData == NULL)
        exit(-1);
    initFs(appData);
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
        printf("%d", choice);
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
    printf("Enter new profile name: ");
    getString(appData->pName, 20);
    printf("Profile created successfully!\n");
}

void useProfile(AppData *appData)
{
}

int getChoice()
{
    int choice;
    printf("Enter choice: ");
    fflush(stdin);
    choice = fgetc(stdin) - 48;
    return choice;
}

void getString(char *string, int maxSize)
{
    fflush(stdin);
    fgets(string, maxSize, stdin);
    if (string[strlen(string) - 1] == '\n')
        string[strlen(string) - 1] = '\0';
}

void destroy(AppData *appData)
{
    free(appData);
}