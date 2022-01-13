#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0 + 0.5;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp_image[i][j] = image[i][width - 1 - j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp_image[i][j];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp_image[i][j] = image[i][j];
        }
    }

    // Blur middle pixels of image
    if (height >= 3 && width >= 3)
    {
        for (int i = 1; i < height - 1; i++)
        {
            for (int j =  1; j < width - 1; j++)
            {
                image[i][j].rgbtBlue = (tmp_image[i - 1][j - 1].rgbtBlue + tmp_image[i - 1][j].rgbtBlue + tmp_image[i - 1][j + 1].rgbtBlue +
                                        tmp_image[i][j - 1].rgbtBlue + tmp_image[i][j].rgbtBlue + tmp_image[i][j + 1].rgbtBlue + tmp_image[i + 1][j - 1].rgbtBlue +
                                        tmp_image[i +  1][j].rgbtBlue + tmp_image[i + 1][j + 1].rgbtBlue) / 9.0 + 0.5;

                image[i][j].rgbtGreen = (tmp_image[i - 1][j - 1].rgbtGreen + tmp_image[i - 1][j].rgbtGreen + tmp_image[i - 1][j + 1].rgbtGreen +
                                         tmp_image[i][j - 1].rgbtGreen + tmp_image[i][j].rgbtGreen + tmp_image[i][j + 1].rgbtGreen + tmp_image[i + 1][j - 1].rgbtGreen +
                                         tmp_image[i + 1][j].rgbtGreen + tmp_image[i + 1][j + 1].rgbtGreen) / 9.0 + 0.5;

                image[i][j].rgbtRed = (tmp_image[i - 1][j - 1].rgbtRed + tmp_image[i - 1][j].rgbtRed + tmp_image[i - 1][j + 1].rgbtRed +
                                       tmp_image[i][j - 1].rgbtRed + tmp_image[i][j].rgbtRed + tmp_image[i][j + 1].rgbtRed + tmp_image[i + 1][j - 1].rgbtRed +
                                       tmp_image[i + 1][j].rgbtRed + tmp_image[i + 1][j + 1].rgbtRed) / 9.0 + 0.5;
            }
        }
    }

    // Blur four coner pixels
    image[0][0].rgbtBlue = (tmp_image[0][0].rgbtBlue + tmp_image[0][1].rgbtBlue + tmp_image[1][0].rgbtBlue +
                            tmp_image[1][1].rgbtBlue) / 4.0 + 0.5;
    image[0][0].rgbtGreen = (tmp_image[0][0].rgbtGreen + tmp_image[0][1].rgbtGreen + tmp_image[1][0].rgbtGreen +
                             tmp_image[1][1].rgbtGreen) / 4.0 + 0.5;
    image[0][0].rgbtRed = (tmp_image[0][0].rgbtRed + tmp_image[0][1].rgbtRed + tmp_image[1][0].rgbtRed +
                           tmp_image[1][1].rgbtRed) / 4.0 + 0.5;

    image[0][width - 1].rgbtBlue = (tmp_image[0][width - 2].rgbtBlue + tmp_image[0][width - 1].rgbtBlue +
                                    tmp_image[1][width - 2].rgbtBlue + tmp_image[1][width - 1].rgbtBlue) / 4.0 + 0.5;
    image[0][width - 1].rgbtGreen = (tmp_image[0][width - 2].rgbtGreen + tmp_image[0][width - 1].rgbtGreen +
                                     tmp_image[1][width - 2].rgbtGreen + tmp_image[1][width - 1].rgbtGreen) / 4.0 + 0.5;
    image[0][width - 1].rgbtRed = (tmp_image[0][width - 2].rgbtRed + tmp_image[0][width - 1].rgbtRed +
                                   tmp_image[1][width - 2].rgbtRed + tmp_image[1][width - 1].rgbtRed) / 4.0 + 0.5;

    image[height - 1][0].rgbtBlue = (tmp_image[height - 2][0].rgbtBlue + tmp_image[height - 2][1].rgbtBlue +
                                     tmp_image[height - 1][0].rgbtBlue + tmp_image[height - 1][1].rgbtBlue) / 4.0 + 0.5;
    image[height - 1][0].rgbtGreen = (tmp_image[height - 2][0].rgbtGreen + tmp_image[height - 2][1].rgbtGreen +
                                      tmp_image[height - 1][0].rgbtGreen + tmp_image[height - 1][1].rgbtGreen) / 4.0 + 0.5;
    image[height - 1][0].rgbtRed = (tmp_image[height - 2][0].rgbtRed + tmp_image[height - 2][1].rgbtRed +
                                    tmp_image[height - 1][0].rgbtRed + tmp_image[height - 1][1].rgbtRed) / 4.0 + 0.5;

    image[height - 1][width - 1].rgbtBlue = (tmp_image[height - 2][width - 2].rgbtBlue + tmp_image[height - 2][width - 1].rgbtBlue +
                                            tmp_image[height - 1][width - 2].rgbtBlue + tmp_image[height - 1][width - 1].rgbtBlue) / 4.0 + 0.5;
    image[height - 1][width - 1].rgbtGreen = (tmp_image[height - 2][width - 2].rgbtGreen + tmp_image[height - 2][width - 1].rgbtGreen +
            tmp_image[height - 1][width - 2].rgbtGreen + tmp_image[height - 1][width - 1].rgbtGreen) / 4.0 + 0.5;
    image[height - 1][width - 1].rgbtRed = (tmp_image[height - 2][width - 2].rgbtRed + tmp_image[height - 2][width - 1].rgbtRed +
                                            tmp_image[height - 1][width - 2].rgbtRed + tmp_image[height - 1][width - 1].rgbtRed) / 4.0 + 0.5;

    // Blur top edge row of pixels
    for (int i = 1; i < width - 1; i++)
    {
        image[0][i].rgbtBlue = (tmp_image[0][i - 1].rgbtBlue + tmp_image[0][i].rgbtBlue + tmp_image[0][i + 1].rgbtBlue +
                                tmp_image[1][i - 1].rgbtBlue + tmp_image[1][i].rgbtBlue + tmp_image[1][i + 1].rgbtBlue) / 6.0 + 0.5;
        image[0][i].rgbtGreen = (tmp_image[0][i - 1].rgbtGreen + tmp_image[0][i].rgbtGreen + tmp_image[0][i + 1].rgbtGreen +
                                 tmp_image[1][i - 1].rgbtGreen + tmp_image[1][i].rgbtGreen + tmp_image[1][i + 1].rgbtGreen) / 6.0 + 0.5;
        image[0][i].rgbtRed = (tmp_image[0][i - 1].rgbtRed + tmp_image[0][i].rgbtRed + tmp_image[0][i + 1].rgbtRed +
                               tmp_image[1][i - 1].rgbtRed + tmp_image[1][i].rgbtRed + tmp_image[1][i + 1].rgbtRed) / 6.0 + 0.5;
    }

    // Blur bottom edge row of pixels
    for (int i = 1; i < width - 1; i++)
    {
        image[height - 1][i].rgbtBlue = (tmp_image[height - 2][i - 1].rgbtBlue + tmp_image[height - 2][i].rgbtBlue +
                                         tmp_image[height - 2][i + 1].rgbtBlue + tmp_image[height - 1][i - 1].rgbtBlue + tmp_image[height - 1][i].rgbtBlue +
                                         tmp_image[height - 1][i + 1].rgbtBlue) / 6.0 + 0.5;
        image[height - 1][i].rgbtGreen = (tmp_image[height - 2][i - 1].rgbtGreen + tmp_image[height - 2][i].rgbtGreen +
                                          tmp_image[height - 2][i + 1].rgbtGreen + tmp_image[height - 1][i - 1].rgbtGreen + tmp_image[height - 1][i].rgbtGreen +
                                          tmp_image[height - 1][i + 1].rgbtGreen) / 6.0 + 0.5;
        image[height - 1][i].rgbtRed = (tmp_image[height - 2][i - 1].rgbtRed + tmp_image[height - 2][i].rgbtRed +
                                        tmp_image[height - 2][i + 1].rgbtRed + tmp_image[height - 1][i - 1].rgbtRed + tmp_image[height - 1][i].rgbtRed +
                                        tmp_image[height - 1][i + 1].rgbtRed) / 6.0 + 0.5;
    }

    // Blur left edge column of pixels
    for (int i = 1; i < height - 1; i++)
    {
        image[i][0].rgbtBlue = (tmp_image[i - 1][0].rgbtBlue + tmp_image[i - 1][1].rgbtBlue + tmp_image[i][0].rgbtBlue +
                                tmp_image[i][1].rgbtBlue + tmp_image[i + 1][0].rgbtBlue + tmp_image[i + 1][1].rgbtBlue) / 6.0 + 0.5;
        image[i][0].rgbtGreen = (tmp_image[i - 1][0].rgbtGreen + tmp_image[i - 1][1].rgbtGreen + tmp_image[i][0].rgbtGreen +
                                 tmp_image[i][1].rgbtGreen + tmp_image[i + 1][0].rgbtGreen + tmp_image[i + 1][1].rgbtGreen) / 6.0 + 0.5;
        image[i][0].rgbtRed = (tmp_image[i - 1][0].rgbtRed + tmp_image[i - 1][1].rgbtRed + tmp_image[i][0].rgbtRed +
                               tmp_image[i][1].rgbtRed + tmp_image[i + 1][0].rgbtRed + tmp_image[i + 1][1].rgbtRed) / 6.0 + 0.5;
    }

    // Blur right edge column of pixels
    for (int i = 1; i < height - 1; i++)
    {
        image[i][width - 1].rgbtBlue = (tmp_image[i - 1][width - 2].rgbtBlue + tmp_image[i - 1][width - 1].rgbtBlue +
                                        tmp_image[i][width - 2].rgbtBlue + tmp_image[i][width - 1].rgbtBlue + tmp_image[i + 1][width - 2].rgbtBlue +
                                        tmp_image[i + 1][width - 1].rgbtBlue) / 6.0 + 0.5;
        image[i][width - 1].rgbtGreen = (tmp_image[i - 1][width - 2].rgbtGreen + tmp_image[i - 1][width - 1].rgbtGreen +
                                         tmp_image[i][width - 2].rgbtGreen + tmp_image[i][width - 1].rgbtGreen + tmp_image[i + 1][width - 2].rgbtGreen +
                                         tmp_image[i + 1][width - 1].rgbtGreen) / 6.0 + 0.5;
        image[i][width - 1].rgbtRed = (tmp_image[i - 1][width - 2].rgbtRed + tmp_image[i - 1][width - 1].rgbtRed +
                                       tmp_image[i][width - 2].rgbtRed + tmp_image[i][width - 1].rgbtRed + tmp_image[i + 1][width - 2].rgbtRed +
                                       tmp_image[i + 1][width - 1].rgbtRed) / 6.0 + 0.5;
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height + 2][width + 2];
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j ++)
        {
            tmp_image[i][j].rgbtBlue = 0;
            tmp_image[i][j].rgbtGreen = 0;
            tmp_image[i][j].rgbtRed = 0;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp_image[i + 1][j + 1] = image[i][j];
        }
    }

    // Calculate square root of (Gx^2 + Gy^2) in each channel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int tmp_rgbtBlueGx = (- tmp_image[i][j].rgbtBlue + tmp_image[i][j + 2].rgbtBlue - 2 * tmp_image[i + 1][j].rgbtBlue +
                                  2 * tmp_image[i + 1][j + 2].rgbtBlue - tmp_image[i + 2][j].rgbtBlue + tmp_image[i + 2][j + 2].rgbtBlue);
            int tmp_rgbtBlueGy = (- tmp_image[i][j].rgbtBlue + tmp_image[i + 2][j].rgbtBlue - 2 * tmp_image[i][j + 1].rgbtBlue +
                                  2 * tmp_image[i + 2][j + 1].rgbtBlue - tmp_image[i][j + 2].rgbtBlue + tmp_image[i + 2][j + 2].rgbtBlue);
            float tmp_rgbtBlueG = sqrt(pow(tmp_rgbtBlueGx, 2) + pow(tmp_rgbtBlueGy, 2)) + 0.5;
            image[i][j].rgbtBlue = (tmp_rgbtBlueG > 255) ? 255 : (BYTE)tmp_rgbtBlueG;

            int tmp_rgbtGreenGx = (- tmp_image[i][j].rgbtGreen + tmp_image[i][j + 2].rgbtGreen - 2 * tmp_image[i + 1][j].rgbtGreen +
                                   2 * tmp_image[i + 1][j + 2].rgbtGreen - tmp_image[i + 2][j].rgbtGreen + tmp_image[i + 2][j + 2].rgbtGreen);
            int tmp_rgbtGreenGy = (- tmp_image[i][j].rgbtGreen + tmp_image[i + 2][j].rgbtGreen - 2 * tmp_image[i][j + 1].rgbtGreen +
                                   2 * tmp_image[i + 2][j + 1].rgbtGreen - tmp_image[i][j + 2].rgbtGreen + tmp_image[i + 2][j + 2].rgbtGreen);
            float tmp_rgbtGreenG = sqrt(pow(tmp_rgbtGreenGx, 2) + pow(tmp_rgbtGreenGy, 2)) + 0.5;
            image[i][j].rgbtGreen = (tmp_rgbtGreenG > 255) ? 255 : (BYTE)tmp_rgbtGreenG;

            int tmp_rgbtRedGx = (- tmp_image[i][j].rgbtRed + tmp_image[i][j + 2].rgbtRed - 2 * tmp_image[i + 1][j].rgbtRed +
                                 2 * tmp_image[i + 1][j + 2].rgbtRed - tmp_image[i + 2][j].rgbtRed + tmp_image[i + 2][j + 2].rgbtRed);
            int tmp_rgbtRedGy = (- tmp_image[i][j].rgbtRed + tmp_image[i + 2][j].rgbtRed - 2 * tmp_image[i][j + 1].rgbtRed +
                                 2 * tmp_image[i + 2][j + 1].rgbtRed - tmp_image[i][j + 2].rgbtRed + tmp_image[i + 2][j + 2].rgbtRed);
            float tmp_rgbtRedG = sqrt(pow(tmp_rgbtRedGx, 2) + pow(tmp_rgbtRedGy, 2)) + 0.5;
            image[i][j].rgbtRed = (tmp_rgbtRedG > 255) ? 255 : (BYTE)tmp_rgbtRedG;
        }
    }

    return;
}
