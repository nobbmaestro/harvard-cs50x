#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/* Function prototypes */
string get_text_input(void);

bool check_for_multiple_spaces(string text);
bool check_for_start_end_spaces(string text);
bool validate_text_input(string text);

int count_letters(string text);
int count_sentences(string text);
int count_words(string text);
int grade_text(string text);

float calculate_avg_num_letters_per_words(int letters, int words);
float calculate_avg_num_sentences_per_words(int senteces, int words);
float calculate_coleman_liau_index(float L, float S);

/* Main function */
int main(void)
{
    int grade;

    const string text = get_text_input();
    grade = grade_text(text);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }
}

/* Helpers */
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

bool check_for_multiple_spaces(string text)
{
    bool valid;
    bool first_entry = true;
    int cache = -1;

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

bool check_for_start_end_spaces(string text)
{
    int last_chr = strlen(text) - 1;
    return (text[0] != ' ') && (text[last_chr] != ' ');
}

bool validate_text_input(string text)
{
    bool valid;

    valid = count_words(text) >= 1;
    valid = (valid) ? check_for_start_end_spaces(text) : false;
    valid = (valid) ? check_for_multiple_spaces(text) : false;

    return valid;
}

int count_letters(string text)
{
    int sum = 0;
    int UPPERCASE_LO = 65, UPPERCASE_HI = 90;
    int LOWERCASE_HI = 97, LOWERCASE_HI = 122;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        int value = (int)text[i];

        if ((value >= UPPERCASE_LO) && (value <= UPPERCASE_HI))
        {
            sum ++;
        }
        else if ((value >= LOWERCASE_HI) && (value <= LOWERCASE_HI))
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

int count_sentences(string text)
{
    int sum = 0;
    for (int i = 0, n = strlen(text); i <= n; i++)
    {
        if ((text[i] == '\0') && (sum == 0) && (n > 1))
        {
            sum++;
        }
        else if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?'))
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

int count_words(string text)
{
    int sum = 0;
    for (int i = 0, n = strlen(text); i <= n; i++)
    {
        if ((text[i] == '\0') && (n >= 1))
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

int grade_text(string text)
{
    int words, letters, sentences;
    float grade, avg_letters, avg_sentences;

    words = count_words(text);
    letters = count_letters(text);
    sentences = count_sentences(text);

    avg_letters = calculate_avg_num_letters_per_words(letters, words);
    avg_sentences = calculate_avg_num_sentences_per_words(sentences, words);
    grade = calculate_coleman_liau_index(avg_letters, avg_sentences);

    return round(grade);
}

float calculate_coleman_liau_index(float L, float S)
{
    return (0.0588 * L) - (0.296 * S) - 15.8;
}

float calculate_avg_num_letters_per_words(int letters, int words)
{
    return ((float)letters / (float)words) * 100.0F;
}

float calculate_avg_num_sentences_per_words(int sentences, int words)
{
    return ((float)sentences / (float)words) * 100.0F;
}
