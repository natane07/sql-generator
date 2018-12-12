#ifndef PARSER_H

#define PARSER_H

#include <stdio.h>

int parseIni(char *, char *, char *);
void printIniToFile(FILE *, char *, char *);
void printIniToString(char *, char *, char *);

#endif