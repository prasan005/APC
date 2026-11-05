#include"header.h"
void print_list(Dlist *res,int flag)
{
    Dlist *temp = res;
    printf("Result = ");
    
    if(flag)
        printf("-");
    while(temp != NULL)
    {
        printf("%d",temp->data);
        temp = temp->next;
    }
    printf("\n");
}