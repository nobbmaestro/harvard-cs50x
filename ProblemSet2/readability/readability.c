#include <cs50.h>
#include <stdio.h>

/* Function prototypes */
float get_coleman_liau_index(float L, float S);


/* Main code */
float get_coleman_liau_index(float L, float S)
{
    /*
        L - average number of letters per 100 words
        S - average number of sentences per 100 words.
    */
    float index = (0.058 * L) - (0.296 * S) - 15.8;
    return index;
}

int main(void)
{
    string text;

    scanf("Text: %s", &text);
    printf("-> %s\n", text);
}