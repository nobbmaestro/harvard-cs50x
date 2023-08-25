#include <cs50.h>
#include <stdio.h>

/* Function prototypes */
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
    /*
        L - average number of letters per 100 words
        S - average number of sentences per 100 words.
    */
    float index = (0.058 * L) - (0.296 * S) - 15.8;
    return index;
}

bool validate_text_input(string text)
{

}

int main(void)
{
    string text;
    text = get_string("Text: ");

    printf("-> %s\n", text);
}