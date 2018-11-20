#include "..\include\menu.h"
#include "..\include\app.h"
#include <stdio.h>
#include <stdlib.h>

void displayMenu(AppData *appData)
{
    system("cls");
    printf("SQL Generator [Version %s]\n(c) 2018 ESGI. All Rights Reserved.\n\n", appData->version);
    printf("Welcome !\nType 0 to create a new profile, 1 to use an existing one or 2 to exit!\n");
}