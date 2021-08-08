// Implements a dictionary's functionality

#include <stdbool.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table 143092
const unsigned int N = 100000;
int word_count = 0;
// Hash table
node *table[N] = { NULL };

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //create an array of NULL chars, i.e. empty
    char word[LENGTH + 1] = { '\0' };
    FILE *file = fopen(dictionary, "r");
    //if we could open the file, leave returing false
    if (file == NULL)
    {
        return false;
    }
    int index = 0;
    unsigned int key;
    char c;
    //keep reading the file one char at a time till we reach the EOF
    while (fread(&c, sizeof(char), 1, file))
    {
        //keep adding to the word array untill we have a full word and hit a new line
        if (c != 10)
        {
            word[index] = c;
            index++;
        }
        //when we hit a new line
        else
        {
            index = 0;

        }
        //if we have a full word, add it to the data structure
        if (index == 0)
        {
            //get the hash code of that word
            key = hash(word);
            node *new_slot = calloc(1, sizeof(node));

            //if the root at that key is empty, copy the word to it
            if (table[key] == NULL)
            {
                table[key] = new_slot;
                strcpy(table[key]->word, word);
            }
            //if the node after the root is empty, copy the word to it
            else if (table[key]->next == NULL)
            {
                strcpy(new_slot->word, word);
                new_slot->next = NULL;
                table[key]->next = new_slot;
            }
            //if the node after the root is full, then make our new node point at it,
            //then make the the root point at the new node
            else if (table[key]->next != NULL)
            {
                strcpy(new_slot->word, word);
                new_slot->next = table[key]->next;
                table[key]->next = new_slot;
            }

            //empty the word array and add 1 to the word count
            memset(&word[0], 0, sizeof(word));
            word_count++;
        }
    }

    // TODO
    fclose(file);
    return true;
}

// Hashes word to a number
/* djb2 with some modifications*/
unsigned int hash(const char *str)
{

    unsigned int hash = 5381;
    int c;
    int i = 0;
    while (*(str + i) != '\0')
    {
        c = tolower(*(str + i));
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        i++;
    }
    //N is the hash table size
    return hash % N;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //if a word is one char or more than the max length, returns true
    if (strlen(word) >= LENGTH)
    {
        return true;
    }
    //key the hash key to use in the search
    unsigned int key = hash(word);
    //if that spot at the table is empty, return not found
    if (table[key] == NULL)
    {
        return false;
    }
    //else go through that part of the table and its linked-list and search for that word
    else
    {
        node *crawler;
        crawler = table[key];
        while (crawler != NULL)
        {
            //see if the word stored at the location we are at is equal to the word we're searching for
            if ((strcasecmp(crawler->word, word)) == 0)
            {
                return true;
            }
            //check if the next node is empty, if it is, leave
            if (crawler->next == NULL)
            {
                return false;
            }
            //move to the next node in the list
            crawler = crawler->next;
        }
    }
    // TODO
    return false;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *tmp;
    node *crawler;
    //go through the whole table
    //N is the table length
    for (int i = 0; i < N; i++)
    {
        crawler = table[i];
        //if the root we are at isn't NULL i.e. empty, free it
        if (crawler != NULL)
        {
            //but first check if it's connected to another node
            while (crawler->next != NULL)
            {
                tmp = crawler;
                crawler = crawler->next;
                free(tmp);
            }
            //when the node we are at is empty, free it
            free(crawler);
        }
    }
    return true;
}
