#include <cs50.h>
#include <stdio.h>

enum CardState {AMEX, MASTERCARD, VISA, INVALID};

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

const char* get_state_name(enum CardState state)
{
    switch (state)
    {
        case AMEX:          return "AMEX";
        case MASTERCARD:    return "MASTERCARD";
        case VISA:          return "VISA";
        case INVALID:       return "INVALID";
    }
}

int main(void)
{
    int num, state;
    num = get_card_number();
    state = validate_card_number(num);

    printf("%s\n", get_state_name(state));
}