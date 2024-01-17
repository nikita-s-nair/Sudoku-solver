/*
Code Overview:
• The main() function takes the sudoku as user input.
• The isAllowed() function checks if a number can be safely placed in a given position without violating any of the game rules.
• The solveSudoku() function solves the puzzle using backtracking.
• The printSudoku() function displays the solved sudoku grid.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// defining the sudoku size
#define N 9

// function to check if a number can be placed in a given cell
bool isAllowed(int puzzle[N][N], int row, int col, int num)
{
    // check if the number exists in the current row or column
    for (int i = 0; i < N; i++)
    {
        if (puzzle[row][i] == num || puzzle[i][col] == num)
        {
            return false;
        }
    }

    // check if the number exists in the current 3x3 grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (puzzle[i + startRow][j + startCol] == num)
            {
                return false;
            }
        }
    }

    return true;
}

// function to solve the sudoku puzzle using backtracking
bool solveSudoku(int puzzle[N][N])
{
    int row, col;

    // find an empty cell
    bool empty_cell = false;
    for (row = 0; row < N; row++)
    {
        for (col = 0; col < N; col++)
        {
            if (puzzle[row][col] == 0)
            {
                empty_cell = true;
                break;
            }
        }
        if (empty_cell)
        {
            break;
        }
    }

    // when there are no empty cells, the puzzle is solved
    if (!empty_cell)
    {
        return true;
    }

    // try to place a number in the empty cell
    for (int num = 1; num <= N; num++)
    {
        if (isAllowed(puzzle, row, col, num))
        {
            puzzle[row][col] = num;

            // recursively solve for the rest of the puzzle
            if (solveSudoku(puzzle))
            {
                return true;
            }

            // if placing the number doesn't lead to a solution, backtrack
            puzzle[row][col] = 0;
        }
    }

    // if no number can be placed, return false
    return false;
}

// function to print the sudoku puzzle
void printSudoku(int puzzle[N][N])
{
    for (int row = 0; row < N; row++)
    {
        if (row % 3 == 0 && row != 0)
        {
            printf("+-----|-------|------+\n");
        }
        for (int col = 0; col < N; col++)
        {
            if (col % 3 == 0 && col != 0)
            {
                printf("| ");
            }
            printf("%d ", puzzle[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int puzzle[N][N];

    // taking user input for the sudoku puzzle
    printf("Enter the sudoku puzzle (enter 0 for empty cells):\n");
    for (int i = 0; i < N; i++)
    {
        printf("Enter numbers for row %d (separated by space): ", i + 1);
        int numCount = 0; // counter for the number of inputs in the row
        for (int j = 0; j < N; j++)
        {
            while (1)
            {
                char *num;
                if (scanf(" %s", &num) == 1)
                {
                    int x = num - '0';
                    if (x >= 0 && x <= 9)
                    {
                        puzzle[i][j] = x;
                        numCount++;
                        break;
                    }
                    else
                    {
                        printf("Please enter a number between 0 and 9.\n");
                        continue;
                    }
                }
                else
                {
                    printf("Invalid input. Please enter 9 numbers separated by space.\n");
                }
            }
        }

        // check if the user entered less than 9 numbers in the row
        if (numCount < N)
        {
            printf("Invalid input. Please enter exactly 9 numbers.\n");
            i--; // prompt the user to re-enter the current row
        }
    }

    if (solveSudoku(puzzle))
    {
        printf("\nThe Solved Sudoku:\n");
        printSudoku(puzzle);
    }
    else
    {
        printf("\nNo solution exists.\n");
        printf("\nKindly check for any errors in the puzzle while entering and try again.\n");
        printf("\n");
    }
    return 0;
}