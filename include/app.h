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
void mainLoop(AppData *);
void chooseProfile(AppData *);
void createProfile(AppData *);
void useProfile(AppData *);
int getChoice();
void getString(char *, int);
void destroy(AppData *);

#endif