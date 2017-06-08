#include<iostream>
#include<conio.h>
#include<math.h>
#include<ctime>
#include "BackTracking_FC.h"
#include "Common.h"

using namespace std;

//int SquareRoot = sqrt(9.0);			// Variable to store the square root of the puzzle board
bool FowardCheck[SIZE][SIZE][SIZE];

bool SolvePuzzle_FC(int grid[SIZE][SIZE])
{
	int row, col;

	// Find the next cell that is empty
	if(!FindEmptyCell(grid, row, col))
		return true;

	//printBoard(grid);cout<<endl;

	// Start checking from 1 to the Max number & check
	// if it is safe
	for(int num = 1; num <= SIZE; num++)
	{
		if(FowardCheck[row][col][num] == true)
		{
			// Check if this [row, col] is safe for this number
			if(isSafe(grid, row, col, num))
			{
				// If it is safe then assign this number
				grid[row][col] = num;
				FowardCheck[row][col][num] == false;

				if(SolvePuzzle_FC(grid))
					return true;

				grid[row][col] = UNASSIGNED;
			}
		}
	}
	return false;
}

void InitializeForwardChecking()
{
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			for(int k = 0; k < SIZE; k++)
				FowardCheck[i][j][k] = true;
}

void CallBackTracking_FCSolver(const char *fname)
{
	int puzzle[SIZE][SIZE];

	InitializeForwardChecking();

	ReadPuzzle(fname);
	GetPuzzle(puzzle);

	if(SolvePuzzle_FC(puzzle) == true)
		printBoard(puzzle);
	else
		cout<<"Not working";
}