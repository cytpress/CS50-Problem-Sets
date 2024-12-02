#include <stdio.h>
#include <math.h>
#include <cs50.h>

int calculate_coins(int cents);

int main(void)
{
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    } while (cents < 0);
    printf("%d", calculate_coins(cents));
}

int calculate_coins(int cents)
{
    int i = 0;
    while (cents >= 25)
    {
        i++;
        cents -= 25;
    }
    while (cents >= 10)
    {
        i++;
        cents -= 10;
    }
    while (cents >= 5)
    {
        i++;
        cents -= 5;
    }
    while (cents >= 1)
    {
        i++;
        cents -= 1;
    }
    return i;
}
