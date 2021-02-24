#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARRAY_SIZE  2000
#define INT_SIZE    9

struct Number
{
    int cells_number;
    int number_elements;
    int* wsk;
    char sign;
};


int bigger(struct Number* number1, struct Number* number2)
{
    int i = 0;

    if (number1->sign == '+' && number2->sign == '-') return 1;
    else if (number1->sign == '-' && number2->sign == '+') return 0;
    else if (number1->sign == '+' && number2->sign == '+')
    {
        if (number1->cells_number > number2->cells_number) return 1;
        else if (number1->cells_number < number2->cells_number) return 0;
        else if (number1->cells_number == number2->cells_number)
        {
            for (i = 0; i < number1->cells_number; i++)
            {
                if (number1->wsk[i] > number2->wsk[i])
                    return 1;
                else if (number1->wsk[i] < number2->wsk[i])
                {
                    return 0;
                }
            }
            return 1;
        }

    }
    else if (number1->sign == '-' && number2->sign == '-')
    {
        if (number1->cells_number > number2->cells_number) return 0;
        else if (number1->cells_number < number2->cells_number) return 1;
        else if (number1->cells_number == number2->cells_number)
        {
            for (i = 0; i < number1->cells_number; i++)
            {
                if (number1->wsk[i] > number2->wsk[i])
                    return 0;
                else if (number1->wsk[i] < number2->wsk[i])
                {
                    return 1;
                }
            }
            return 1;
        }
    }
    return 0;
}

void shellSort(struct Number** wskaznik, int number_of_elements)
{
    int k = 0, i = 0, j = 0;
    struct Number* tmp;

    int x = log(number_of_elements) / log(2);
    k = pow(2, x) - 1;

    while (k >= 1)
    {
        for (i = k; i < number_of_elements; i++)
        {
            tmp = wskaznik[i];
            j = i;
            while (j >= k && bigger(wskaznik[j - k], tmp) == 1)
            {
                wskaznik[j] = wskaznik[j - k];
                j = j - k;
            }
            wskaznik[j] = tmp;
        }
        k = (k + 1) / 2 - 1;
    }
}

void load_line(struct Number* wskaznik, char* char_tab);

void divide_totabint(struct Number* wskaznik, char* char_tab);

void print(struct Number* wskaznik);



int main()
{
    int number_of_elements = 0, i = 0;

    scanf("%d\n", &number_of_elements);

    struct Number** wskaznik = (struct Number**)malloc(number_of_elements * sizeof(struct Number*));

    for (i = 0; i < number_of_elements; i++)
    {
        wskaznik[i] = (struct Number*)malloc(sizeof(struct Number));
        wskaznik[i]->number_elements = 0;
        wskaznik[i]->cells_number = 0;
        wskaznik[i]->sign = '+';

        char* char_tab = (char*)malloc(ARRAY_SIZE * sizeof(char));

        load_line(wskaznik[i], char_tab);

        wskaznik[i]->wsk = (int*)malloc(wskaznik[i]->cells_number * sizeof(int));

        divide_totabint(wskaznik[i], char_tab);

        free(char_tab);
    }

    shellSort(wskaznik, number_of_elements);

    for (i = 0; i < number_of_elements; i++)
    {
        print(wskaznik[i]);
    }
    for (i = 0; i < number_of_elements; i++)
    {
        free(wskaznik[i]);
    }
    free(wskaznik);

    return 0;
}



void load_line(struct Number* wskaznik, char* char_tab)
{
    do
    {
        if (wskaznik->number_elements % ARRAY_SIZE == 0 && wskaznik->number_elements > 0)
        {
            char_tab = (char*)realloc((void*)char_tab, ((wskaznik->number_elements / ARRAY_SIZE) + 1) * ARRAY_SIZE * sizeof(char));
        }
        *(char_tab + wskaznik->number_elements) = getc(stdin);
        if (wskaznik->number_elements == 0 && *(char_tab) == '-')
        {
            wskaznik->sign = '-';
            wskaznik->number_elements--;
        }
        wskaznik->number_elements++;
    } while (wskaznik->number_elements == 0 || *(char_tab + wskaznik->number_elements - 1) != '\n');

    *(char_tab + wskaznik->number_elements - 1) = '\0'; wskaznik->number_elements--;

    wskaznik->cells_number = (wskaznik->number_elements / INT_SIZE) + (wskaznik->number_elements % INT_SIZE > 0 ? 1 : 0);

}

void divide_totabint(struct Number* wskaznik, char* char_tab)
{
    int k = 0, j = 0, l = 0, x = 0;
    char tablica[10];

    for (k = 0, j = 0; k < wskaznik->number_elements, j < wskaznik->cells_number; k++)
    {
        x = 0;
        if (j == 0 && k == wskaznik->number_elements % INT_SIZE - 1)
        {
            tablica[l] = *(char_tab + k);
            tablica[l + 1] = '\0';
            sscanf(tablica, "%d", &x);
            (wskaznik->wsk[j]) = x;
            l = 0; j++;
        }
        else if (((k + 1 - wskaznik->number_elements % INT_SIZE) % INT_SIZE) == 0)
        {
            tablica[l] = *(char_tab + k);
            tablica[l + 1] = '\0';
            sscanf(tablica, "%d", &x);
            (wskaznik->wsk[j]) = x;
            l = 0; j++;
        }
        else
        {
            tablica[l] = *(char_tab + k);
            l++;
        }
    }
}

void print(struct Number* wskaznik)
{
    int j;
    if (wskaznik->sign == '-') printf("%c", wskaznik->sign);

    for (j = 0; j < wskaznik->cells_number; j++)
    {
        if (j > 0)
        {
            printf("%09d", wskaznik->wsk[j]);
        }
        else
            printf("%d", wskaznik->wsk[j]);
    }
    printf("\n");
}

