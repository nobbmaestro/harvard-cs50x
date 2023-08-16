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
    for (row = 1; row < height; row++)
    {
        char output[] = "";
        for (chr = 1; chr < height; chr++)
        {
            output[chr] = (chr < row) ? '#' : ' ';
        }
        printf("%s", output);
    }
}

int main(void)
{
    int height;
    height = get_input();
    generate_output(height);
}
