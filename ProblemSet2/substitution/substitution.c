#include <cs50.h>
#include <stdio.h>

#define KEY_LEN 26

/* Function prototypes */

/* Main function */
int main(int argc, string argv[])
{
    bool valid_key;
    string key, plain, cipher;

    if (argc == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    key = argv[1];
    printf("key: %s\n", key);

}

/* Helpers */
bool validate_key(string key)
{
    bool valid = false;

    // valid = strlen(key) != KEY_LEN;

    return valid;
}