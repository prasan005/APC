#include "header.h"
int addition(Dlist *op1, Dlist *op2, Dlist **res_h, Dlist **res_t)
{
    int carry=0;
    while (op1 != NULL || op2 != NULL || carry !=0)
    {
        int sum = carry;
        if(op1 != NULL)
        {
            sum = sum+ op1->data;
            op1 = op1->prev; 
        }

        if(op2 != NULL)
        {
            sum = sum+ op2->data;
            op2 = op2->prev; 
        }

        Dlist *new = malloc(sizeof(Dlist));
        new->data = sum%10;
        carry = sum/10;
        new->prev = new->next = NULL;
        if(*res_h == NULL && *res_t == NULL)
        {
            *res_h = *res_t = new;
        }
        else
        {
            (*res_h)->prev = new;
            new->next = *res_h;
            *res_h = new;
        }

    }
    
     return 0;
}


int subtraction(Dlist *op1, Dlist *op2, Dlist **res_h, Dlist **res_t)
{
    int borrow = 0;
    while(op1 != NULL || op2 != NULL)
    {
        int sub = -borrow;
        if(op1 != NULL)
        {
            sub = sub + op1->data;
            op1 = op1->prev;
        }

        if(op2 != NULL)
        {
            sub = sub - op2->data;
            op2 = op2->prev;
        }

        if(sub<0)
        {
            sub = sub + 10;
            borrow = 1;
        }
        else{
            borrow = 0;
        }

        Dlist *new = malloc(sizeof(Dlist));
        if(new == NULL)
            return -1;
        new->data = sub;
        new->next= new->prev = NULL;
        if(*res_h == NULL && *res_t == NULL)
        {
            *res_h = *res_t = new;
        }
        else
        {
            (*res_h)->prev = new;
            new->next = *res_h;
            *res_h = new;
        }
    }

    while(*res_h != NULL && (*res_h)->next != NULL && (*res_h)->data == 0)
    {
        Dlist *temp = *res_h;
        *res_h = temp->next;
        (*res_h)->prev = NULL;
        free(temp);
    }

    return 0;
}



int multiplication(Dlist *op1, Dlist *op2, Dlist **res_h, Dlist **res_t)
{
    int count = 0;
    Dlist *mul_hd = NULL, *mul_td = NULL;

    while (op1 != NULL)
    {
        Dlist *mul_h = NULL, *mul_t = NULL;
        Dlist *temp = op2;
        int carry = 0;
        while (temp != NULL || carry > 0)
        {
            int sum = 0;
            if (temp != NULL)
            {
                sum = op1->data * temp->data;
                temp = temp->prev;
            }
            sum = sum + carry;
            Dlist *new = malloc(sizeof(Dlist));
            new->data = sum % 10;
            carry = sum / 10;
            new->next = new->prev = NULL;
            if (mul_h == NULL && mul_t == NULL)
            {
                mul_h = mul_t = new;
            }
            else
            {
                mul_h->prev = new;
                new->next = mul_h;
                mul_h = new;
            }
        }

        int i = 0;
        while (i < count)
        {
            Dlist *new = malloc(sizeof(Dlist));
            new->data = 0;
            new->prev = mul_t;
            mul_t->next = new;
            mul_t = new;
            new->next = NULL;
            i++;
        }

        Dlist *old = mul_hd;
        addition(mul_t, mul_td, res_h, res_t);
        free_list(old); /* free_list(NULL) is fine on the first round */
        mul_hd = *res_h;
        mul_td = *res_t;
        free_list(mul_h);
        op1 = op1->prev;
        count++;
        if (op1 != NULL)
            *res_h = *res_t = NULL;
    }

    while ((*res_h)->next != NULL && (*res_h)->data == 0)
    {
        Dlist *temp = *res_h;
        *res_h = temp->next;
        (*res_h)->prev = NULL;
        free(temp);
    }
    return 0;
}


int division(Dlist *op1, Dlist *op2, Dlist **res_h, Dlist **res_t)
{
    Dlist *rem_h = NULL, *rem_t = NULL;   /* running remainder */
    Dlist *q_h = NULL, *q_t = NULL;       /* quotient */
    Dlist *tr_h, *tr_t;
    Dlist *op2_t = op2;
    Dlist *temp = op1;
    Dlist *chk = op2;

    if (op1 == NULL || op2 == NULL)
        return -1;

    /* division by zero */
    while (chk != NULL && chk->data == 0)
        chk = chk->next;
    if (chk == NULL)
    {
        printf("Division by zero\n");
        return -1;
    }

    while (op2_t->next != NULL)
        op2_t = op2_t->next;

    while (temp != NULL)
    {
        /* bring down the next digit into the remainder */
        if (rem_h != NULL && rem_h->next == NULL && rem_h->data == 0)
            rem_h->data = temp->data;          /* remainder was 0, just replace it */
        else
        {
            Dlist *new = malloc(sizeof(Dlist));
            if (new == NULL)
            {
                free_list(rem_h);
                free_list(q_h);
                return -1;
            }
            new->data = temp->data;
            new->next = NULL;
            new->prev = rem_t;
            if (rem_h == NULL)
                rem_h = new;
            else
                rem_t->next = new;
            rem_t = new;
        }

        /* how many times does op2 fit into the remainder (0 to 9) */
        int count = 0;
        while (compare_list(rem_h, op2) >= 0)
        {
            tr_h = tr_t = NULL;
            subtraction(rem_t, op2_t, &tr_h, &tr_t);
            free_list(rem_h);                  /* old remainder not needed */
            rem_h = tr_h;
            rem_t = tr_t;
            count++;
        }

        /* every brought-down digit gives exactly one quotient digit */
        Dlist *q = malloc(sizeof(Dlist));
        if (q == NULL)
        {
            free_list(rem_h);
            free_list(q_h);
            return -1;
        }
        q->data = count;
        q->next = NULL;
        q->prev = q_t;
        if (q_h == NULL)
            q_h = q;
        else
            q_t->next = q;
        q_t = q;

        temp = temp->next;
    }

    /* remove leading zeros of quotient, keep at least one digit */
    while (q_h->next != NULL && q_h->data == 0)
    {
        Dlist *t = q_h;
        q_h = t->next;
        q_h->prev = NULL;
        free(t);
    }

    free_list(rem_h);
    *res_h = q_h;
    *res_t = q_t;
    return 0;
}