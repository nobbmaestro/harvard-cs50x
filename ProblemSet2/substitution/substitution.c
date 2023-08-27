#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define KEY_LEN 26
#define UPPERCASE_LO 65
#define UPPERCASE_HI 90
#define LOWERCASE_LO 97
#define LOWERCASE_HI 122

/* Function prototypes */
bool validate_key(string key);
bool check_key_length(string key);
bool check_key_alphabetic(string key);
bool check_key_unique(string key);

string encrypt_text(string text, string key);
string decrypt_text(string text);
int get_relative_shift(char chr, string key);

/* Main function */
int main(int argc, string argv[])
{
    int exit_status;
    string key, plain, cipher;

    if ((argc == 1) || (argc > 2))
    {
        printf("Usage: ./substitution key\n");
        exit_status = 1;
    }
    else if (!validate_key(argv[1]))
    {
        printf("Invalid key.\n");
        exit_status = 1;
    }
    else
    {
        key = argv[1];
        printf("key: %s\n", key);

        plain = get_string("plaintext: ");
        cipher = encrypt_text(plain, key);
        printf("ciphertext: %s\n", cipher);

        exit_status = 1;
    }
    return exit_status;
}

/* Helpers */
bool validate_key(string key)
{
    bool valid = true;

    valid &= check_key_length(key);
    valid &= check_key_alphabetic(key);
    valid &= check_key_unique(key);

    return valid;
}

bool check_key_length(string key)
{
    return strlen(key) == KEY_LEN;
}

bool check_key_alphabetic(string key)
{
    bool valid;

    for (int i = 0; i < KEY_LEN; i++)
    {
        int value = (int)key[i];

        if ((value >= UPPERCASE_LO) && (value <= UPPERCASE_HI))
        {
            valid = true;
        }
        else if ((value >= LOWERCASE_LO) && (value <= LOWERCASE_HI))
        {
            valid = true;
        }
        else
        {
            valid = false;
        }

        if (!valid)
        {
            break;
        }
    }
    return valid;
}

bool check_key_unique(string key)
{
    int key_map[KEY_LEN];

    /* Set all key_map indexes to zero */
    for (int i = 0; i < KEY_LEN; i++)
    {
        key_map[i] = 0;
    }

    /* Populate the key_map array */
    for (int i = 0; i < KEY_LEN; i++)
    {
        int index;
        int value = (int)key[i];

        if ((value >= UPPERCASE_LO) && (value <= UPPERCASE_HI))
        {
            index = value - UPPERCASE_LO;
            key_map[index]++;
        }
        else if ((value >= LOWERCASE_LO) && (value <= LOWERCASE_HI))
        {
            index = value - LOWERCASE_LO;
            key_map[index]++;
        }
        else
        {
            /* Do nothing */
        }
    }

    /* Check the key_map array for dublicated */
    bool unique = true;
    for (int i = 0; i < KEY_LEN; i++)
    {
        unique &= key_map[i] == 1;

        if (!unique)
        {
            break;
        }
    }

    return unique;
}

string encrypt_text(string text, string key)
{
    char cipher[strlen(text)];
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        int shift = get_relative_shift(text[i], key);
        printf("shift: %d, %c -> %c\n", shift, text[i], text[i] + shift);
    }
    return text;
}

char get_shifted_char(char chr, string key)
{
    int value = (int)chr;
    bool upper = (value >= UPPERCASE_LO) && (value <= UPPERCASE_HI);
    bool lower = (value >= LOWERCASE_LO) && (value <= LOWERCASE_HI);

    char map_chr = (lower) ? chr - (LOWERCASE_HI - UPPERCASE_HI) : chr;
    int index = (int)map_chr - UPPERCASE_LO;

    return key[index];
}

int get_relative_shift(char chr, string key)
{
    int shift = 0;
    int value = (int)chr;

    bool upper = (value >= UPPERCASE_LO) && (value <= UPPERCASE_HI);
    bool lower = (value >= LOWERCASE_LO) && (value <= LOWERCASE_HI);
    char map_chr = (lower) ? chr - (LOWERCASE_HI - UPPERCASE_HI) : chr;

    /* If chr is alphabetic, find the match from key */
    if (upper || lower)
    {
        for (int i = 0; i < KEY_LEN; i++)
        {
            if (map_chr == key[i])
            {
                shift = i - ((int)map_chr - UPPERCASE_LO);
                break;
            }
            else
            {
                /* Do nothing */
            }
        }
    }
    else
    {
        /* Do nothing */
    }

    return shift;
}