#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void caesar_encryption(string txt, int key);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        for (int i; i < strlen(argv[1]); i++)
        {
            if (isdigit(argv[1][i]) == false)
            {
                printf("Usage ./caesar key\n");
                return 1;
            }
        }
        int n = atoi(argv[1]);
        string plaintxt = get_string("plaintxt: ");
        printf("ciphertext: ");
        caesar_encryption(plaintxt, n);
        printf("\n");
        return 0;
    }
    else
    {
        printf("Usage ./caesar key\n");
        return 1;
    }
}

// caesar cypher = (plain + key) % 26
void caesar_encryption(string txt, int key)
{
    for (int i = 0, length = strlen(txt); i < length; i++)
    {
        if (txt[i] >= 'a' && txt[i] <= 'z')
        {
            printf("%c", ((txt[i] - 'a' + (key % 26)) % 26 + 'a'));
        }
        else if (txt[i] >= 'A' && txt[i] <= 'Z')
        {
            printf("%c", ((txt[i] - 'A' + (key % 26)) % 26 + 'A'));
        }
        else
        {
            printf("%c", txt[i]);
        }
    }
}