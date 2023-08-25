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
        printf("Grade 1\n");
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

bool check_for_start_end_spaces(string text)
{
    int last_chr = strlen(text) - 1;
    return (text[0] != ' ') && (text[last_chr] != ' ');
}

bool validate_text_input(string text)
{
    bool valid;

    valid = count_words(text) >= 1;
    printf("Valid word count: \t%d\n", valid);
    valid = (valid) ? check_for_start_end_spaces(text) : false;
    printf("Valid start/end: \t%d\n", valid);
    valid = (valid) ? check_for_multiple_spaces(text) : false;
    printf("Valid spaces: \t\t%d\n", valid);

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
    grade = calculate_coleman_liau_index(round(avg_letters), round(avg_sentences));

    printf("\n");
    printf("letters: \t%d\n", letters);
    printf("words: \t\t%d\n", words);
    printf("sentences: \t%d\n", sentences);
    printf("\n");
    printf("AVG letters: \t%f\n", avg_letters);
    printf("AVG sentences: \t%f\n", avg_sentences);
    printf("\n");
    printf("GRADE: \t%f\n", grade);

    return round(grade);
}

float calculate_coleman_liau_index(float L, float S)
{
    return (0.058 * L) - (0.296 * S) - 15.8;
}

float calculate_avg_num_letters_per_words(int letters, int words)
{
    return ((float)letters / (float)words) * 100.0F;
}

float calculate_avg_num_sentences_per_words(int sentences, int words)
{
    return ((float)sentences / (float)words) * 100.0F;
}
