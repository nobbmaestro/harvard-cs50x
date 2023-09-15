#include "helpers.h"
#include "math.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

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
    int mid = (int) (width / 2);
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
            if (((avg.rgbtBlue >= 0x00) && (avg.rgbtBlue <= 0xFF)) && ((avg.rgbtGreen >= 0x00) && (avg.rgbtGreen <= 0xFF)) &&
                ((avg.rgbtRed >= 0x00) && (avg.rgbtRed <= 0xFF)))
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

/* Helper functions */
int calculate_pixel_average(RGBTRIPLE pixel)
{
    return round((float) (pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed) / 3.0F);
}

RGBTRIPLE calculate_neighbor_average(int index_h, int index_w, int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE average;
    int blue = 0x00;
    int green = 0x00;
    int red = 0x00;

    /* Obtain the lower and upper index limits */
    int index_h_lo = (index_h > 0) ? (index_h - 1) : 0;
    int index_w_lo = (index_w > 0) ? (index_w - 1) : 0;
    int index_h_hi = (index_h < (height - 1)) ? (index_h + 1) : (height - 1);
    int index_w_hi = (index_w < (width - 1)) ? (index_w + 1) : (width - 1);

    int elements = 0;
    for (int i = index_h_lo; i <= index_h_hi; i++)
    {
        for (int j = index_w_lo; j <= index_w_hi; j++)
        {
            blue += image[i][j].rgbtBlue;
            green += image[i][j].rgbtGreen;
            red += image[i][j].rgbtRed;
            elements++;
        }
    }
    average.rgbtBlue = round((float) blue / (float) elements);
    average.rgbtGreen = round((float) green / (float) elements);
    average.rgbtRed = round((float) red / (float) elements);

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
    int gx_kernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy_kernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE weighted_sum;
    int gx_blue = 0x00, gy_blue = 0x00;
    int gx_green = 0x00, gy_green = 0x00;
    int gx_red = 0x00, gy_red = 0x00;

    for (int i = 0; i <= 2; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            bool in_range;
            int curr_index_h = index_h - 1 + i;
            int curr_index_w = index_w - 1 + j;

            /* Check whether current index is out-of-bounds */
            in_range = true;
            in_range &= (curr_index_h) >= 0;
            in_range &= (curr_index_w) >= 0;
            in_range &= (curr_index_h) < height;
            in_range &= (curr_index_w) < width;

            /* Obtain current pixel value. If not in range, set to zero */
            int curr_blue = (in_range) ? image[curr_index_h][curr_index_w].rgbtBlue : 0x00;
            int curr_green = (in_range) ? image[curr_index_h][curr_index_w].rgbtGreen : 0x00;
            int curr_red = (in_range) ? image[curr_index_h][curr_index_w].rgbtRed : 0x00;

            /* Calculate the weighted sum for x-direction */
            gx_blue += curr_blue * gx_kernel[i][j];
            gx_green += curr_green * gx_kernel[i][j];
            gx_red += curr_red * gx_kernel[i][j];

            /* Calculate the weighted sum for y-direction */
            gy_blue += curr_blue * gy_kernel[i][j];
            gy_green += curr_green * gy_kernel[i][j];
            gy_red += curr_red * gy_kernel[i][j];
        }
    }

    /* Calculate sqrt of Gx^2 + Gy^2 for each color */
    int blue = (int) round(sqrt(pow((float) gx_blue, 2.0F) + pow((float) gy_blue, 2.0F)));
    int green = (int) round(sqrt(pow((float) gx_green, 2.0F) + pow((float) gy_green, 2.0F)));
    int red = (int) round(sqrt(pow((float) gx_red, 2.0F) + pow((float) gy_red, 2.0F)));

    /* Ensure max value of 0xFF (255) */
    weighted_sum.rgbtBlue = (blue <= 0xFF) ? blue : 0xFF;
    weighted_sum.rgbtGreen = (green <= 0xFF) ? green : 0xFF;
    weighted_sum.rgbtRed = (red <= 0xFF) ? red : 0xFF;

    return weighted_sum;
}