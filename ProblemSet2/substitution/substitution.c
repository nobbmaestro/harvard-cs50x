#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define KEY_LEN 3

/* Function prototypes */
bool validate_key(string key);
bool check_key_length(string key);
bool check_key_alphabetic(string key);
bool check_key_unique(string key);

string encrypt_text(string text);
string decrypt_text(string text);

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
        cipher = encrypt_text(plain);
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
    int u_low = 65, u_high = 90;
    int l_low = 97, l_high = 122;

    for (int i = 0; i < KEY_LEN; i++)
    {
        int value = (int)key[i];

        if ((value >= u_low) && (value <= u_high))
        {
            valid = true;
        }
        else if ((value >= l_low) && (value <= l_high))
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
    int u_low = 65, u_high = 90;
    int l_low = 97, l_high = 122;

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

        if ((value >= u_low) && (value <= u_high))
        {
            index = value - u_low;
            key_map[index]++;
        }
        else if ((value >= l_low) && (value <= l_high))
        {
            index = value - u_low;
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
    return text;
}

char apply_char_encryption(char chr, string key)
{

}