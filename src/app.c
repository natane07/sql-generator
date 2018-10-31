#include "..\include\app.h"
#include <stdlib.h>
#include <stddef.H>
#include <stdio.h>

AppData *init()
{
    AppData *appData = malloc(sizeof(AppData *));
    if (appData == NULL)
        exit(-1);
    return appData;
}

void mainLoop(AppData *appData)
{
    //main code here ...
    fgets(appData->pName, 60, stdin);
    printf("%s", appData->pName);
}

void destroy(AppData *appData)
{
    free(appData);
}