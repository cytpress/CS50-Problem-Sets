#include "helpers.h"
#include <math.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;
            int avg = round((float)(r + g + b) / 3);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
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
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;
            int sepia_r = round((float)r * 0.393 + (float)g * 0.769 + (float)b * 0.189);
            int sepia_g = round((float)r * 0.349 + (float)g * 0.686 + (float)b * 0.168);
            int sepia_b = round((float)r * 0.272 + (float)g * 0.534 + (float)b * 0.131);
            sepia_r = sepia_r > 255 ? 255 : sepia_r;
            sepia_g = sepia_g > 255 ? 255 : sepia_g;
            sepia_b = sepia_b > 255 ? 255 : sepia_b;
            image[i][j].rgbtRed = sepia_r;
            image[i][j].rgbtGreen = sepia_g;
            image[i][j].rgbtBlue = sepia_b;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE temp_pixel = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp_pixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
            int sum_r = 0;
            int sum_g = 0;
            int sum_b = 0;
            int counter = 0;
            // loop from left-top to right-bot
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    // make sure the loop won't out of range
                    if (i + x >= 0 && i + x <= height - 1 && j + y >= 0 && j + y <= width - 1)
                    {
                        sum_r += image[i + x][j + y].rgbtRed;
                        sum_g += image[i + x][j + y].rgbtGreen;
                        sum_b += image[i + x][j + y].rgbtBlue;
                        counter++;
                    }
                }
            }
            copy[i][j].rgbtRed = round((float)sum_r / (float)counter);
            copy[i][j].rgbtGreen = round((float)sum_g / (float)counter);
            copy[i][j].rgbtBlue = round((float)sum_b / (float)counter);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
        }
    }
    return;
}
