#include ".\..\include\insdata.h"
#include ".\..\include\utils.h"
#include <windows.h>

void createInsDataMenu(HWND hwnd, HWND *controls)
{
}

void destroyInsDataMenu(HWND *controls)
{
    destroyMenu(controls, INSDATA_WIN_CTRL_NUM);
}