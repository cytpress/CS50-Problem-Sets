#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>

int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int calculate_score(string word);

int main(void)
{
    string player1_word = get_string("Player 1: ");
    string player2_word = get_string("Player 2: ");

    int player1_score = calculate_score(player1_word);
    int player2_score = calculate_score(player2_word);

    if (player1_score > player2_score)
    {
        printf("Player 1 wins!\n");
    }
    else if (player1_score < player2_score)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie\n");
    }
}

int calculate_score(string word)
{
    int score = 0;

    for (int i = 0, length = strlen(word); i < length; i++)
    {
        if (isupper(word[i]))
        {
            score += points[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            score += points[word[i] - 'a'];
        }
    }
    return score;
}