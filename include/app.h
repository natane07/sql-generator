#ifndef APP_H

#define APP_H

typedef struct AppData AppData;
struct AppData
{
    char pName[20];
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