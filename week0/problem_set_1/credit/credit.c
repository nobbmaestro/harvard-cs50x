#include <cs50.h>
#include <stdio.h>

int get_card_number(void)
{
    int num = 0;
    while (num <= 0)
    {
        num = get_int("Number: ");
    }
    return num;
}

bool validate_card_number(void)
{
    /* Do nothing */
    return false;
}

int main(void)
{
    int num;
    num = get_card_number();
}