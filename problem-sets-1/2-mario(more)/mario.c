#include <stdio.h>
#include <cs50.h>

void print_row(int spaces, int bricks);

int main()
{
    int n;
    do
    {
        n = get_int("Height: ");
    } while (n < 1 || n > 8);

    for (int i = 0; i < n; i++)
    {
        print_row(n - i, i + 1);
    }
}

void print_row(int spaces, int bricks)
{
    for (int i = 1; i < spaces; i++)
    {
        printf(" ");
    }

    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }

    printf("  ");

    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
    for (int i = 1; i < spaces; i++)
    {
        printf(" ");
    }

    printf("\n");
}