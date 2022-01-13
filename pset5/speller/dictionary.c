// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 17576;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    node *p = NULL;
    p = table[index]->next;
    while (p != NULL)
    {
        if (strcasecmp(p->word, word) == 0)
        {
            return true;
        }
        p = p->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int index = 0;
    if (strlen(word) > 3 && isalpha(word[3]))
    {
        index = (int)(tolower(word[3])) - 97;
    }

    if (strlen(word) > 4 && isalpha(word[4]))
    {
        index = index * 26 + (int)(tolower(word[4])) - 97;
    }

    if (strlen(word) > 5 && isalpha(word[5]))
    {
        index = index * 26 + (int)(tolower(word[4])) - 97;
    }

    if (index >= N)
    {
        return N - 1;
    }
    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *input_dic = fopen(dictionary, "r");
    if (input_dic == NULL)
    {
        printf("Could not open a dictionary file.\n");
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        table[i] = malloc(sizeof(node));
        if (table[i] == NULL)
        {
            printf("Could not allocate enough memory.\n");
            return false;
        }

        table[i]->next = NULL;
    }

    char buffer[LENGTH + 1];
    while (fscanf(input_dic, "%s", buffer) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Could not allocate enough memory.\n");
            return false;
        }

        strcpy(n->word, buffer);

        node *tmp = NULL;
        tmp = table[hash(n->word)]->next;
        table[hash(n->word)]->next = n;
        n->next = tmp;
    }

    fclose(input_dic);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int dic_size = 0;
    node *cursor = NULL;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i]->next;
        while (cursor != NULL)
        {
            dic_size++;
            cursor = cursor->next;
        }
    }

    return dic_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *cursor = NULL;
    node *tmp = NULL;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i]->next;
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

        free(table[i]);
    }

    return true;
}