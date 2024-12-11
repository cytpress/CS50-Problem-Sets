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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}};

    int Gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
            int gxR = 0, gxG = 0, gxB = 0;
            int gyR = 0, gyG = 0, gyB = 0;
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if (i + x >= 0 && i + x <= height - 1 && j + y >= 0 && j + y <= width - 1)
                    {
                        gxR += image[i + x][j + y].rgbtRed * Gx[x + 1][y + 1];
                        gxG += image[i + x][j + y].rgbtGreen * Gx[x + 1][y + 1];
                        gxB += image[i + x][j + y].rgbtBlue * Gx[x + 1][y + 1];

                        gyR += image[i + x][j + y].rgbtRed * Gy[x + 1][y + 1];
                        gyG += image[i + x][j + y].rgbtGreen * Gy[x + 1][y + 1];
                        gyB += image[i + x][j + y].rgbtBlue * Gy[x + 1][y + 1];
                    }
                }
            }
            int sobel_r = round(sqrt(gxR * gxR + gyR * gyR));
            int sobel_g = round(sqrt(gxG * gxG + gyG * gyG));
            int sobel_b = round(sqrt(gxB * gxB + gyB * gyB));

            sobel_r = sobel_r > 255 ? 255 : sobel_r;
            sobel_g = sobel_g > 255 ? 255 : sobel_g;
            sobel_b = sobel_b > 255 ? 255 : sobel_b;

            sobel_r = sobel_r < 0 ? 0 : sobel_r;
            sobel_g = sobel_g < 0 ? 0 : sobel_g;
            sobel_b = sobel_b < 0 ? 0 : sobel_b;

            copy[i][j].rgbtRed = sobel_r;
            copy[i][j].rgbtGreen = sobel_g;
            copy[i][j].rgbtBlue = sobel_b;
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
