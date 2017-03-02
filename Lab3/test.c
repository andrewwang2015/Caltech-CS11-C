#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void bubbleSort(int numbers[], int num_elements)
{

    int k = num_elements - 1;
    int temp;
    int i;
    int j; 
    for (i = 0 ; i < num_elements; i++)
    {

        for (int j = 0; j < k; j++)
        {

            if (numbers[j] > numbers[j+1])
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

int main()
{
    int i;
    int array[5] = {-1,3,-6,2,4};
    bubbleSort(array , 5);
   
    for (int i = 0; i < 5; i ++)
    {
        printf("%d\n", array[i]);
    }
    return 0;
}
