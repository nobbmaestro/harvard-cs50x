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
                tmp.rgbtBlue  = image[height - i][j].rgbtBlue;
                tmp.rgbtGreen = image[height - i][j].rgbtGreen;
                tmp.rgbtRed   = image[height - i][j].rgbtRed;

                image[height - i][j].rgbtBlue  = image[i][j].rgbtBlue;
                image[height - i][j].rgbtGreen = image[i][j].rgbtGreen;
                image[height - i][j].rgbtRed   = image[i][j].rgbtRed;

                image[i][j].rgbtBlue  = tmp.rgbtBlue;
                image[i][j].rgbtGreen = tmp.rgbtGreen;
                image[i][j].rgbtRed   = tmp.rgbtRed;
            }
            else
            {
                break;
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
    image[0][0].rgbtBlue = 0;
    image[0][0].rgbtGreen = 0;
    image[0][0].rgbtRed = 0;

    image[0][1].rgbtBlue = 10;
    image[0][1].rgbtGreen = 10;
    image[0][1].rgbtRed = 10;

    image[0][2].rgbtBlue = 20;
    image[0][2].rgbtGreen = 20;
    image[0][2].rgbtRed = 20;

    /* Row 1 */
    image[1][0].rgbtBlue = 30;
    image[1][0].rgbtGreen = 30;
    image[1][0].rgbtRed = 30;

    image[1][1].rgbtBlue = 40;
    image[1][1] .rgbtGreen= 40;
    image[1][1].rgbtRed = 40;

    image[1][2].rgbtBlue = 50;
    image[1][2].rgbtGreen = 50;
    image[1][2].rgbtRed = 50;

    /* Row 2 */
    image[2][0].rgbtBlue = 60;
    image[2][0].rgbtGreen = 60;
    image[2][0].rgbtRed = 60;

    image[2][1].rgbtBlue = 70;
    image[2][1].rgbtGreen = 70;
    image[2][1].rgbtRed = 70;

    image[2][2].rgbtBlue = 80;
    image[2][2].rgbtGreen = 80;
    image[2][2].rgbtRed = 80;

    reflect(3, 3, image);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("(%d, %d): %d %d %d\n", i, j, image[i][j].rgbtBlue, image[i][j].rgbtGreen, image[i][j].rgbtRed);
        }
    }
}