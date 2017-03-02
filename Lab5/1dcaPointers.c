/* This program uses array operations to implement a 1dCA with two 
states (full and empty, which correspond to 1 and 0). */

#include <stdlib.h>
#include "memcheck.h"
#include <stdio.h>
#include <time.h>

void printGeneration(int cellSize, int* starting);
void getFirst(int cellSize, int* arr);
void update(int cellSize, int generations, int* arr);



/* 
@brief: This is the function which will print the generation. It will print
 a '*' for 1's and a '.' for 0's

@param: cellSize - the number of cells in a row
        starting - pointer to first element of array to print

@return: n/a
*/

void printGeneration(int cellSize, int* starting)
{
    int i;
    for (i = 0 ; i < cellSize; i++)
    {
        if (*(starting + i) == 1)
        {
            printf("*");
        
        }

        else
        {
            printf(".");
        }
    }

    printf("\n");   /* new line so next generation starts on a new line. */
}

/* 
@brief: This function updates the previous generation by replacing it with
the newly constructed row. 

@param: cellSize - the number of cells in a row
        original - pointer to starting element of previous previous
        successive - pointer to starting element of array that will replace
        the old one

@return: n/a
*/

void replace(int cellSize, int* successive, int* original)
{
    int i;
    for (i = 0; i < cellSize; i++)
    {
        *(original + i) = *(successive + i);
    }
}


/* 
@brief: This is the function which will randomly assign full or empty 
states for the first generation of cells/ first row.

@param: cellSize - the number of cells in a row
        arr - pointer to starting element of starting array

@return: n/a
*/

void getFirst(int cellSize, int* arr)
{
    int randomNum;
    int i;

    srand(time(0));  /* Seeds the random generatior */

    *arr = 0;
    *(arr + cellSize - 1) = 0;              /* Set first and last to empty */
    for (i = 1 ; i < (cellSize - 1); i++)
    {
        randomNum = rand() % 2;  /* Random number ( 0 or 1) */
        if (randomNum == 1)
        {
           *(arr + i) = 1;
        }

        else
        {
            *(arr + i) = 0;
        }
    }
}


/* 
@brief: This is the function whcih will update each succesive generation
of cells and call on the print function to output these generations one
row at a time.

@param: cellSize - the number of cells in a row
        generations - the number of generations
        arr - pointer to starting element of starting array

@return: n/a

UPDATE RULES:
1. If the current cell is empty, and one of the two adjacent cells is full 
(but not both), set the current cell to be full.

2. Otherwise set the current cell to be empty.
*/

void update(int cellSize, int generations, int* arr)
{
    int *successiveGeneration;
    int i;
    int k;
    int *p1;
    int *p2;
    int *p3;
    int *newP;

    successiveGeneration = (int *) calloc(cellSize, sizeof(int));
    if (successiveGeneration == NULL)
    {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1);  /* abort the program */
    }

    printGeneration(cellSize, arr);


    p1 = arr;
    p2 = arr + 1;
    p3 = arr + 2;
    newP = successiveGeneration;

    *newP = 0;
    *(newP + cellSize - 1) = 0;
    newP = successiveGeneration + 1;


    for (k = 0; k < generations; k++)
    {
        p1 = arr;
        p2 = arr + 1;
        p3 = arr + 2;
        newP = successiveGeneration;

        *newP = 0;
        *(newP + cellSize - 1) = 0;
        newP = successiveGeneration + 1;

        for (i = 1; i < cellSize - 1; i++)
        {
            if ((*p2 == 0) && (*p1 ^ *p3))
            {
                *newP = 1;
            }

            else
            {
                *newP = 0;
            }
            p1++; p2++; p3++; newP++;
        }

        printGeneration(cellSize, successiveGeneration);
        replace(cellSize, successiveGeneration, arr);
    }
    
    free(successiveGeneration);
}

/* 
@brief: This is the main function. It will handle all inputline
 arguments and proceed accordingly.

@param: argc - number of input arguments
       argv[] - contains all input arguments

@return: n/a - ends the program
*/


int main(int argc, char* argv[])
{

    int numCells;
    int numGenerations;
    int *generation1;

    if (argc != 3)
    {
        fprintf(stderr, "%s has incorrect number of inputs.\n", argv[0]);
        return 1;       
    }

    numCells = atoi(argv[1]);
    numGenerations = atoi(argv[2]);

    generation1 = (int *) calloc(numCells, sizeof(int));
    if (generation1 == NULL)
    {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1);  /* abort the program */
    }

    getFirst(numCells, generation1);
    update(numCells, numGenerations, generation1);
    free(generation1);

    print_memory_leaks();
    
    return 0;
}


