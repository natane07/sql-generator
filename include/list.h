#ifndef LIST_H

#define LIST_H

typedef struct Element Element;
struct Element
{
    char *content;
    Element *next;
};

typedef struct List List;
struct List
{
    Element *first;
    int length;
};

List *listInit();
void push(List *, char *);
void unshift(List *, char *);
void pop(List *);
void shift(List *);
int has(List *, char *);
void forEach(List *, void (*)(char *, void *), void *);
int findIndex(List *, int (*)(char *, char *), char *);
void destroyList(List *);
void printList(List *);
void printElement(char *);
Element *getElement(List *, int);
void setElement(List *, int, char *);

#endif