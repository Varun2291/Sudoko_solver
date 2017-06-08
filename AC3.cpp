#include<cstdio>
#include<iostream>
#include<map>
#include<queue>
#include<list>
#include<time.h>

#include "Common.h"
#include "AC3.h"

using namespace std;

bool Ac3FinalArray[SIZE][SIZE][SIZE];
bool Ac3TempArray[SIZE][SIZE][SIZE];
std::map<int,int> arc_map;

std::list<int> getDomain(int row, int col)
{
	std::list<int> val;
	for (int num = 1 ; num <= 9 ; num++)
	{
		val.push_back(num);
	}
	return val;
}

void removeFromDomain(int row, int col, int value)
{
	Ac3TempArray[row][col][value] = false;
}

int getDomainLength(int row, int col)
{
	int count = 0;
	for(int i = 0; i < SIZE; i++)
		if(Ac3TempArray[row][col][i] == true)
			count++;
	return count;
}

void InitializeAC3()
{
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			for(int k = 0; k < SIZE; k++)
				Ac3FinalArray[i][j][k] = true;
}

bool revise(int grid[SIZE][SIZE], int i, int j, int k, int l) 
{
	bool revised = false;

	std::list<int> domainI = getDomain(i, j);
	std::list<int> domainJ = getDomain(k, l);

	std::list<int>::const_iterator iterator_x;
	std::list<int>::const_iterator iterator_y;

	for(iterator_x = domainI.begin(); iterator_x != domainI.end(); ++iterator_x)
	{
		bool satisfiable = false;
 
		for(iterator_y = domainJ.begin(); iterator_y != domainJ.end(); ++iterator_y)
		{
			if (*iterator_y != *iterator_x) 
				satisfiable = true;
		}

		if (!satisfiable) 
		{
			removeFromDomain(i, j, *iterator_x);
			revised = true;
		}
	}
	return revised; 
}

void prepareQueue(int grid[SIZE][SIZE], std::map<int,int> arc_map) 
{
	for (int assignedRow = 0; assignedRow < SIZE; assignedRow++) 
	{
		for (int assignedCol = 0; assignedCol < SIZE; assignedCol++) 
		{
			// Queue squares in current unit 
			int startRow = (assignedRow / 3) * 3;
			int startCol = (assignedCol / 3) * 3;
			int endRow = startRow + SIZE;
			int endCol = startCol + SIZE;

			for (int row = startRow; row < endRow; row++) 
			{
				for (int col = startCol; col < endCol; col++) 
				{
					if (row != assignedRow && col != assignedCol) 
					{
				      arc_map.insert(std::pair<int,int>(row, col));
					}
				}
			}

			// Queue squares in current row 
			for (int row = 0; row < SIZE; row++) 
			{
				if (row != assignedRow) 
				{
					arc_map.insert(std::pair<int,int>(row, assignedCol));
				}
			}

			// Queue squares in current column 
			for (int col = 0; col < SIZE; col++) 
			{
				if (col != assignedCol) 
				{
					arc_map.insert(std::pair<int,int>(assignedRow, col));
				}
			}
		}
	}
}

bool SolvePuzzle_AC3(int board[SIZE][SIZE])
{
	int row, col;

	if(!FindEmptyCell(board, row, col))
		return true;

	// Start checking from 1 to the Max number & check
	// if it is safe
	for(int num = 1; num <= SIZE; num++)
	{
		if(Ac3FinalArray[row][col][num] == true)
		{
			// Check if this [row, col] is safe for this number
			if(isSafe(board, row, col, num))
			{
				// If it is safe then assign this number
				board[row][col] = num;
				Ac3FinalArray[row][col][num] == false;

				if(SolvePuzzle_AC3(board))
					return true;

				board[row][col] = UNASSIGNED;
			}
		}
	}
	return false;
}

bool AC3(int grid[SIZE][SIZE]) 
{
	std::map<int,int> arcs;
	prepareQueue(grid, arcs);

	auto iter = arcs.begin();

	while (arcs.size() > 0) 
	{
		int edge[4] = {};

		// Get the 1st pair
		edge[0] = iter->first;
		edge[1] = iter->second;
		iter++;
		// Get the next pair
		edge[2] = iter->first;
		edge[3] = iter->second;

		if (!revise(grid, edge[0], edge[1], edge[2], edge[3])) 
			continue;

		int assignedRow = edge[0];
		int assignedCol = edge[1];
		int otherRow = edge[2];
		int otherCol = edge[3];

		if (getDomainLength(assignedRow, assignedCol) == 0) 
			return false;

		// Queue squares in current unit 
		int startRow = (assignedRow / 3) * 3;
		int startCol = (assignedCol / 3) * 3;
		int endRow = startRow + 3;
		int endCol = startCol + 3;

		for (int row = startRow; row < endRow; row++) 
		{
			for (int col = startCol; col < endCol; col++) 
			{
				if (row != assignedRow && col != assignedCol && row != otherRow && col != otherCol) 
				{
					arc_map.insert(std::pair<int, int>(row, col));
				}
			}
		}

		// Queue squares in current row 
		for (int row = 0; row < SIZE; row++) 
		{
			if (row != assignedRow && row != otherRow) 
			{
				arc_map.insert(std::pair<int,int>(row, assignedCol));
			}
		}

		// Queue squares in current column 
		for (int col = 0; col < SIZE; col++) 
		{
			if (col != assignedCol && col != otherCol) 
			{
				arc_map.insert(std::pair<int,int>(assignedRow, col));
			}
		}
		iter++;
	}
	
	return true;
}
		
void CallBacktracking_AC3(const char *fname)
{
	int puzzle[SIZE][SIZE];
	//const char *fname = "C:\\Users\\Yashasvi\\Downloads\\AI\\Sudoku\\puzzle-5-hard.txt";

	InitializeAC3();

	ReadPuzzle(fname);
	GetPuzzle(puzzle);
	//printBoard(puzzle);
	if(SolvePuzzle_AC3(puzzle) == true)
		printBoard(puzzle);
	else
		cout<<"Not working";
}