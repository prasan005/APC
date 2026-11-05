#include "header.h"

int main(int argc, char *argv[])
{
    Dlist *op1_h = NULL, *op1_t = NULL;
    Dlist *op2_h = NULL, *op2_t = NULL;
    Dlist *res_h = NULL, *res_t = NULL;

    if (argc != 4)
    {
        printf("Usage: ./a.out number1 operator number2\n");
        return 1;
    }

    if (dynamic_memory(&op1_h, &op1_t, argv[1]) != 0 || dynamic_memory(&op2_h, &op2_t, argv[3]) != 0)
    {
        printf("Invalid number\n");
        free_list(op1_h);
        free_list(op2_h);
        return 1;
    }
    int flag = 0;
    if (argv[2][0] == '+')
    {
        if (argv[1][0] != '-' && argv[3][0] != '-')
        {
            // + num1 + num2 = positive addition
            addition(op1_t, op2_t, &res_h, &res_t);
        }
        else if (argv[1][0] == '-' && argv[3][0] == '-')
        {
            // - num1 + - num2 = negative addition
            addition(op1_t, op2_t, &res_h, &res_t);
            flag = 1;
        }
        else
        {
            // Different signs: subtract magnitudes
            int cmp = compare_list(op1_h, op2_h);

            if (cmp >= 0)
            {
                subtraction(op1_t, op2_t, &res_h, &res_t);
                if (argv[1][0] == '-' && cmp != 0)
                    flag = 1;
            }
            else
            {
        
                subtraction(op2_t, op1_t, &res_h, &res_t);
                if (argv[3][0] == '-' && cmp != 0)
                    flag = 1;
            }
        }
    }
    else if (argv[2][0] == '-')
    {

        if (argv[1][0] != '-' && argv[3][0] == '-')
        {
            //pos add
            addition(op1_t, op2_t, &res_h, &res_t);
        }
        else if (argv[1][0] == '-' && argv[3][0] != '-')
        {
            //neg add
            addition(op1_t, op2_t, &res_h, &res_t);
            flag = 1;
        }
        else
        {
            int cmp = compare_list(op1_h, op2_h);
            if (argv[1][0] == '-' && argv[3][0] == '-')
            {
                if (cmp > 0)
                {
                    subtraction(op1_t, op2_t, &res_h, &res_t);
                    flag = 1;
                }
                else if (cmp <= 0)
                {
                    subtraction(op2_t, op1_t, &res_h, &res_t);
                }
            }
            else if (argv[1][0] != '-' && argv[3][0] != '-')
            {
                if (cmp >= 0)
                {
                    subtraction(op1_t, op2_t, &res_h, &res_t);
                }
                else
                {
                    subtraction(op2_t, op1_t, &res_h, &res_t);
                    flag = 1;
                }
            }
        }
    }
    else if (argv[2][0] == 'x')
    {
        if ((argv[1][0] == '-' && argv[3][0] != '-') || (argv[1][0] != '-' && argv[3][0] == '-'))
            flag = 1;
        multiplication(op1_t, op2_t, &res_h, &res_t);
    }
    else if (argv[2][0] == '/')
    {
        if ((argv[1][0] == '-' && argv[3][0] != '-') || (argv[1][0] != '-' && argv[3][0] == '-'))
            flag = 1;
        if (division(op1_h, op2_h, &res_h, &res_t) != 0)
        {
            free_list(op1_h);
            free_list(op2_h);
            return 1;
        }
    }
    else
    {
        printf("Invalid operator\n");
        return 1;
    }

    if (res_h != NULL && res_h->next == NULL && res_h->data == 0)
        flag = 0; /* no "-0" */

    print_list(res_h, flag);
    free_list(op1_h);
    free_list(op2_h);
    free_list(res_h);
    return 0;
}
