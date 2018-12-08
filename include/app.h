#ifndef APP_H

#define APP_H

#include "list.h"

typedef struct AppData AppData;
struct AppData
{
    char *version;
    char *pName;
    List *existingProfiles;
};

AppData *init();
AppData *setAppData(AppData *);
void mainLoop(AppData *);
void chooseProfile(AppData *);
void createProfile(AppData *);
void useProfile(AppData *);
void destroy(AppData *);

#endif