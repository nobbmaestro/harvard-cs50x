#include "helpers.h"
#include "bmp.h"

#define DEFAULT_COLOR_HEX 0x00E8C6

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // if (image[h][w] == 0x0)
            // {
            //     image[h][w] = rgbtBlue;
            // }
            // else
            // {
            //     /* Do nothing */
            // }
        }
    }
}
