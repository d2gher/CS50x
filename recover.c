#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
const int BUFFER_SIZE = 512;

int main(int argc, char *argv[])
{
    //make sure the user uses the tool currectly
    //by providing the filename where we will restore the images from
    if (argc != 2)
    {
     printf("USAGE: ./recover fileName\n");
     return 1;
    }
    //open that file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Couldn't open file\n");
        return 2;
    }

    BYTE buffer[BUFFER_SIZE]; //array to use as a buffer
    int counter = 0;          //count what the image we are on
    FILE *image = NULL;       //file type to save the new image into

    //do this while there is still data to read
    while (fread(&buffer, BUFFER_SIZE, 1, input))
    {
        //when we find a new image
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //if there is an image file opened before, close it
            if (image != NULL)
            {
                fclose(image);
            }

            //array to store the name of the image into
            //7bits for the name and 1bit for the null char
            char image_name[8];
            //the 03 in "%03i" makes whatever number in counter be written in 3 dismals
            //i.e. 5 will be 005
            sprintf(image_name, "%03i.jpg", counter);
            //open an image file to copy the data into
            image = fopen(image_name, "w");
            if (image == NULL)
            {
                printf("Couldn't create image file \n");
                return 4;
            }
            counter++;
        }
        //if there is an image file open, copy the current chunk of data stored inside buffer into it
        if (image != NULL)
        {
            fwrite(&buffer, BUFFER_SIZE, 1, image);
        }
    }
    //close the files that are open
    if (image != NULL)
    {
        fclose(image);
    }
    if (input != NULL)
    {
        fclose(input);
    }
}
