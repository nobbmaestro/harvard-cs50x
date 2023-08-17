#include <cs50.h>
#include <stdio.h>
#include <math.h>

#define MAX_CARD_NUMBER_LEN 16

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

void convert_int_into_array(char *p_dst_buffer, unsigned int num)
{
    int len = (int)floor(log10((float)num)) + 1;
    int arr[len];
    int i = len - 1;

    do {
        arr[i] = (unsigned)num % 10;
        num /= 10;
        i--;
    } while (num != 0);

    for (i = 0; i < len; i++)
    {
        printf("index: %d - value: %d\n", i, arr[i]);
    }
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
    int arr_num[MAX_CARD_NUMBER_LEN];

    convert_int_into_array(&arr_num);

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

    num = get_card_number();
    state = validate_card_number(num);

    printf("%s\n", get_state_name(state));
}