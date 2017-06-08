#include<iostream>
#include<conio.h>
#include<math.h>
#include<ctime>

#include "BackTracking.h"
#include "Common.h"

using namespace std;

bool SolvePuzzle(int grid[SIZE][SIZE])
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
		// Check if this [row, col] is safe for this number
		if(isSafe(grid, row, col, num))
		{
			// If it is safe then assign this number
			grid[row][col] = num;

			if(SolvePuzzle(grid))
				return true;

			grid[row][col] = UNASSIGNED;
		}
	}
	return false;
}

void CallBackTrackingSolver(const char *fname)
{
	int puzzle[SIZE][SIZE];

	clock_t startTime = clock();
	ReadPuzzle(fname);
	GetPuzzle(puzzle);

	if(SolvePuzzle(puzzle) == true)
		printBoard(puzzle);
	else
		cout<<"Not working";

}