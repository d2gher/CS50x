#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//prototype
int valid_key(string key);

int main(int argc, string argv[])
{
    //checks if the user added just 1 string after the tool's name as cml argument
    if (argc == 2)
    {
        //stores what the user add, and uses it as the ciphering key
        string key = argv[1];

        //checks if the key the user add is valid, i.e. 26 alphabet characters with no duplucates
        if (valid_key(key))
        {
            //if it is, then ask the user for the text to encrypt
            string P = get_string("Plaintext: ");

            printf("ciphertext: ");
            //loop through every character
            for (int i = 0, n = strlen(P); i < n; i++)
            {
                int character;
                //encrypt it if it's an alphabet
                if (isalpha(P[i]))
                {
                    if (isupper(P[i]))
                    {
                        character = toupper(key[P[i] - 65]);
                        printf("%c", character);
                    }
                    else
                    {
                        character = tolower(key[P[i] - 97]);
                        printf("%c", character);
                    }
                }
                //print it as it is if it's not an alphabet
                else
                {
                    printf("%c", P[i]);
                }
            }
            printf("\n");
            //everything works fine
            return 0;
        }
        else
        {
            printf("Key must contain 26 unique alphabet characters.\n");
            //something went wrong
            return 1;
        }
    }
    //get out if there isn't a ciphering key or the user isn't using the tool right
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

//check if a string of characters is a valid encryption key
int valid_key(string key)
{
    int keyLen = 26;
    int Char = 0;

    //mark every seen character
    char seen[26] = {0};
    int seenInt = 0;
    int tempKey = 0;

    //make sure every character is from the alphabet
    for (int i = 0; i < keyLen; i++)
    {
        if (isalpha(key[i]))
        {
            Char++;
        }
        //mark a character as seen in the seen[] array
        tempKey = toupper(key[i]);
        seen[tempKey - 'A']++;
    }

    //loops through the seen array to make sure every character was once, and no more
    for (int i = 0; i < keyLen; i++)
    {
        if (seen[i] == 1)
        {
            seenInt++;
        }
    }
    //if the key has 26 unique alphabet characters, return 1
    if (Char == keyLen && seenInt == keyLen)
    {
        return 1;
    }
    //return 0 if not
    else
    {
        return 0;
    }

}
