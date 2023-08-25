#include <cs50.h>
#include <stdio.h>

#define KEY_LEN 26

/* Function prototypes */

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
    else if (argv[1] != KEY_LEN)
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
