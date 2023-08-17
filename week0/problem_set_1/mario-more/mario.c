#include <cs50.h>
#include <stdio.h>

int get_input(void)
{
    int n = get_int("Height: ");
    return n;
}

void generate_row(int row, int height)
{
    int i, j;
    int size = (2*height) + 1;
    char output[size];
    char solid = '#';
    char empty = ' ';

    /* Generate the left-side half */
    for (i = 0; i < height; i++)
    {
        output[i] = (i >= (height - row - 1)) ? solid : empty;
    }

    /* Add the middle space */
    output[i++] = empty;

    /* Generate the right-side half */
    for (j = i-1; j >= 0; j--)
    {
        output[i++] = output[j];
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
