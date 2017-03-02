/* This program takes in commmand line arguments consisting of 
options to specify either a bubble sort, minimal sort, or 
no output and up to 32 numbers with which to sort. */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX_SIZE 32  /* maximum number of inputted numbers */   
void minimalSort(int numbers[], int num_elements);
void bubbleSort(int numbers[], int num_elements);

/* This function is the bubble sort method. At each step, 
if two adjacent elements of a list are not in order, 
they will be swapped. Thus, bigger elements will "bubble" 
to the front.

Input: numbers [] - array of numbers from input
       num_elements - size of array passed in

Output: sorted array via bubble sort
*/

void bubbleSort(int numbers[], int num_elements)
{

    int k = num_elements - 1;
    int temp;
    int i;
    int j; 
    for (i = 0 ; i < num_elements; i++)
    {

        for (j = 0; j < k; j++)
        {

            if (numbers[j] > numbers[j+1])      /* Swapping */
            {
                temp = numbers[j];
                numbers[j] = numbers[j+1];
                numbers[j+1] = temp;


            }
        }
        k--;
    }

    for (i = 1; i < num_elements; i++)
    {
        assert(numbers[i] >= numbers[i-1]); 
    }
}

/* This function is the minimal sort method. It is detailed below:

Let array be the array of integers, and num_elements be the total number 

 elements in array.

Start with start = 0 (for the index of the zeroth element).

Set smallest = start (smallest stores the index of 
the smallest element encountered so far).

Run through a loop with the variable index going from 
start to num_elements

If array[index] < array[smallest], set   smallest = index.

Once the loop ends, swap array[start] and array[smallest] 

(moving the smallest element found to the beginning of the

 array you searched).

Increment start, and if start < num_elements, go back to step 2. 
Do not use a goto statement, however; use another loop.

If start >= num_elements then you're done and the array is sorted.

Input: numbers [] - array of numbers from input
       num_elements - size of array passed in

Output: sorted array via minimal sort
*/

void minimalSort(int numbers[], int num_elements)
{
    int start = 0;
    int smallest = start;
    int i;
    int temporarySwap;
    while (start < num_elements)
    {
        smallest = start;
        for (i = start; i < num_elements; i++)
        {
            if (numbers[i] < numbers[smallest])
            {
                smallest = i;
            }
        }
        temporarySwap = numbers[start];
        numbers[start] = numbers[smallest];
        numbers[smallest] = temporarySwap;
        start++;
    }


    for (i = 1; i < num_elements; i++)
    {
        assert(numbers[i] >= numbers[i-1]);
    }
}


/* This is the main function. It will handle all inputline
 arguments and proceed accordingly.

Input: argc - number of input arguments
       argv[] - contains all input arguments

Output: n/a Will just end the program. 
*/

int main(int argc, char* argv[])
{   
    int array[MAX_SIZE];
    int number = 0;
    int i;
    int quiet = 0;
    int bubble = 0;


    for (i = 0; i < MAX_SIZE; i++)
    {
        array[i] = 0;           /* Initializes all elements to 0 */
    }


    if (argc < 2)
    {
        fprintf(stderr, "usage: %s [-b] [-q] number 1 [number2...] \
            (maximum 32 numbers)\n", argv[0]);
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


            else if (strcmp(argv[i], "-b") == 0)
            {

                bubble = 1;
            }

            else
            {

                if (number < 32)
                {
                    array[number] = atoi(argv[i]);
                    number++;
                }
                else
                {
                    fprintf(stderr, "No numbers were entered. usage: \
                        %s   [-b] [-q] number 1 [number2...] \
                        (maximum 32 numbers)\n", argv[0]);
                    return 2;   /* If more than 32 inputs (not allowed) */
                }                  

            }
        }
    }


    if (bubble == 1)            /* If the -b option is inputted */
    {
        bubbleSort(array, number);
    }

    else
    {
        minimalSort(array, number);
    }

    if (quiet == 1)     /* If the -q option is inputted */
    {
        return 0;   /* suppresses output */
    }


    for (i = 0 ; i < (number) ; i++)
    {
        printf("%d \n", array[i]);
    }

    return 0;
}

    