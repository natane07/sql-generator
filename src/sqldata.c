#include ".\..\include\sqldata.h"
#include ".\..\include\sql.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int generateDataInteger(int min, int max)
{
    return rand() % ((max + 1) - min) + min;
}

int generateGender()
{
    return generateDataInteger(0, 1);
}

void generateGUID()
{
}

float generateDataDouble()
{
    int max = 90;
    int min = 10;
    int bigratio;
    float proba;
    bigratio = generateDataInteger(min, max);
    proba = bigratio / 10.0;
    return proba;
}

void generateDataDate(char *date)
{
    int day = generateDataInteger(1, 25);
    int month = generateDataInteger(1, 12);
    int year = generateDataInteger(2000, 2018);
    if (day < 10)
    {
        if (month < 10)
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
        if (month < 10)
        {
            sprintf(date, "%d/0%d/%d", day, month, year);
        }
        else
        {
            sprintf(date, "%d/%d/%d", day, month, year);
        }
    }
}

void generateDataText(char *text, int size)
{
    int i;
    char pc[] = "abcdefghijklmnopqrstuvwxyz";
    for (i = 0; i < size; i++)
    {
        text[i] = pc[generateDataInteger(0, 25)];
    }
    text[size] = '\0';
}

void generateCity(char city[])
{
    FILE *fichier = NULL;
    char ville[11][200];
    fichier = fopen("./ville.txt", "r");
    if (fichier != NULL)
    {
        fscanf(fichier, "%s %s %s %s %s %s %s %s %s %s", ville[1], ville[2], ville[3], ville[4], ville[5], ville[6], ville[7], ville[8], ville[9], ville[10]);
        fclose(fichier);
    }
    int random = rand() % (1 - 11) + 1;
    strcpy(city, ville[random]);
}

void generateName(char name[])
{
    FILE *fichier = NULL;
    char tab_name[11][200];
    fichier = fopen("./name.txt", "r");
    if (fichier != NULL)
    {
        fscanf(fichier, "%s %s %s %s %s %s %s %s %s %s", tab_name[1], tab_name[2], tab_name[3], tab_name[4], tab_name[5], tab_name[6], tab_name[7], tab_name[8], tab_name[9], tab_name[10]);
        fclose(fichier);
    }
    int random = rand() % (1 - 11) + 1;
    strcpy(name, tab_name[random]);
}

void generateNumberPhone(char *numberPhone)
{
    int i;
    int number[10];
    char tab_numberPhone[20];
    strcpy(numberPhone, "0");
    for (i = 0; i < 9; i++)
    {
        number[i] = generateDataInteger(0, 9);
        sprintf(tab_numberPhone, "%d", number[i]);
        strcat(numberPhone, tab_numberPhone);
    }
}

void generateMail(char mail[])
{
    FILE *fichier = NULL;
    int random;
    char name[250];
    char tab_mail[11][200];
    fichier = fopen("./mail.txt", "r");
    if (fichier != NULL)
    {
        fscanf(fichier, "%s %s %s %s %s %s %s %s %s %s", tab_mail[1], tab_mail[2], tab_mail[3], tab_mail[4], tab_mail[5], tab_mail[6], tab_mail[7], tab_mail[8], tab_mail[9], tab_mail[10]);
        fclose(fichier);
    }
    random = rand() % (1 - 10) + 1;
    generateName(name);
    strcpy(mail, name);
    strcat(mail, tab_mail[random]);
}

void WriteInsDataToFile()
{
    char query[SQL_QUERY_MAX_LENGTH];
    strcpy(query, SQL_DATA_INSERT);
}