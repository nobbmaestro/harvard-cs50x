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
    int mid = (int)(height / 2);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i < mid)
            {
                RGBTRIPLE tmp;
                tmp = image[height - i - 1][j];
                image[height - i - 1][j] = image[i][j];
                image[i][j]  = tmp;
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
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

void local_main()
{
    RGBTRIPLE image[3][3];

    /* Row 0 */
    image[0][0].rgbtBlue  = 10;
    image[0][0].rgbtGreen = 10;
    image[0][0].rgbtRed   = 10;

    image[0][1].rgbtBlue  = 20;
    image[0][1].rgbtGreen = 20;
    image[0][1].rgbtRed   = 20;

    image[0][2].rgbtBlue  = 30;
    image[0][2].rgbtGreen = 30;
    image[0][2].rgbtRed   = 30;

    /* Row 1 */
    image[1][0].rgbtBlue  = 110;
    image[1][0].rgbtGreen = 110;
    image[1][0].rgbtRed   = 110;

    image[1][1].rgbtBlue  = 120;
    image[1][1].rgbtGreen = 120;
    image[1][1].rgbtRed   = 120;

    image[1][2].rgbtBlue  = 130;
    image[1][2].rgbtGreen = 130;
    image[1][2].rgbtRed   = 130;

    /* Row 2 */
    image[2][0].rgbtBlue  = 210;
    image[2][0].rgbtGreen = 210;
    image[2][0].rgbtRed   = 210;

    image[2][1].rgbtBlue  = 220;
    image[2][1].rgbtGreen = 220;
    image[2][1].rgbtRed   = 220;

    image[2][2].rgbtBlue  = 230;
    image[2][2].rgbtGreen = 230;
    image[2][2].rgbtRed   = 230;

    reflect(3, 3, image);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("(%d, %d): %d %d %d\n", i, j, image[i][j].rgbtBlue, image[i][j].rgbtGreen, image[i][j].rgbtRed);
        }
    }
}