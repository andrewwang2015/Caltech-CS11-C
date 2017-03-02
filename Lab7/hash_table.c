/*
 * CS 11, C Track, lab 7
 *
 * FILE: hash_table.c
 *
 *       Implementation of the hash table functionality.
 *
 */

/*
 * Include the declaration of the hash table data structures
 * and the function prototypes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "memcheck.h"


/*** Hash function. ***/

int hash(char *s)
{
    int i;
    int sum = 0;

    for (i = 0; *(s + i) != '\0'; i++)
    {
        sum += *(s + i);
    }

    return (sum % NSLOTS);
}


/*** Linked list utilities. ***/

/* Create a single node. */
node *create_node(char *key, int value)
{
    node *result = (node *)malloc(sizeof(node));

    if (result == NULL)
    {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }

    result->key = key;
    result->value = value;
    result->next = NULL;

    return result;
}


/* Free all the nodes of a linked list. */
void free_list(node *list)
{
    node *temp = NULL;
    char *tempKey;
    while (list != NULL)
    {
        temp = list;
        tempKey = temp->key;
        list = list->next;
        if (tempKey != NULL)
        {
            free(tempKey);
        }
        free(temp);
    }
}


/*** Hash table utilities. ***/

/* Create a new hash table. */
hash_table *create_hash_table()
{
    hash_table* newTable = (hash_table *)malloc(sizeof(hash_table));
    if (newTable == NULL)
    {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }

    (newTable->slot) = (node**)malloc(NSLOTS * sizeof(node));
    return newTable;
}


/* Free a hash table. */
void free_hash_table(hash_table *ht)
{
    int i;
    node **tempSlot = ht->slot;
    for (i = 0; i < NSLOTS; i++)
    {
        free_list(tempSlot[i]);
    }

    free(tempSlot);
    free(ht);
}


/*
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 */
int get_value(hash_table *ht, char *key)
{

    node **tempSlot = ht->slot;
    int keyValue = hash(key);

    node *listOfInterest = tempSlot[keyValue];

    while (listOfInterest != NULL)
    {
        if (strcmp(key, listOfInterest->key) == 0)
        {

            return listOfInterest->value;
        }

        listOfInterest = listOfInterest -> next;
    }

    return 0;
}


/*
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 */
bool set_value(hash_table *ht, char *key, int value)
{
    node ** tempSlot = ht->slot;
    int keyValue = hash(key);
    node *tempList = tempSlot[keyValue];
    node *newNode = NULL;
    node *original = tempList;

    if (tempList == NULL)
    {
        tempList = create_node(key,value);
        tempSlot[keyValue] = tempList;
    }

    else
    {
        while (tempList != NULL)
        {
            if (strcmp(tempList->key, key) == 0)
            {
                tempList->value += 1;
                free(key);
                break;
            }

            tempList = tempList->next;
        }

        if (tempList == NULL)
        {
            newNode = create_node(key,value);
            newNode->next = original;
            tempSlot[keyValue] = newNode;
        }

    }
    return true;
}


/* Print out the contents of the hash table as key/value pairs. */
void print_hash_table(hash_table *ht)
{
    int i;
    node **currentSlot = ht->slot;
    node *listIterator = NULL;

    for (i = 0 ; i < NSLOTS ; i++)
    {
        listIterator = currentSlot[i];
        while (listIterator != NULL)
        {
            printf("%s %d\n", listIterator->key, listIterator -> value);
            listIterator = listIterator -> next;
        }
    }

}


