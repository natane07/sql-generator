#include <windows.h>
#include ".\..\include\menu.h"
#include ".\..\include\styles.h"
#include ".\..\include\file.h"
#include ".\..\include\utils.h"
#include ".\..\include\parser.h"

void createMainMenu(HWND hwnd, HWND *mainMenuControls)
{
    mainMenuControls[0] = CreateWindow("COMBOBOX", PROFILESEL_MSG, STL_COMBO, 350, 150, 300, 100, hwnd, (HMENU)PROFILESEL_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[1] = CreateWindow("STATIC", PROFILEHINT_MSG, STL_TEXT_CENTER, 525, 10, 400, 24, hwnd, (HMENU)PROFILEHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[2] = CreateWindow("BUTTON", CRTABLE_MSG, STL_BUTTON, 550, 350, 150, 24, hwnd, (HMENU)CRTABLE_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[3] = CreateWindow("BUTTON", INSDATA_MSG, STL_BUTTON, 750, 350, 150, 24, hwnd, (HMENU)INSDATA_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[4] = CreateWindow("STATIC", VERSIONHINT_MSG, STL_TEXT_RIGHT, 1220, 10, 300, 24, hwnd, (HMENU)VERSIONHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[5] = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", PROFILECR_MSG, STL_EDIT, 800, 150, 300, 24, hwnd, (HMENU)PROFILECR_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[6] = CreateWindow("BUTTON", PROFILECRSUB_MSG, STL_BUTTON, 1110, 150, 150, 24, hwnd, (HMENU)PROFILECRSUB_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[7] = CreateWindow("STATIC", MENUHINT_MSG, STL_TEXT_CENTER, 425, 75, 600, 24, hwnd, (HMENU)MENUHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[8] = CreateWindow("STATIC", GTHINT_MSG, STL_TEXT_CENTER, 575, 300, 300, 24, hwnd, (HMENU)GTHINT_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[9] = CreateWindow("STATIC", LASTSCRMSG_MSG, STL_TEXT_CENTER, 575, 500, 300, 24, hwnd, (HMENU)LASTSCRMSG_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[10] = CreateWindow("COMBOBOX", LASTSCRLIST_MSG, STL_COMBO, 575, 550, 300, 100, hwnd, (HMENU)LASTSCRLIST_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
    mainMenuControls[11] = CreateWindow("BUTTON", LASTSCRSUB_MSG, STL_BUTTON, 650, 650, 150, 24, hwnd, (HMENU)LASTSCRSUB_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
}

void destroyMainMenu(HWND *mainMenuControls)
{
    destroyMenu(mainMenuControls, MAIN_WIN_CTRL_NUM);
}

void setVersion(HWND hwnd, AppData *appData)
{
    char buffer[MAX_SENT_LENGTH];
    sprintf(buffer, "%s [%s]", VERSIONHINT_MSG, appData->version);
    sendWinText(hwnd, VERSIONHINT_ID, buffer);
}

void setExistingProfiles(HWND hwnd, AppData *appData)
{
    Element *current = appData->existingProfiles->first;
    int index;
    while (current != NULL)
    {
        addStringToCombo(hwnd, PROFILESEL_ID, current->content);
        current = current->next;
    }
    index = findStringIndexInCombo(hwnd, PROFILESEL_ID, appData->pName);
    if (index == CB_ERR)
        index = 0;
    setComboCursor(hwnd, PROFILESEL_ID, index);
    appData->pName = updateField(appData->pName, hwnd, PROFILESEL_ID, index);
    setLatestScriptsForProfile(hwnd, LASTSCRLIST_ID, appData->pName);
    updateHint(hwnd, appData->pName);
}

void setMessage(char *message, char *pName)
{
    sprintf(message, "%s %s!", PROFILEHINT_MSG, pName);
}

char *updateField(char *destination, HWND hwnd, int controlId, int idString)
{
    char buffer[MAX_NAME_LENGTH];
    getStringFromCombo(hwnd, controlId, idString, buffer);
    return resetString(destination, buffer);
}

void createProfile(HWND hwnd, AppData *appData)
{
    char buffer[MAX_NAME_LENGTH];
    initMemory(buffer, MAX_NAME_LENGTH);
    getStringFromWin(hwnd, PROFILECR_ID, buffer, MAX_NAME_LENGTH);
    int ok = checkProfileName(appData->existingProfiles, buffer, CREATE);
    if (ok)
    {
        saveProfile(hwnd, appData, buffer);
    }
}

void saveProfile(HWND hwnd, AppData *appData, char *pName)
{
    int index;
    char sent[MAX_SENT_LENGTH];
    appData->pName = resetString(appData->pName, pName);
    push(appData->existingProfiles, pName);
    index = addStringToCombo(hwnd, PROFILESEL_ID, pName);
    setComboCursor(hwnd, PROFILESEL_ID, index);
    updateHint(hwnd, pName);
    setLatestScriptsForProfile(hwnd, LASTSCRLIST_ID, pName);
    appendNameToFile(pName);
    setDefaultProfile(appData->settings, appData->pName);
    sprintf(sent, "%s %s", pName, OK_PROFILE_CR);
    printInfo(sent);
}

void appendNameToFile(char *pName)
{
    FILE *fp = openFile(getenv(LOCALSTORAGE), PROFILES_FILE, "a");
    if (fp != NULL)
    {
        fprintf(fp, "%s\n", pName);
        fclose(fp);
    }
}

void updateSettingFile(List *settings)
{
    FILE *fp = openFile(getenv(LOCALSTORAGE), CONFIG_FILE, "w");
    if (fp != NULL)
    {
        writeListToFile(settings, fp);
    }
}

void updateHint(HWND hwnd, char *pName)
{
    char buffer[MAX_SENT_LENGTH];
    setMessage(buffer, pName);
    sendWinText(hwnd, PROFILEHINT_ID, buffer);
}

int loadProfile(AppData *appData)
{
    char buffer[MAX_SENT_LENGTH];
    sprintf(buffer, "%s %s", appData->pName, OK_PROFILE_LD);
    int ok = checkProfileName(appData->existingProfiles, appData->pName, LOAD);
    if (ok)
    {
        setDefaultProfile(appData->settings, appData->pName);
        initUserDir(appData->pName);
        printInfo(buffer);
        return 1;
    }
    return 0;
}

void setDefaultProfile(List *settings, char *pName)
{
    int index = findIndex(settings, compareKey, SETT_DEF_PRO);
    if (index != -1)
    {
        char setting[MAX_SETTING_LENGTH];
        printIniToString(setting, SETT_DEF_PRO, pName);
        setElement(settings, index, setting);
        updateSettingFile(settings);
    }
}

int checkProfileName(List *profiles, char *profile, int mode)
{
    if (has(profiles, profile) && mode == CREATE)
    {
        printError(ERR_NAME_TAKEN);
        return 0;
    }
    if (!isStringSafe(profile))
    {
        printError(ERR_NAME_UNSAFE);
        return 0;
    }
    if (strlen(profile) < MIN_NAME_LENGTH || strlen(profile) >= MAX_NAME_LENGTH)
    {
        printError(ERR_NAME_LENGTH);
        return 0;
    }
    return 1;
}

void setLatestScriptsForProfile(HWND hwnd, int idControl, char *name)
{
    char fPath[MAX_PATH_LENGTH];
    List *scripts = listInit();
    sprintf(fPath, "%s\\%s\\%s\\%s", getenv(LOCALSTORAGE), DATA_DIR, name, name);
    destroyComboContent(hwnd, idControl);
    FILE *fp = fopen(fPath, "r");
    if (fp != NULL)
    {
        getFileContent(scripts, MAX_FILE_LENGTH, MIN_FILE_LENGTH, fp, 0);
        removeClones(scripts);
        Element *current = scripts->first;
        while (current != NULL)
        {
            addStringToCombo(hwnd, idControl, current->content);
            current = current->next;
        }
        setComboCursor(hwnd, idControl, 0);
    }
    destroyList(scripts);
}

void reExportScript(HWND hwnd, int controlId, char *pName)
{
    OPENFILENAME ofn;
    char fName[MAX_FILE_LENGTH];
    getCurrentStringFromCombo(hwnd, controlId, fName);
    char file[MAX_PATH_LENGTH];
    initMemory(file, MAX_PATH_LENGTH);
    char fCopy[MAX_PATH_LENGTH];
    sprintf(fCopy, "%s\\%s\\%s\\%s", getenv(LOCALSTORAGE), DATA_DIR, pName, fName);
    setOfn(hwnd, &ofn, file, NULL);
    if (GetSaveFileName(&ofn))
    {
        CopyFile(fCopy, file, FALSE);
    }
}