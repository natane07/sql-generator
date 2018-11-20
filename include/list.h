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
char *pop(List *);
char *shift(List *);
void forEach(List *, void (*)(char **, void *), void *);
void printList(List *);
void printElement(char *);
Element *getElement(List *, int);
void setElement(List *, int, char *);

#endif