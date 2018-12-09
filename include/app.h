#ifndef APP_H

#define APP_H

#include "list.h"

//errors
#define NAME_TAKEN_ERR "This profile name is already in use!\n"
#define NAME_UNSAFE_ERR "Profile names should only use alphanumeric characters!\n"

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