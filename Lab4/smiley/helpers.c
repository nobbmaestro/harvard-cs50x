#include "helpers.h"

#define RGBTb 0x00
#define RGBTg 0xE8
#define RGBTr 0xC6

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((image[i][j].rgbtBlue == 0x00) && (image[i][j].rgbtGreen == 0x00) && (image[i][j].rgbtRed == 0x00))
            {
                image[i][j].rgbtBlue  = RGBTb;
                image[i][j].rgbtGreen = RGBTg;
                image[i][j].rgbtRed   = RGBTr;
            }
            else
            {
                /* Do nothing */
            }
        }
    }
}
