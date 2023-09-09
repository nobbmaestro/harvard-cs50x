#include "helpers.h"
#include "stdlib.h"
#include "math.h"
#include "stdio.h"

/* (Helper) Function Prototypes */
int calculate_pixel_average(RGBTRIPLE pixel);
void copy_image(int height, int width, RGBTRIPLE src[height][width], RGBTRIPLE dst[height][width]);
RGBTRIPLE calculate_neighbor_average(int index_h, int index_w, int height, int width, RGBTRIPLE image[height][width]);
RGBTRIPLE calculate_weighted_sum(int index_h, int index_w, int height, int width, RGBTRIPLE image[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = calculate_pixel_average(image[i][j]);

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

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    /* Create copy of the image */
    RGBTRIPLE(*tmp)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    copy_image(height, width, image, tmp);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE avg = calculate_neighbor_average(i, j, height, width, tmp);

            /* Apply blur only on passed sanity check */
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
    /* Free memory for image copy */
    free(tmp);
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    /* Create copy of the image */
    RGBTRIPLE(*tmp)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    copy_image(height, width, image, tmp);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = calculate_weighted_sum(i, j, height, width, tmp);
        }
    }
    /* Free memory for image copy */
    free(tmp);
}

void local_main()
{
    int h = 3, w = 3;
    RGBTRIPLE image[h][w];

    image[0][0].rgbtBlue  = 0;
    image[0][0].rgbtGreen = 10;
    image[0][0].rgbtRed   = 25;

    image[0][1].rgbtBlue  = 0;
    image[0][1].rgbtGreen = 10;
    image[0][1].rgbtRed   = 30;

    image[0][2].rgbtBlue  = 40;
    image[0][2].rgbtGreen = 60;
    image[0][2].rgbtRed   = 80;

    image[1][0].rgbtBlue  = 20;
    image[1][0].rgbtGreen = 30;
    image[1][0].rgbtRed   = 90;

    image[1][1].rgbtBlue  = 30;
    image[1][1].rgbtGreen = 40;
    image[1][1].rgbtRed   = 100;

    image[1][2].rgbtBlue  = 80;
    image[1][2].rgbtGreen = 70;
    image[1][2].rgbtRed   = 90;

    image[2][0].rgbtBlue  = 20;
    image[2][0].rgbtGreen = 20;
    image[2][0].rgbtRed   = 40;

    image[2][1].rgbtBlue  = 30;
    image[2][1].rgbtGreen = 10;
    image[2][1].rgbtRed   = 30;

    image[2][2].rgbtBlue  = 50;
    image[2][2].rgbtGreen = 40;
    image[2][2].rgbtRed   = 10;

    int i = 1;
    int j = 2;
    RGBTRIPLE sum = calculate_weighted_sum(i, j, h, w, image);
    printf("\nsum(%d, %d) -> (%d, %d, %d)\n", i, j, sum.rgbtBlue, sum.rgbtGreen, sum.rgbtRed);
}

/* Helper functions */
int calculate_pixel_average(RGBTRIPLE pixel)
{
    return round((float)(pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed)/ 3.0F);
}

RGBTRIPLE calculate_neighbor_average(int index_h, int index_w, int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE average;
    int blue  = 0x00;
    int green = 0x00;
    int red   = 0x00;

    /* Obtain the lower and upper index limits */
    int index_h_lo = (index_h > 0) ? (index_h - 1) : 0;
    int index_w_lo = (index_w > 0) ? (index_w - 1) : 0;
    int index_h_hi = (index_h < (height - 1)) ? (index_h + 1) : (height - 1);
    int index_w_hi = (index_w < (width - 1))  ? (index_w + 1) : (width - 1);

    int elements = 0;
    for (int i = index_h_lo; i <= index_h_hi; i++)
    {
        for (int j = index_w_lo; j <= index_w_hi; j++)
        {
            blue  += image[i][j].rgbtBlue;
            green += image[i][j].rgbtGreen;
            red   += image[i][j].rgbtRed;
            elements++;
        }
    }
    average.rgbtBlue  = round((float)blue  / (float)elements);
    average.rgbtGreen = round((float)green / (float)elements);
    average.rgbtRed   = round((float)red   / (float)elements);

    return average;
}

void copy_image(int height, int width, RGBTRIPLE src[height][width], RGBTRIPLE dst[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            /* Copy source to destination */
            dst[i][j] = src[i][j];
        }
    }
}

RGBTRIPLE calculate_weighted_sum(int index_h, int index_w, int height, int width, RGBTRIPLE image[height][width])
{
    int gx_kernel[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int gy_kernel[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

    RGBTRIPLE weighted_sum;
    int gx_blue  = 0x00, gy_blue  = 0x00;
    int gx_green = 0x00, gy_green = 0x00;
    int gx_red   = 0x00, gy_red   = 0x00;

    /* Obtain the lower and upper index limits */
    int index_h_lo = (index_h > 0) ? (index_h - 1) : 0;
    int index_w_lo = (index_w > 0) ? (index_w - 1) : 0;
    int index_h_hi = (index_h < (height - 1)) ? (index_h + 1) : (height - 1);
    int index_w_hi = (index_w < (width - 1))  ? (index_w + 1) : (width - 1);

    for (int i = index_h_lo; i <= index_h_hi; i++)
    {
        for (int j = index_w_lo; j <= index_w_hi; j++)
        {
            /* Calculate the weighted sum for x-direction */
            gx_blue  += image[index_h_lo+i][index_w_lo+j].rgbtBlue  * gx_kernel[i][j];
            gx_green += image[index_h_lo+i][index_w_lo+j].rgbtGreen * gx_kernel[i][j];
            gx_red   += image[index_h_lo+i][index_w_lo+j].rgbtRed   * gx_kernel[i][j];

            /* Calculate the weighted sum for y-direction */
            gy_blue  += image[index_h_lo+i][index_w_lo+j].rgbtBlue  * gy_kernel[i][j];
            gy_green += image[index_h_lo+i][index_w_lo+j].rgbtGreen * gy_kernel[i][j];
            gy_red   += image[index_h_lo+i][index_w_lo+j].rgbtRed   * gy_kernel[i][j];
        }
    }
    /* Calculate sqrt of Gx^2 + Gy^2 for each color */
    weighted_sum.rgbtBlue  = (int)round( sqrt( pow((float)gx_blue,  2.0F) + pow((float)gy_blue,  2.0F) ));
    weighted_sum.rgbtGreen = (int)round( sqrt( pow((float)gx_green, 2.0F) + pow((float)gy_green, 2.0F) ));
    weighted_sum.rgbtRed   = (int)round( sqrt( pow((float)gx_red,   2.0F) + pow((float)gy_red,   2.0F) ));

    /* Ensure max value of 0xFF (255) */
    weighted_sum.rgbtBlue  = weighted_sum.rgbtBlue  > 0xFF ? 0xFF : weighted_sum.rgbtBlue;
    weighted_sum.rgbtGreen = weighted_sum.rgbtGreen > 0xFF ? 0xFF : weighted_sum.rgbtGreen;
    weighted_sum.rgbtRed   = weighted_sum.rgbtRed   > 0xFF ? 0xFF : weighted_sum.rgbtRed;

    return weighted_sum;
}