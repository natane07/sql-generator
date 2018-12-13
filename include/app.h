#ifndef APP_H

#define APP_H

#include "list.h"

//errors
#define NAME_NOT_EXISTS_ERR "That profile name doesn't exist!\n"
#define NAME_TAKEN_ERR "That profile name is already in use!\n"
#define NAME_UNSAFE_ERR "Profile names should only use alphanumeric characters!\n"
#define LENGTH_ERR "Profile name too short or too long!\n"

typedef struct AppData AppData;
struct AppData
{
    char *version;
    char *pName;
    List *existingProfiles;
    List *settings;
};

AppData *init();
AppData *setAppData(AppData *);
void mainLoop(AppData *);
void chooseProfile(AppData *);
void createProfile(AppData *);
void useProfile(AppData *);
void saveProfile(AppData *, char *);
void loadProfile(AppData *);
void destroy(AppData *);

#endif