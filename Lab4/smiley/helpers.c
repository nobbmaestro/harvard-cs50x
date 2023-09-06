#include "helpers.h"

#define RGBTb 0x00
#define RGBTg 0xE8
#define RGBTr 0xC6

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;

    tmp.rgbtBlue  = 0x0;
    tmp.rgbtGreen = 0x0;
    tmp.rgbtRed   = 0x0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((image[i][j].rgbtBlue == tmp.rgbtBlue) &&
                (image[i][j].rgbtGreen == tmp.rgbtGreen) &&
                (image[i][j].rgbtRed == tmp.rgbtRed))
            {
                image[i][j].rgbtBlue = RGBTb;
                image[i][j].rgbtGreen = RGBTg;
                image[i][j].rgbtRed = RGBTr;
            }
            else
            {
                /* Do nothing */
            }
        }
    }
}
