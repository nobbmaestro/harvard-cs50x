#include <cs50.h>
#include <stdio.h>

enum card_state{'AMEX', 'MASTERCARD', 'VISA', 'INVALID'}

int get_card_number(void)
{
    int num = 0;
    while (num <= 0)
    {
        num = get_int("Number: ");
    }
    return num;
}

card_state validate_card_number(void)
{
    /* Do nothing */
    return card_state.INVALID;
}

int main(void)
{
    int num;
    num = get_card_number();
}