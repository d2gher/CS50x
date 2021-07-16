#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    //gets the text we want to test
    string theText = get_string("Text: ");
    //gets the text's length
    const int LENGTH = strlen(theText);

    double letters = 0;
    double words = 1;
    double sentences = 0;

    //go through the whole text and count how many letters and sentences
    for (int i = 0; i < LENGTH; i++)
    {
        //if that spot in the text is in the alphapet, count it in letters
        if (isalpha(theText[i]))
        {
            letters++;
        }
        //whenever there is space, it adds to the words counter
        if (theText[i] == ' ')
        {
            words++;
        }
        //whenever there is (., ?, !), it adds to the sentences counter
        if (theText[i] == '.' || theText[i] == '?' || theText[i] == '!')
        {
            sentences++;
        }
    }

    //average of the letters and sentences
    double L = letters / words * 100;
    double S = sentences / words * 100;

    //Coleman-Liau index
    double index = 0.0588 * L - 0.296 * S - 15.8;
    //round index to the nearest value
    index = round(index);

    //print the result
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int)index);
    }
}
