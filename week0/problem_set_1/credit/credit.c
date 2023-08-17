#include <cs50.h>
#include <stdio.h>

enum card_state {AMEX, MASTERCARD, VISA, INVALID};

int get_card_number(void)
{
    int num = 0;
    while (num <= 0)
    {
        num = get_int("Number: ");
    }
    return num;
}

int validate_card_number(void)
{
    /* Do nothing */
    return INVALID;
}

int main(void)
{
    int card_num, card_state;
    card_num = get_card_number();
    card_state = validate_card_number(card_num);

    printf()
}