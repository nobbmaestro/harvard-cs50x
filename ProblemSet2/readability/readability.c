#include <cs50.h>
#include <stdio.h>

/* Function prototypes */
float calculate_coleman_liau_index(float L, float S);
int calculate_num_sentences(string * p_text);
int calculate_num_letters(string * p_text);
int calculate_num_words(string * p_text);
float calculate_avg_letters_per_words(int letters, int words);
float calculate_avg_

/* Main code */
float calculate_coleman_liau_index(float L, float S)
{
    /*
        L - average number of letters per 100 words
        S - average number of sentences per 100 words.
    */
    float index = (0.058 * L) - (0.296 * S) - 15.8;
    return index;
}

int calculate_num_sentences(void)
{
    return 0;
}

int main(void)
{
    string text;
    text = get_string("Text: ");

    printf("-> %s\n", text);
}