/* This program uses Knuth's algorithm to compute the day of the year on which 
Easter falls for all years in an input file
and outputs it to another file */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
bool zellerCongruence (int day, int month, int year);
int calculate_Easter_date(int year); 

/*
"calculate_Easter_date" takes the year of interest as an integer and returns an
integer corresponding to a particular date. If the return integer is n and n 
is negative, then the integer corresponds to March n. If the return integer is 
n and n is positive, then the return integer corresponds to April (31 - n). 
This function uses Knuth's algorithm to compute the day of the year
on which Easter falls. 

*/

bool zellerCongruence (int day, int month, int year)
{
    int dayOfWeek;
    int yearOfCentury;
    int zeroBasedCentury;
    yearOfCentury = year % 100;
    zeroBasedCentury = year / 100;
    if (month == 1)
    {
        month = 13;
        year --;
    }

    if (month == 2)
    {
        month = 14;
        year --;
    }

    dayOfWeek = (day + 13 * (month + 1) / 5 + yearOfCentury + yearOfCentury/4 + 
        zeroBasedCentury / 4 + 5 * zeroBasedCentury);
    dayOfWeek = dayOfWeek % 7;
    return (dayOfWeek == 1);
}

int calculate_Easter_date(int year)
{
    int goldenYear;   /* how many years into metonic cycle we are in */
    int century;
    int skippedLeap;
    int correctionFactor;   /* Because we assume moon orbits earth 235 times */            
    int guaranteedSunday;
    int epact;          /* age of moon at beginning of year */
    int finalScaling;

    if (year < 1582 || year > 39999)    /* out of range */
    {
        return 0;
    }
    goldenYear = year % 19 + 1;   /* due to Metonic cycle */
    century = year / 100 + 1;
    skippedLeap = 3 * century / 4 - 12;
    correctionFactor = (8 * century + 5) / 25 - 5;
    guaranteedSunday = 5 * year / 4 - skippedLeap - 10;
    epact = (11 * goldenYear + 20 + correctionFactor - skippedLeap) % 30;
    if ((epact == 25 && goldenYear > 11) || epact == 24)
    {
        epact++;
    }
    finalScaling = 44 - epact;
    if (finalScaling < 21)
    {
        finalScaling += 30;
    }

    finalScaling = finalScaling + 7 - ((guaranteedSunday + finalScaling) % 7);
    if (finalScaling > 31)
    {
        return (finalScaling - 31);/* corresponds to April (finalScaling - 31)*/
    }

    return (-1 * finalScaling);       /* corresponds to March (finalScaling) */
    
    
}

int main (void)
{
    int inputYear;
    int testIfEnd;
    int output;

    
    while (1 == 1)
    {
        testIfEnd = scanf("%d", &inputYear);
        if (testIfEnd == EOF)
        {
            break;
        }

        output = calculate_Easter_date(inputYear);
        if (output == 0)
        {
            fprintf(stderr, "Year not in range!");
        }

        else if (output < 0)
        {
            assert(zellerCongruence(-1 * output, 3, inputYear));
            printf("%d - March %d \n", inputYear,  -1 * output);
            
        }

        else 
        {
            assert(zellerCongruence(output, 4, inputYear));
            printf("%d - April %d \n", inputYear,  output);
        }


    }

    return 0;

}