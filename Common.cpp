#include<cstdio>
#include<iostream>

#include "Common.h"

using namespace std;

int puzzle[SIZE][SIZE] = {0};		// Variable to store the puzzle
int SquareRoot = sqrt(9.0);			// Variable to store the square root of the puzzle board

// Function to print the board
void printBoard(int board[SIZE][SIZE])
{
	cout<<endl;
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
			cout<<board[i][j]<<" ";
		cout<<endl;
	}
}

// Function to find the empty cell in the puzzle
// The function returns the row and column value of the next empty cell
bool FindEmptyCell(int grid[SIZE][SIZE], int &row, int &col)
{
	for(row = 0; row < SIZE; row++)
	{
		for(col = 0; col < SIZE; col++)
		{
			if(grid[row][col] == UNASSIGNED)
				return true;
		}
	}
	return false;
}

// Function to check if the 'num' is present in current row
bool IsInRow(int grid[SIZE][SIZE], int row, int num)
{
	for(int col = 0; col < SIZE; col++)
		if(grid[row][col] == num)
			return true;
	return false;
}

// Function to check if the 'num' is present in current column
bool IsInCol(int grid[SIZE][SIZE], int col, int num)
{
	for(int row = 0; row < SIZE; row++)
		if(grid[row][col] == num)
			return true;
	return false;
}

// Function to check if the 'num' is present in current Box
bool IsInBox(int grid[SIZE][SIZE], int StartRow, int StartCol, int num)
{
	for(int row = 0; row < SquareRoot; row++)
		for(int col = 0; col < SquareRoot; col++)
			if(grid[row+StartRow][col+StartCol] == num)
				return true;
	return false;
}

// Function to check if the 'num' is safe to use, i.e. 
// check in the current, column and Box
bool isSafe(int grid[SIZE][SIZE], int row, int col, int num)
{
	return (!IsInRow(grid, row, num) && !IsInCol(grid, col, num) &&
		!IsInBox(grid, row - row % SquareRoot, col - col % SquareRoot, num));
}

void SetValues(int r, int c, int num)
{
	puzzle[r][c] = num;
}

void GetPuzzle(int puzzleRead[SIZE][SIZE])
{
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			puzzleRead[i][j] = puzzle[i][j];
}

void ReadPuzzle(const char *fname)
{
	FILE *ptr = fopen(fname, "r");
	int val;

	if(!ptr)
	{
		cout<<"Not able to open the file: "<<fname;
		return;
	}

	if(fscanf(ptr, "%d", &val) != 1)
	{
		cout<<"Error: Expecting Size of the puzzle: "<<fname;
		fclose(ptr);
		return;
	}

	for(int r = 0; r < SIZE; r++)
	{
		for(int c = 0; c < SIZE; c++)
		{
			if(fscanf(ptr, "%d", &val) != 1)
			{
				cout<<"Error: Expecting values: "<<fname;
				fclose(ptr);
				return;
			}
			SetValues(r, c, val);
		}
	}
	fclose(ptr);
}