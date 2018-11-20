#include "include\menu.h"
#include "include\app.h"

int main(int argc, char **argv)
{
    AppData *appData = init();
    displayMenu(appData);
    mainLoop(appData);
    destroy(appData);
}