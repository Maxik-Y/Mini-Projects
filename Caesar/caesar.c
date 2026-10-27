#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if(!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int key = atoi(argv[1]);

    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        char c = plaintext[i];

        if (isupper(c)){
            c = (((c - 'A') + key) % 26) + 'A';
        }
        else if (islower(c)){
            c = (((c - 'a') + key) % 26) + 'a';
        }
        printf("%c",c);
    }

    printf("\n");
    return 0;
}
