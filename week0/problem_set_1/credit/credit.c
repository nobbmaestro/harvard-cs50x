#include <cs50.h>
#include <stdio.h>
#include <math.h>

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

int * convert_int_into_array(unsigned int num)
{
    int len = (int)floor(log10((float)num)) + 1;
    int * arr[len];
    int i = 0;

    do {
        arr[i] = (unsigned)num % 10;
        num /= 10;
        i++;
    } while (num != 0);

    return arr;
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

    num = get_card_number();

    int arr = convert_int_into_array(num);
    printf("%d\n", arr);

    state = validate_card_number(num);

    printf("%s\n", get_state_name(state));
}