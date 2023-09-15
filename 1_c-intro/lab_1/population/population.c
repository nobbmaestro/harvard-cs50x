#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n_start, n_end, n_years = 0;

    // TODO: Prompt for start size
    do
    {
        n_start = get_int("Start size: ");
    }
    while (n_start < 9);

    // TODO: Prompt for end size
    do
    {
        n_end = get_int("End size: ");
    }
    while (n_end < n_start);

    // TODO: Calculate number of years until we reach threshold
    int tmp = n_start;
    while (tmp < n_end)
    {
        tmp = tmp + (int) (tmp / 3) - (int) (tmp / 4);
        /* printf("Temp population: %d\n", tmp); */
        n_years++;
    }

    // TODO: Print number of years
    printf("Years: %d\n", n_years);
}

