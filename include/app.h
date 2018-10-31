#ifndef APP_H

#define APP_H

typedef struct AppData AppData;
struct AppData
{
    char pName[60];
};

AppData *init();
void mainLoop(AppData *);
void destroy(AppData *);

#endif