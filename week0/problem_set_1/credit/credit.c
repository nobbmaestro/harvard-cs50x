#include <cs50.h>
#include <stdio.h>

define MAX_CARD_NUMBER_LEN 16

enum CardState {AMEX, MASTERCARD, VISA, INVALID};

long get_card_number(void)
{
    long num = 0;
    while (num <= 0)
    {
        num = get_long("Number: ");
    }
    return num;
}

bool check_valid_card_number(int num)
{
    /* Do nothing */
    return false;
}

bool check_card_number_amex(int num)
{
    /* Do nothing */
    return false;
}

bool check_card_number_mastercard(int num)
{
    /* Do nothing */
    return false;
}

bool check_card_number_visa(int num)
{
    /* Do nothing */
    return false;
}

int validate_card_number(int num)
{
    int state;

    if (check_valid_card_number(num))
    {
        if (check_card_number_amex(num))
        {
            state = AMEX;
        }
        else if (check_card_number_mastercard(num))
        {
            state = MASTERCARD;
        }
        else if (check_card_number_visa(num))
        {
            state = VISA;
        }
        else
        {
            state = -1;
        }
    }
    else
    {
        state = INVALID;
    }

    return state;
}

const char* get_state_name(enum CardState state)
{
    switch (state)
    {
        case AMEX:          return "AMEX";
        case MASTERCARD:    return "MASTERCARD";
        case VISA:          return "VISA";
        case INVALID:       return "INVALID";
        default:            return "N/A";
    }
}

int main(void)
{
    long num;
    int state;
    int num_array[MAX_CARD_NUMBER_LEN];

    num = get_card_number();
    state = validate_card_number(num);

    printf("%s\n", get_state_name(state));
}