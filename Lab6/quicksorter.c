/* @brief: This program takes in commandline arguments of numbers, 
puts it into a linked list, and quicksorts the linked list. */

#include <stdlib.h>
#include "memcheck.h"
#include <stdio.h>
#include "linked_list.h"
#include <string.h>
#include <assert.h>


void printUsage(char* programName);
node* quickSort(node *initialList);



/* 
@brief: This is the main function. It will handle all inputline
 arguments and proceed accordingly.

@param: argc - number of input arguments
       argv[] - contains all input arguments

@return: n/a - ends the program
*/

int main(int argc, char* argv[])
{   
    node* inputList = NULL;
    node* finalList = NULL;
    int numbers = 0;
    int quiet = 0;
    int i;
    int currentNum;

    if (argc < 2)
    {
        printUsage(argv[0]);
        return 1;       /* If nothing is inputted, exit. */
    }

    else
    {

        for (i = 1; i < argc; i++)
        {

            if (strcmp(argv[i], "-q") == 0)
            {
                quiet = 1;
            }


            else
            {
                numbers++;
                currentNum = atoi(argv[i]);
                inputList = create_node(currentNum, inputList);
            }
        }
    }

    finalList = quickSort(inputList);

    if (quiet == 1 && numbers == 0)     /* If the -q is the only input */
    {
        printUsage(argv[0]);
    }

    else if (quiet == 1)
    {
        return 0;
    }

    else
    {
        print_list(finalList);
    }

    free_list(finalList);
    free_list(inputList);
    
    print_memory_leaks();
    return 0;
}

/* 
@brief: Prints out usage function for program.

@param: character array referring to program name

@return: none
*/

void printUsage(char* programName)
{
    fprintf(stderr, "usage: %s [-q] number 1 [number2...]\
        as many numbers as you want)\n", programName);
}


/* 
@brief: Recursively sorts the inputted list via Quicksort

@param: Pointer to linkedlist for sorting

@return: Pointer to sorted list
*/

node* quickSort(node *initialList)
{
    node* leftHalf = NULL;
    node* rightHalf = NULL;
    node* sortedLeft = NULL;
    node* sortedRight = NULL;
    node* finalSorted2 = NULL;
    node* iList = NULL;
    int pivot;

    if (initialList == NULL || initialList->next == NULL)
    {
        /* If empty list or list of one number, 
        return copy of initial list */

        return copy_list(initialList);  
    }

    else
    {
        
        pivot = initialList->data;

        for (iList = initialList->next; iList != NULL; iList = iList->next)
        {
            if (iList->data < pivot)
            {
                leftHalf = create_node(iList->data, leftHalf);
            }

            else 
            {
                rightHalf = create_node(iList->data, rightHalf);
            }
        }


        sortedRight = quickSort(rightHalf);
        sortedLeft = quickSort(leftHalf);

        sortedRight = create_node(pivot, sortedRight);
        finalSorted2 = append_lists(sortedLeft, sortedRight);

        free_list(sortedLeft);
        free_list(sortedRight);
        free_list(rightHalf);
        free_list(leftHalf);
        assert(is_sorted(finalSorted2));
        return finalSorted2;

    }
}

