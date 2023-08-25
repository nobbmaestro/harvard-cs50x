#include <cs50.h>
#include <stdio.h>
#include <string.h>

/* Function prototypes */
string get_text_input(void);
bool validate_text_input(string text);
bool check_for_start_end_spaces(string text);
bool check_for_multiple_spaces(string text);

int count_letters(string text);
int count_sentences(string text);
int count_words(string text);

float calculate_coleman_liau_index(float L, float S);
float calculate_avg_num_letters_per_words(int letters, int words);
float calculate_avg_num_sentences_per_words(int senteces, int words);

/* Main code */
float calculate_coleman_liau_index(float L, float S)
{
    /*  L - average number of letters per 100 words
        S - average number of sentences per 100 words.  */
    float index = (0.058 * L) - (0.296 * S) - 15.8;
    return index;
}

string get_text_input(void)
{
    string text;
    do
    {
        text = get_string("Text: ");
    }
    while (!validate_text_input(text));

    return text;
}

bool check_for_start_end_spaces(string text)
{
    int last_chr = strlen(text) - 1;
    return (text[0] != ' ') && (text[last_chr] != ' ');
}

bool check_for_multiple_spaces(string text)
{
    bool valid;
    bool first_entry = true;
    int cache = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        bool is_space = text[i] == ' ';

        if (first_entry)
        {
            first_entry = false;
            valid = true;
        }
        else if (is_space)
        {
            valid = (i - cache) > 1;
        }
        else
        {
            valid = true;
        }

        /* If valid, update cache if necessary. Quit if not valid */
        if (valid)
        {
            cache = (is_space) ? i : cache;
        }
        else
        {
            break;
        }
    }
    return valid;
}

int count_letters(string text)
{
    int sum = 0;
    int u_low = 65, u_high = 90;
    int l_low = 97, l_high = 122;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        int value = (int)text[i];

        if ((value >= u_low) && (value <= u_high))
        {
            sum ++;
        }
        else if ((value >= l_low) && (value <= l_high))
        {
            sum ++;
        }
        else
        {
            /* Do nothing */
        }
    }
    return sum;
}

int count_words(string text)
{
    int sum = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((i == 0) && (n > 0))
        {
            sum ++;
        }
        else if (text[i] == ' ')
        {
            sum++;
        }
        else
        {
            /* Do nothing */
        }
    }
    return sum;
}

int count_sentences(string text)
{
    int sum = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((i == 0) && (n > 0))
        {
            sum++;
        }
        else if (text[i] == '.')
        {
            sum++;
        }
        else
        {
            /* Do nothing */
        }
    }
    return sum;
}

bool validate_text_input(string text)
{
    bool valid;

    valid = count_words(text) >= 1;
    valid = (valid) ? check_for_start_end_spaces(text) : false;
    valid = (valid) ? check_for_multiple_spaces(text) : false;

    return valid;
}

int main(void)
{
    const string text = get_text_input();

    printf("-> %s\n", text);
}