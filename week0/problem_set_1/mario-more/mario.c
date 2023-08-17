#include <cs50.h>
#include <stdio.h>

int get_input(void)
{
    int n = get_int("Height: ");
    return n;
}

void generate_left_at_index(int row, int height)
{
    int i, j;
    int size = (2*height) + 1;
    char output[size];

    for (i = 0; i < height; i++)
    {
        output[i] = (i >= (height - row - 1)) ? '#' : ' ';
    }
    output[++i] = ' ';
    for (j = i; j > 0; j--)
    {
        output[i++] = output[j];
        i++;
        // printf("i = %d, output[i] = %d --- j = %d, output[j] = %d\n", i, j, output[i], output[j]);
        printf("i = %d, j = %d\n", i, j);
        printf("output[i] = %c, output[j] = %c\n", output[i], output[j]);
    }


    printf("--> %s\n", output);
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
