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

char *getString(char *string, int maxSize)
{
    char buffer[maxSize];
    if (string != NULL)
        free(string);
    fflush(stdin);
    fgets(buffer, maxSize, stdin);
    remCrlf(buffer);
    string = setString(string, buffer);
    return string;
}

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
    setString(destination, source);
    return destination;
}