/*
@ brief: This program uses recursion to analyze if a particular layout of 
pins to begin a triangle game can yield a solution with only one pin left 
on the board to close the game. If so, the solution will be printed out 
and if not, the program will exit with a message saying just that .

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "triangle_routines.h"

#define BOARD_SIZE 15       /* 15 slots for pegs */
#define NMOVES 36           /* Number of possible moves */


void make_move(int board[], int move[]);
int npegs(int board[]);
int valid_move(int board[], int move[]);
void make_move(int board[], int move[]);
void unmake_move(int board[], int move[]);
int solve(int board[]);


/* moves consists of all possible hardcoded moves according to 
the rules of Triangle */
int moves[NMOVES][3] =
{
    {0, 1, 3},
    {3, 1, 0},
    {1, 3, 6}, 
    {6, 3, 1},
    {3, 6, 10},
    {10, 6, 3},
    {0, 2, 5},
    {5, 2, 0},
    {2, 5, 9},
    {9, 5, 2},
    {5, 9, 14},
    {14, 9, 5},
    {1, 4, 8},
    {8, 4, 1},
    {2, 4, 7},
    {7, 4, 2},
    {4, 7, 11},
    {11, 7, 4},
    {3, 7, 12},
    {12, 7, 3},
    {5, 8, 12},
    {12, 8, 5},
    {4, 8, 13},
    {13, 8, 4},
    {3, 4, 5},
    {5, 4, 3},
    {6, 7, 8},
    {8, 7, 6},
    {7, 8, 9},
    {9, 8, 7},
    {10, 11, 12},
    {12, 11, 10},
    {11, 12, 13},
    {13, 12, 11},
    {12, 13, 14},
    {14, 13, 12}
};


/* @brief: Core method of program. It uses recursion to analyze each 
possible board and iterates through all possible moves to look for 
possible solutions 


    @input: board[] - array of 0's and 1's corresponding to slots with no 
    peg or peg, respectively.

    @output: 1 if there is solution. 0 if no solution exists.


*/

int solve(int board[])
{
    int i;
    int solvableOrNah = 0;
    if (npegs(board) == 1)      /* base case: one peg left, game over */
    {
        triangle_print(board);
        return 1;
    }

    else
    {
        for (i = 0; i < NMOVES; i++)
        {
            if (valid_move(board, moves[i]))
            {
                make_move(board, moves[i]);
                solvableOrNah = solve(board);
                unmake_move(board, moves[i]);
                if (solvableOrNah == 1)
                {
                    triangle_print(board);
                    return 1;
                }                
            }

        }
    }

    return 0;
}

/* @brief: Runs the program by asking for input of a specific board and 
then using the solve method to see if a solution exists. If solution does 
exist, it will print out the sequence of boards leading to the solution 
in reverse order. If not, it will say there is no solution. */

int main(void)
{
    int solutionOrNah;
    int board[BOARD_SIZE];
    triangle_input(board);
    solutionOrNah = solve(board);
    if (solutionOrNah == 0)
    {
        printf("This board lacks a solution. \n");
    }
    else
    {
        printf("This board contains the solution outlined above. \n");
    }
    return 0;
}


/* @brief: Determines number of pegs on board.

   @input: a board
   @output: number of pegs on the inputted board
*/

int npegs(int board[])
{
    int i;
    int numberPegs;
    numberPegs = 0;
    for (i = 0 ; i < BOARD_SIZE; i++)
    {
        if (board[i] == 1)
        {
            numberPegs++;
        }
    }

    return numberPegs;

}

/* @brief: Determines if inputted move on inputted board is valid.

   @input: a board, the particular move
   @output: 1 if valid move, 0 if not
*/
int valid_move(int board[], int move[])
{
    if (board[move[2]] == 0 && board[move[1]] == 1 && board[move[0]] == 1)
    {
        return 1;
    }

    return 0;
}

/* @brief: Makes the inputted move on the board

   @input: a board, the particular move
   @output: none
*/
void make_move(int board[], int move[])
{
    board[move[2]] = 1;
    board[move[1]] = 0;
    board[move[0]] = 0;
}



/* @brief: Undoes the inputted move on the board

   @input: a board, the particular move
   @output: none
*/

void unmake_move(int board[], int move[])
{ 
    board[move[2]] = 0;
    board[move[1]] = 1;
    board[move[0]] = 1;
}