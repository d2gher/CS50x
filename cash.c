#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //Initialize our change and give them value
    int quarters = 0;
    int dimes = 0;
    int nickels = 0;
    int pennies = 0;
    float Dollars;
    int coins = 0;
    //get the amount
    do
    {
        Dollars = get_float("The price:");
    }
    while (Dollars < 0);

    //get the change of that amount
    float cents = round(Dollars * 100);

    while (cents >= 25)
    {
        cents-= 25;
        coins++;
        quarters++;
    }
    while (cents >= 10)
    {
        cents-= 10;
        coins++;
        dimes++;
    }
    while (cents >= 5)
    {
        cents-= 5;
        coins++;
        nickels++;
    }
    while (cents >= 1)
    {
        cents-= 1;
        coins++;
        pennies++;
    }
    //print the result
    printf("coins: %i\n", coins);
    printf("quarters: %i\n", quarters);
    printf("dimes: %i\n", dimes);
    printf("nickels: %i\n", nickels);
    printf("pennies: %i\n", pennies);
}