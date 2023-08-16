#include <cs50.h>
#include <stdio.h>

int get_input(void)
{
    int n = get_int("Height: ");
    return n;
}

void generate_left_at_index(int row, int height)
{
    int chr;
    char output[height];

    for (chr = 0; chr < height; chr++)
    {
        output[chr] = (chr >= (height - row - 1)) ? '#' : ' ';
    }

    printf("%s\n", output);
}

void generate_output(int height)
{
    int row;
    for (row=0; row<height; row++)
    {
        generate_left_at_index(row, height);
    }
}

int main(void)
{
    int height;
    height = get_input();
    generate_output(height);
}
