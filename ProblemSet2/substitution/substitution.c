#include <cs50.h>
#include <stdio.h>

#define KEY_LEN 26

/* Function prototypes */

/* Main function */
int main(int argc, string argv[])
{
    string key, plain, cipher;

}

/* Helpers */
bool validate_key(string key)
{
    bool valid;

    valid = strlen(key) != KEY_LEN;

    return valid;
}