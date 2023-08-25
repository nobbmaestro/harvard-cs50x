#include <cs50.h>
#include <stdio.h>

/* Function prototypes */
string get_input(void);
bool validate_text_input(string text);

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
    } while (!validate_text_input(text));

    return text;
}

bool check_for_start_end_space(string text)
{
    int last_idx = strlen(text);
    return (text[0] != ' ') || (text[last_idx] != ' ');
}

bool check_for_multiple_spaces(string text)
{
    bool valid;
    int cache;

    for (int i = 0, n = strlen(text); i <= n; i++)
    {
        char curr_char = text[i];
        if (curr_char == ' ')
        {
            cache = i;
        }
    }

    return valid;
}

bool validate_text_input(string text)
{
    bool valid;
    valid = count_words(text) >= 1;

    return true;
}

int main(void)
{
    const string text = get_input();

    printf("-> %s\n", text);
}