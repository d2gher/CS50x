#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //initialize n to store the number of columns
    int n;
    //promte for the number and repeat the prome if it doesn't meet the conditions
    do
    {
        n = get_int("How tall? (from 1 to 8)\n");
    }
    while (n < 1 || n > 8);

    // get how many space or hash in a line
    int space = n;
    int hash = 0;
    for (int e = 0; e < n; e++)
    {
        //subtract or add how many space or hashs on each line
        hash++;
        space--;
        //first pyramid
        for (int i = 0; i < space; i++)
        {
            printf(" ");
        }
        for (int i = 0; i < hash; i++)
        {
            printf("#");
        }
        //space between the two pyramids
        printf("  ");

        //second pyramid
        for (int o = 0; o < hash; o++)
        {
            printf("#");
        }
        //next line
        printf("\n");
    }
}