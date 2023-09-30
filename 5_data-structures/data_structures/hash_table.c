#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#define HASH_MAX 25

unsigned int hash(char *str)
{
    int sum = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        sum += str[i];
    }
    return sum % HASH_MAX;
}

int main(void)
{
    printf("hash: %d\n", hash("John"));
    printf("hash: %d\n", hash("Paul"));

    return 0;
}