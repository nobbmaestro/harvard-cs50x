#include "helpers.h"
#include "math.h"

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

int main()
{
    RGBTRIPLE image;
    image[0][0] = 0;
    image[0][1] = 10;
    image[0][2] = 20;
    image[1][0] = 30;
    image[1][1] = 40;
    image[1][2] = 50;
    image[2][0] = 60;
    image[2][1] = 70;
    image[2][2] = 80;

    reflect(3, 3, image);

    for (int i = 0, i < 3; i++)
    {
        printf("row: %d \t (%d, %d, %d)\n", i, image[i][0], image[i][1], image[i][2])
    }
}