#include <cs50.h>
#include <stdio.h>
#include <math.h>

#define MAX_CARD_NUMBER_LEN 16
#define NULL_TERMINATION -1

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

int get_array_length(int *p_arr_num)
{
    int len = 0;

    for (int i = 0; i < MAX_CARD_NUMBER_LEN; i++)
    {
        if (p_arr_num[i] != NULL_TERMINATION)
        {
            len++;
        }
        else
        {
            break;
        }
    }

    return len;
}
void convert_int_into_array(int *p_arr_num, unsigned int num)
{
    long len = (long)floor(log10((float)num)) + 1;
    int i = len - 1;

    do {
        p_arr_num[i] = (unsigned)num % 10;
        num /= 10;
        i--;
    } while (num != 0);

    /* Append null termination at last used index */
    p_arr_num[len] = NULL_TERMINATION;

    #if 1
    printf("card number: %d\n", num);
    for (i = 0; i < MAX_CARD_NUMBER_LEN; i++)
    {
        if (p_arr_num[i] != NULL_TERMINATION)
        {
            printf("index: %d - value: %d\n", i, p_arr_num[i]);
        }
        else
        {
            break;
        }
    }
    #endif
}

bool check_valid_card_number(int *p_arr_num)
{
    /* Do nothing */
    return true;
}

bool check_card_number_amex(int *p_arr_num)
{
    const int expected_len = 15;
    const int valid_digits[] = {31, 37};

    bool match = false;

    /* Check for expected card number length */
    match = get_array_length(p_arr_num) == expected_len;
    printf("len = %d\n", get_array_length(p_arr_num));

    return match;
}

bool check_card_number_mastercard(int *p_arr_num)
{
    const int expected_len = 16;
    const int valid_digits[] = {51, 52, 53, 54, 55};

    bool match = false;

    /* Check for expected card number length */
    match = get_array_length(p_arr_num) == expected_len;

    return match;
}

bool check_card_number_visa(int *p_arr_num)
{
    const int expected_len_lo = 13;
    const int expected_len_hi = 16;
    const int valid_digits[] = {4};

    return false;
}

int validate_card_number(int num)
{
    int state;
    int arr_num[MAX_CARD_NUMBER_LEN];

    convert_int_into_array(&arr_num[0], num);

    if (check_valid_card_number(&arr_num[0]))
    {
        if (check_card_number_amex(&arr_num[0]))
        {
            state = AMEX;
        }
        else if (check_card_number_mastercard(&arr_num[0]))
        {
            state = MASTERCARD;
        }
        else if (check_card_number_visa(&arr_num[0]))
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