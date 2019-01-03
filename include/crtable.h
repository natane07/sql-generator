#ifndef CRTABLE_H

#define CRTABLE_H

#include <windows.h>

//view
#define CRTABLEWIN_CLASS "CrTableClass"
#define CRTABLE_NAME "Create Table"

//controls
#define LITABHINT_ID 9
#define LITABHINT_MSG "Table List"
#define TABEDHINT_ID 10
#define TABEDHINT_MSG "Table Editor"
#define TITLEHINT_ID 11
#define TITLEHINT_MSG "Enter Table Name:"
#define TITLEDIT_ID 12
#define TITLEDIT_MSG ""

void createCrTableMenu(HWND, HWND *);

#endif