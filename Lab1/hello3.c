#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
    int i;
    char s[100];

    int randomNum;

      
    srand(time(0));
    randomNum = rand() % 10 + 1;  
    printf("Enter your name: ");
    scanf("%99s", s);

    
    if (randomNum % 2 == 0)
    {
        for (i = 0; i < randomNum ; i++)
        {
            printf("%d: hello, %s! \n", randomNum, s);
        }
    }

    else {
        for (i = 0; i < randomNum ; i++)
        {
            printf("%d: hi there, %s! \n", randomNum, s);
        }        
    }
    
    return 0;
}