#include ".\..\include\sqldata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int generateDataInteger(int min, int max)
{
    srand(time(NULL));
    return rand() % (max - min) + min;
}

float generateDataDouble()
{
    int max = 90;
    int min = 10;
    int bigratio;
    float proba;
    srand(time(NULL));
    bigratio = generateDataInteger(min, max);
    proba = bigratio / 10.0;
    return proba;
}

void generateDataDate(char *date)
{
    int day = generateDataInteger(1, 25);
    int month = generateDataInteger(1, 12);
    int year = generateDataInteger(2000, 2018);
    if (day > 0 && day < 10)
    {
        if (month > 0 && month < 10)
        {
            sprintf(date, "0%d/0%d/%d", day, month, year);
        }
        else
        {
            sprintf(date, "0%d/%d/%d", day, month, year);
        }
    }
    else
    {
        if (month > 0 && month < 10)
        {
            sprintf(date, "%d/0%d/%d", day, month, year);
        }
    }
}

char *generateDataText(char *text, int SIZE)
{
    unsigned char ar[SIZE];
    char text_tempo[SIZE];
    int size;
    int i;
    strcpy(text, "\0");
    strcpy(text_tempo, "\0");
    srand(time(NULL));
    for (i = 0; i < SIZE; i++)
    {
        ar[i] = 'A' + rand() % 26;
        size = strlen(text);
        text[size] = ar[i];
        text[size + 1] = '\0';
    }
    return text;
}