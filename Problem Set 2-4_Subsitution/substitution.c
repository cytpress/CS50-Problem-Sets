#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void subsitution_encryption(string txt, string key);

int main(int argc, string argv[])
{
    // check only 1 input & has 26 characters
    if (argc == 2 && (strlen(argv[1]) == 26))
    {
        // check all alphabet & repeat
        string r = argv[1];
        for (int i = 0, l = strlen(argv[1]); i < l; i++)
        {
            if (isalpha(argv[1][i]) == false)
            {
                printf("Key must contain only alphabet\n");
                return 1;
            }
            for (int j = 0, c = 0; j < l; j++)
            {
                if (r[i] == argv[1][j])
                {
                    c++;
                }
                if (c == 2)
                {
                    printf("Key must not repeat\n");
                    return 1;
                }
            }
        }
        string key = argv[1];
        string plaintxt = get_string("plaintext: ");
        printf("ciphertext: ");
        subsitution_encryption(plaintxt, key);
        printf("\n");
        return 0;
    }
    else
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
}
void subsitution_encryption(string txt, string key)
{
    string table_u = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string table_l = "abcdefghijklmnopqrstuvwxyz";
    char key_difference[27] = {};

    for (int i = 0, l = strlen(key); i < l; i++)
    {
        if (key[i] >= 'a' && key[i] <= 'z')
        {
            key[i] -= 32;
        }
        key_difference[i] = key[i] - table_u[i];
    }

    for (int i = 0, l = strlen(txt); i < l; i++)
    {
        if (txt[i] >= 'a' && txt[i] <= 'z')
        {
            for (int j = 0, l = strlen(table_l); j < l; j++)
            {
                if (txt[i] == table_l[j])
                {
                    printf("%c", (txt[i] + key_difference[j]));
                }
            }
        }
        else if (txt[i] >= 'A' && txt[i] <= 'Z')
        {
            for (int j = 0, l = strlen(table_u); j < l; j++)
            {
                if (txt[i] == table_u[j])
                {
                    printf("%c", (txt[i] + key_difference[j]));
                }
            }
        }
        else
        {
            printf("%c", txt[i]);
        }
    }
}