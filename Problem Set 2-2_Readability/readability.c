#include <ctype.h>
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// index = 0.0588 * L - 0.296 * S - 15.8
// L = letters / words * 100
// S = sentences  / words * 100

int count_letters(string txt);
int count_words(string txt);
int count_sentences(string txt);
int calculate_index(float letters, float words, float sentences);

int main(void)
{
    string text_to_analyze = get_string("Text: ");
    int letters = count_letters(text_to_analyze);
    int words = count_words(text_to_analyze);
    int sentences = count_sentences(text_to_analyze);
    int index = calculate_index(letters, words, sentences);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string txt)
{
    int letter_conunt = 0;
    for (int i = 0, length = strlen(txt); i < length; i++)
    {
        if (isalpha(txt[i]))
        {
            letter_conunt++;
        }
    }
    return letter_conunt;
}
int count_words(string txt)
{
    int word_count = 0;
    for (int i = 0, length = strlen(txt); i < length; i++)
    {
        if (isblank(txt[i]))
        {
            word_count++;
        }
    }
    return word_count + 1;
}
int count_sentences(string txt)
{
    int sentence_count = 0;
    for (int i = 0, length = strlen(txt); i < length; i++)
    {
        if (txt[i] == '.' || txt[i] == '!' || txt[i] == '?')
        {
            sentence_count++;
        }
    }
    return sentence_count;
}

// index = 0.0588 * L - 0.296 * S - 15.8
// L = letters / words * 100
// S = sentences  / words * 100
int calculate_index(float letters, float words, float sentences)
{
    float l = 0, s = 0, index = 0;
    l = letters / words * 100;
    s = sentences / words * 100;
    index = 0.0588 * l - 0.296 * s - 15.8;
    return round(index);
}
