#include <cs50.h>
#include <stdio.h>

#define KEY_LEN 26

/* Function prototypes */

/* Main function */
int main(int argc, string argv[])
{
    bool valid_key;
    string key, plain, cipher;

    if ((argc == 1) || (argc > 2))
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (argv[1] != KEY_LEN)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        key = argv[1];
        printf("key: %s\n", key);
        return 0;
    }
}

/* Helpers */
bool validate_key(string key)
{
    bool valid = false;

    // valid = strlen(key) != KEY_LEN;

    return valid;
}