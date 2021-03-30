#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // to iterate around each pixle on width and height
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixels = image[i][j];
            int average = round((pixels.rgbtRed + pixels.rgbtGreen + pixels.rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixels = image[i][j];

            int sepiaRed = round(.393 * pixels.rgbtRed + .769 * pixels.rgbtGreen + .189 * pixels.rgbtBlue);
            {
                if ( sepiaRed > 255)
                {
                    sepiaRed = 255;
                }
                image[i][j].rgbtRed = sepiaRed;
            }

            int sepiaGreen = round(.349 * pixels.rgbtRed + .686 * pixels.rgbtGreen + .168 * pixels.rgbtBlue);
            {
                if ( sepiaGreen > 255)
                {
                    sepiaGreen = 255;
                }
                image[i][j].rgbtGreen = sepiaGreen;
            }

            int sepiaBlue = round(.272 * pixels.rgbtRed + .534 * pixels.rgbtGreen + .131 * pixels.rgbtBlue);
            {
                if ( sepiaBlue > 255)
                {
                    sepiaBlue = 255;
                }
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp [height][width];
    for (int i = 0; i < height; i++)
    {
        int currentPix = 0;
        for (int j = width - 1; j >= 0; j--, currentPix++)
        {
            temp[i][currentPix] = image[i][j];
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j]; 
        }
    }
    
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++) 
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            
            //so we can figure out what to divide by , also dont forget to always do floats as a decimal 
            float pixCounter = 0.00; 
            // i and h are needed to confirm things before we start doing math
            for (int k = -1; k < 2; k++)
            { 
                for (int h = -1; h < 2; h++) 
                { 
                    if (i + k < 0 || i + k > height - 1 || j + h < 0 || j + h > width - 1)
                    {
                        continue;
                    }
                    
                    sumRed += image[i + k][j + h].rgbtRed;
                    sumGreen += image[i + k][j + h].rgbtGreen;
                    sumBlue += image[i + k][j + h].rgbtBlue;
                    
                    pixCounter++;
                }
                    
            }
            
            temp[i][j].rgbtRed = round(sumRed / pixCounter);
            temp[i][j].rgbtGreen = round(sumGreen / pixCounter);
            temp[i][j].rgbtBlue = round(sumBlue / pixCounter);
        }
    }
    //reiterate everything back into  the image as done in other filters.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}
