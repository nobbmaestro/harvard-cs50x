#include <cs50.h>
#include <stdio.h>
#include <string.h>

/* Function prototypes */
string get_input(void);
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

string get_input(void)
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
    int last_idx = strlen(text);
    return (text[0] != ' ') || (text[last_idx] != ' ');
}

bool check_for_multiple_spaces(string text)
{
    bool valid;
    int cache = 0;

    for (int i = 0, n = strlen(text); i <= n; i++)
    {
        bool is_space = text[i] == ' ';

        valid = ((i - cache == 1) && is_space);
        cache = (is_space) ? i : cache;

        if (!valid)
        {
            break;
        }
    }

    return valid;
}

int count_words(string text)
{
    return 1;
}

bool validate_text_input(string text)
{
    bool valid = true;
    valid &= count_words(text) >= 1;
    printf("Checking for number of words: \t%d\n", valid);
    valid &= check_for_start_end_spaces(text);
    printf("Checking for stard/end spaces: \t%d\n", valid);

    return valid;
}

int main(void)
{
    const string text = get_input();

    printf("-> %s\n", text);
}