#include "helpers.h"
#include "math.h"
#include "stdio.h"

int average_rgbt(int blue, int green, int red)
{
    return round((float)(blue + green + red)/ 3.0F);
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = average_rgbt(image[i][j].rgbtBlue, image[i][j].rgbtGreen, image[i][j].rgbtRed);

            /* Apply grayscale only on passed sanity check */
            if ((avg > 0x00) && (avg < 0xFF))
            {
                image[i][j].rgbtBlue = avg;
                image[i][j].rgbtGreen = avg;
                image[i][j].rgbtRed = avg;
            }
            else
            {
                /* Do nothing */
            }
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mid = (int)(width / 2);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < mid; j++)
        {
            if (j < mid)
            {
                RGBTRIPLE tmp;
                int rj = width - j - 1;

                tmp = image[i][rj];
                image[i][rj] = image[i][j];
                image[i][j] = tmp;
            }
            else
            {
                /* Do nothing */
            }
        }
    }
}

RGBTRIPLE get_neighbor_average(int index_h, int index_w, int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE average;
    average.rgbtBlue  = 0x00;
    average.rgbtGreen = 0x00;
    average.rgbtRed   = 0x00;

    int index_h_lo = (index_h > 0) ? (index_h - 1) : 0;
    int index_w_lo = (index_w > 0) ? (index_w - 1) : 0;
    int index_h_hi = (index_h < (height - 1)) ? (index_h + 1) : height;
    int index_w_hi = (index_w < (width - 1)) ? (index_w + 1) : width;

    int elements = 0;
    for (int i = index_h_lo; i < index_h_hi; i++)
    {
        for (int j = index_w_lo; j < index_w_hi; j++)
        {
            average.rgbtBlue  += image[i][j].rgbtBlue;
            average.rgbtGreen += image[i][j].rgbtGreen;
            average.rgbtRed   += image[i][j].rgbtRed;
            elements++;
        }
    }
    average.rgbtBlue  /= elements;
    average.rgbtGreen /= elements;
    average.rgbtRed   /= elements;

    return average;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE avg = get_neighbor_average(i, j, height, width, image);
            /* Apply blue only on passed sanity check */
            if (((avg.rgbtBlue  >= 0x00) && (avg.rgbtBlue  <= 0xFF)) &&
                ((avg.rgbtGreen >= 0x00) && (avg.rgbtGreen <= 0xFF)) &&
                ((avg.rgbtRed   >= 0x00) && (avg.rgbtRed   <= 0xFF)))
            {
                image[i][j] = avg;
            }
            else
            {
                /* Do nothing */
            }
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
