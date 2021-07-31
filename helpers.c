#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //go through each row of pixels
    for (int i = 0; i < height; i++)
    {
        //go throuh each pixel in the row
        for (int j = 0; j < width; j++)
        {
            //get the average of the colors in the pixel and use it as the intensity of the grayscale
            float avrg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / (float) 3;
            image[i][j].rgbtBlue = round(avrg);
            image[i][j].rgbtGreen = round(avrg);
            image[i][j].rgbtRed = round(avrg);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //go through each row of pixels
    for (int i = 0; i < height; i++)
    {
        //go throuh each pixel in the row
        for (int j = 0; j < width; j++)
        {
            //gets the colors of the original pixel
            float originalRed = image[i][j].rgbtRed;
            float originalGreen = image[i][j].rgbtGreen;
            float originalBlue = image[i][j].rgbtBlue;

            //use an algorithm to get the sepia colors for that pixel
            float sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            float sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            float sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            //make sure no value goes past 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            //assign the new colors
            image[i][j].rgbtBlue = round(sepiaBlue);
            image[i][j].rgbtGreen = round(sepiaGreen);
            image[i][j].rgbtRed = round(sepiaRed);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //make a new array then copy the image to it
    RGBTRIPLE(*img_copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        //go throuh each pixel in the row
        for (int j = 0; j < width; j++)
        {
            img_copy[i][j] = image[i][j];
        }
    }
    //go through each row of pixels
    for (int i = 0; i < height; i++)
    {
        //go throuh each pixel in the row and change it with the one from the opposite side
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = img_copy[i][width - 1 - j].rgbtBlue ;
            image[i][j].rgbtGreen = img_copy[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtRed = img_copy[i][width - 1 - j].rgbtRed;
        }
    }
    free(img_copy);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //make a new array then copy the image to it
    RGBTRIPLE(*img_copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    for (int i = 0; i < height; i++)
    {
        //go throuh each pixel in the row
        for (int j = 0; j < width; j++)
        {
            img_copy[i][j] = image[i][j];
        }
    }
    //go through each row of pixels
    for (int i = 0; i < height; i++)
    {
        //go throuh each pixel in the row
        for (int j = 0; j < width; j++)
        {
            //to store the averges in
            int red = 0;
            int green = 0;
            int blue = 0;
            int boxes = 0;
            //create a 3*3 box around the pixel and store the value color of each bit of it
            //as long as it's still in the array
            for(int r = i - 1; r < i + 2; r++)
            {
                for (int c = j - 1; c < j + 2; c++)
                {
                    if (r >= 0 && r < height && c >= 0 && c < width)
                    {
                        red += img_copy[r][c].rgbtRed;
                        green += img_copy[r][c].rgbtGreen;
                        blue += img_copy[r][c].rgbtBlue;
                        boxes++;
                    }
                }
            }
            //calculate the avarge of each color and make it that pixel's color
            image[i][j].rgbtBlue = round(blue / (float) boxes);
            image[i][j].rgbtGreen = round(green / (float) boxes);
            image[i][j].rgbtRed = round(red / (float) boxes);
        }
    }
    free(img_copy);
    return;
}
