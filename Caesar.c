#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//proto
int are_digits(string key);

int main(int argc, string argv[])
{
    //checks if the user added just 1 word after the tool's name
    if (argc == 2)
    {
        //stores what the user add, and uses it as the ciphering key
        string key = argv[1];
        //turn what's in the sting into intgers
        int intKey = atoi(key);

        //checks if what the user added are digits, and if so, starts to print the ciphered text
        if (are_digits(key))
        {
            string P = get_string("Plaintext: ");
            printf("ciphertext: ");

            //loop through every character
            for (int i = 0, n = strlen(P); i < n; i++)
            {
                //changing it if it is an alphabet
                if (isalpha(P[i]))
                {
                    if (isupper(P[i]))
                    {
                        int C = ((P[i] - 'A') + intKey) % 26;
                        printf("%c", 'A' + C);
                    }
                    else
                    {
                        int C = ((P[i] - 'a') + intKey) % 26;
                        printf("%c", 'a' + C);
                    }
                }
                //print it as it is if it's not from the alphabet
                else
                {
                    printf("%c", P[i]);
                }
            }
            printf("\n");
            return 0;
        }
    }
    //get out if there isn't a ciphering key or the user isn't using the tool right
    else
    {
        printf("Usage: caesar key\n");
        return 1;
    }
}

//check if a sting is just digits
int are_digits(string key)
{
    int len = strlen(key);
    int D = 0;

    for (int i = 0; i < len; i++)
    {
        if (isdigit(key[i]))
        {
            D++;
        }
    }
    //return 1 if the number of digits is equal to the length of the string
    if (D == len)
    {
        return 1;
    }
    //return 0 if not
    else
    {
        return 0;
    }

}
