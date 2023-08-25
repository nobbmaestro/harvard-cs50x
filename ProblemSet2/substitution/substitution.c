#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define KEY_LEN 2

/* Function prototypes */
bool validate_key(string key);
bool check_key_alphabetic(string key);
bool check_key_unique(string key);

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
        printf("Key must contain 26 characters.\n");
        exit_status = 1;
    }
    else
    {
        key = argv[1];
        printf("key: %s\n", key);
        exit_status = 1;
    }
    return exit_status;
}

/* Helpers */
bool validate_key(string key)
{
    bool valid = true;

    valid &= validate_key_length(key);
    valid &= validate_key_chars(key);

    return valid;
}

bool check_key_length(string key)
{
    return strlen(key) == KEY_LEN;
}

bool check_key_alphabetic(string key)
{
    bool valid;
    int u_low = 65, u_high = 90;
    int l_low = 97, l_high = 122;

    for (int i = 0; i < KEY_LEN; i++)
    {
        char c = key[i];
        if ((c >= u_low) && (c <= u_high))
        {
            valid = true;
        }
        else if ((c >= l_low) && (c <= l_high))
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
    return false;
}