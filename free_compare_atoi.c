#include "header.h"
int dynamic_memory(Dlist **op_h, Dlist **op_t, char *str)
{
    int i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;

    for (; str[i] != '\0'; i++)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            free_list(*op_h);
            *op_h = *op_t = NULL;
            return -1;
        }

        Dlist *new = malloc(sizeof(Dlist));

        if (new == NULL)
        {
            free_list(*op_h);
            *op_h = *op_t = NULL;
            return -1;
        }

        if (*op_h == NULL && *op_t == NULL)
        {
            *op_h = *op_t = new;
            new->next = new->prev = NULL;
            new->data = str[i] - '0';
        }
        else
        {
            (*op_t)->next = new;
            new->prev = *op_t;
            new->next = NULL;
            new->data = str[i] - '0';
            *op_t = new;
        }
    }

    if (*op_h == NULL)
        return -1;

    return 0;
}




void free_list(Dlist *head)
{
    
    while(head!= NULL)
    {
        Dlist *temp = head;
        head = head->next;
        free(temp);
    }
}



int compare_list(Dlist *a, Dlist *b)
{
    int count1 = 0, count2 = 0;
    Dlist *p;

    while (a != NULL && a->next != NULL && a->data == 0)   /* skip leading zeros */
        a = a->next;
    while (b != NULL && b->next != NULL && b->data == 0)
        b = b->next;

    for (p = a; p != NULL; p = p->next) count1++;
    for (p = b; p != NULL; p = p->next) count2++;

    if (count1 != count2)
        return (count1 > count2) ? 1 : -1;

    while (a != NULL && b != NULL)
    {
        if (a->data != b->data)
            return (a->data > b->data) ? 1 : -1;
        a = a->next;
        b = b->next;
    }
    return 0;
}