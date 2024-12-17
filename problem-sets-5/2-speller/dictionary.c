// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"
#include <stdlib.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 12345;

//
int size_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hash_value = hash(word);
    node *ptr = table[hash_value];
    while (ptr != NULL)
    {
        if (strcasecmp(word, ptr->word) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int hash_value = 0;
    for (int i = 0, l = strlen(word); i < l; i++)
    {
        hash_value = hash_value * 1517 + (toupper(word[i]) - 'A');
    }
    return hash_value % N;
    // return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *source = fopen(dictionary, "r");
    char word[45];

    if (source == NULL)
    {
        printf("cannot open file");
        return false;
    }
    while (fscanf(source, "%s", word) != EOF)
    {
        node *character_list = malloc(sizeof(node));
        if (character_list == NULL)
        {
            return false;
        }
        strcpy(character_list->word, word);
        int hash_value = hash(character_list->word);
        character_list->next = table[hash_value];
        table[hash_value] = character_list;
        size_count++;
    }
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return size_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *ptr = NULL;
    node *tmp = NULL;
    for (int i = 0; i < N; i++)
    {
        ptr = table[i];
        while (ptr != NULL)
        {
            tmp = ptr->next;
            free(ptr);
            ptr = tmp;
        }
    }
    return true;
}
