#include <cs50.h>
#include <stdio.h>

int get_input(void)
{
    int n = get_int("Height: ");
    return n;
}

void generate_output(int height)
{
    int row, chr;
    for (row = 0; row < height; row++)
    {
        char output[height];
        chr = 0;

        while (chr <= height)
        {
           output[chr] = (chr > row) ? '0' : '#';
           chr++;
        }
        output[++chr] = ' ';

        printf("%s\n", output);
    }
}

int main(void)
{
    int height;
    height = get_input();
    generate_output(height);
}
