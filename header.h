#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct list
{

    struct list *prev;
    int data;
    struct list *next;
} Dlist;

int dynamic_memory(Dlist **, Dlist **, char *);
int compare_list(Dlist *, Dlist *);
int addition(Dlist *, Dlist *, Dlist **, Dlist **);
int subtraction(Dlist *, Dlist *, Dlist **, Dlist **);
int multiplication(Dlist *, Dlist *, Dlist **, Dlist **);
int division(Dlist *, Dlist *, Dlist **, Dlist **);
void print_list(Dlist *,int);
void free_list(Dlist *);

#endif