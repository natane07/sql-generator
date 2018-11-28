#include "..\include\utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int getChoice()
{
    int choice;
    printf("Enter choice: ");
    fflush(stdin);
    choice = fgetc(stdin) - 48;
    return choice;
}

void getString(char *string, int maxSize)
{
    fflush(stdin);
    fgets(string, maxSize, stdin);
    if (string[strlen(string) - 1] == '\n')
        string[strlen(string) - 1] = '\0';
}

void remCrlf(char *str)
{
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
}

char *setString(char *destination, char *source)
{
    destination = malloc((strlen(source) + 1) * sizeof(char));
    strcpy(destination, source);
    return destination;
}

char *resetString(char *destination, char *source)
{
    free(destination);
    setString(destination, source);
    return destination;
}