#include "..\include\utils.h"
#include "..\include\parser.h"
#include "..\include\file.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void remCrlf(char *str)
{
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
}

char *setString(char *destination, char *source)
{
    destination = malloc((strlen(source) + 1) * sizeof(char));
    if (destination == NULL)
        exit(-1);
    strcpy(destination, source);
    return destination;
}

char *resetString(char *destination, char *source)
{
    free(destination);
    return setString(destination, source);
}

int isStringSafe(char *str)
{
    char allowedChars[] = ALPHA_NUM;
    char *match;
    int i;
    for (i = 0; i < strlen(str); i++)
    {
        match = strpbrk(str + i, allowedChars);
        if (match != str + i)
        {
            return 0;
        }
    }
    return 1;
}

int compareKey(char *ini, char *comparator)
{
    int ok;
    char key[MAX_SETTING_SIZE];
    char value[MAX_SETTING_SIZE];
    ok = parseIni(ini, key, value);
    if (ok)
    {
        return strcmp(comparator, key) == 0;
    }
    return 0;
}

void printError(const char *error)
{
    MessageBox(NULL, error, "Error!", MB_ICONERROR | MB_OK);
}