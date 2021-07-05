#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    long numb;
    long numbCopy;
    int len = 0;
    do
    {
        //get the number
        numb = get_long("Credit card number: ");
        numbCopy = numb;
        //get the number's length
        for (; numbCopy > 0; len++)
        {
            numbCopy /= 10;
        }
    }
    //reprompt if the numbers were less than 13 digit or more than 16
    while (len < 9);

    //Luhn's algorithm
    numbCopy = numb;
    int sum = 0;
    for (int i = 0; numbCopy > 0; i++)
    {
        //add every other number starting from the far right to sum
        int tempNumb;
        if (i % 2 == 0)
        {
            tempNumb = numbCopy % 10;
            sum += tempNumb;
        }

        //get every other number starting from the second to far right and * them with 2 then add every digit to the sum on it's own
        else
        {
            tempNumb = (numbCopy % 10) * 2;
            sum += (tempNumb / 10) + (tempNumb % 10);
        }
        //move on to the next number
        numbCopy = numbCopy / 10;
    }

    //make an array to hold all the numbers
    numbCopy = numb;
    int newNumber;
    int digits[len];
    for (int i = 0; i < len ; i++)
    {
        newNumber = numbCopy % 10;
        digits[i] = newNumber;
        numbCopy /= 10;
    }


    //If its a valid card number it checks what type it is based on the first two numbers
    if ((sum % 10 == 0) && (len > 12))
    {
        //American Express
        if ((digits[len - 1] == 3) && (digits[len - 2] == 7 || digits[len - 2] == 4))
        {
            printf("AMEX\n");
        }
        //MasterCard
        else if ((digits[len - 1] == 5) && (digits[len - 2] == 1 || digits[len - 2] == 2
        || digits[len - 2] == 3 || digits[len - 2] == 4 || digits[len - 2] == 5))
        {
            printf("MASTERCARD\n");
        }
        //Visa
        else if (digits[len-1] == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    //if the number is inVALID
    else
    {
        printf("INVALID\n");
    }

}