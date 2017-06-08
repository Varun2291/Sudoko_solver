#include<cstdio>
#include<iostream>
#include "BackTrack_VertexOrder.h"
#include "Common.h"
#include <ctime>

using namespace std;

//int puzzle[SIZE][SIZE] = {0};

bool FindEmptyCell_MRV(int grid[SIZE][SIZE], int &mr_row, int &mr_col)
{
	int row, col;
	int min = SIZE+1;
	int count = 0;
	int min_row = 0;
	int min_col = 0;
	for(row = 0; row < SIZE; row++)
	{
		count = 0;
		for(col = 0; col < SIZE; col++)
		{
			if(grid[row][col] == UNASSIGNED)
				count++;		
		}
		if((count < min) && (count != 0))
		{
			min_row = row;
			min = count;
		}
	}
	for(col =0; col< SIZE; col++)
	{ 
		if(grid[min_row][col] == UNASSIGNED)
		{
			min_col = col;
			mr_row = min_row;
			mr_col = min_col;
			return true;
		}
	}
	return false;
}

bool SolvePuzzle_MRV(int grid[SIZE][SIZE])
{
	int row, col;

	//printBoard(grid);cout<<endl;

	if(!FindEmptyCell_MRV(grid, row, col))
		return true;

	// Start checking from 1 to the Max number & check
	// if it is safe
	for(int num = 1; num <= SIZE; num++)
	{
		// Check if this [row, col] is safe for this number
		if(isSafe(grid, row, col, num))
		{
			// If it is safe then assign this number
			grid[row][col] = num;

			if(SolvePuzzle_MRV(grid))
				return true;

			grid[row][col] = UNASSIGNED;
		}
	}
	return false;
}

void CallBackTrackingSolver_VertexOrder(const char *fname)
{
	int puzzle[SIZE][SIZE];

	ReadPuzzle(fname);
	GetPuzzle(puzzle);

	if(SolvePuzzle_MRV(puzzle) == true)
		printBoard(puzzle);
	else
		cout<<"Not working";
}