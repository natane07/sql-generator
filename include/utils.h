#ifndef UTILS_H

#define UTILS_H

#define ALPHA_NUM "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

int getChoice();
char *getString(char *, int);
void remCrlf(char *);
char *setString(char *, char *);
char *resetString(char *, char *);
int isStringSafe(char *);
int compareKey(char *, char *);

#endif