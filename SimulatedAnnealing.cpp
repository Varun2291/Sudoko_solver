#include <iostream>
#include <math.h>
#include <time.h> 
#include "Common.h"

using namespace std;
int SquareRoot_SA = sqrt(9.0);			// Variable to store the square root of the puzzle board
bool HardCodedValues[SIZE][SIZE] = {false};

void Initialize(int grid[SIZE][SIZE])
{
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			if(grid[i][j] != UNASSIGNED)
				HardCodedValues[i][j] = true;
}

int BoardCost(int grid[SIZE][SIZE])
{
	int cost = 0;
	int col_cost = 0;
	int row_cost = 0;
	bool rowFlag = true;
	bool colFlag = true;

	// Check row cost
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			rowFlag = true;
			for(int k = 0; k < SIZE; k++)
			{
				if((grid[i][j] == grid[i][k]) && (k != j))
				{
					rowFlag = false;
					break;
				}
			}
			if(rowFlag)
				row_cost--;
		}
	}

	// Check column cost
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			colFlag = true;
			for(int k = 0; k < SIZE; k++)
			{
				if((grid[j][i] == grid[k][i]) && (k != j))
				{
					colFlag = false;
					break;
				}
			}
			if(colFlag)
				col_cost--;
		}
	}

	cost = row_cost + col_cost;
	return cost;
}

void copyBoard(int src[SIZE][SIZE], int dest[SIZE][SIZE])
{
	int **temp = new int*[SIZE];
	for(int k = 0; k < SIZE; ++k)
	{
		temp[k] = new int[SIZE];
	}

	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			temp[i][j] = src[i][j];

	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			dest[i][j] = temp[i][j];
	
	for(int k = 0; k < SIZE; ++k)
	{
		delete[] temp[k];
	}
	delete[] temp;
}

int getBlockIndices(int k)
{
	int row_offset = (k / SquareRoot_SA) * SquareRoot_SA;
	int col_offset = (k % SquareRoot_SA) * SquareRoot_SA;
	int indices;
	for(int i = 0; i < SIZE; i++)
	{
		indices = col_offset + (i%3) + 9*(row_offset + (i/3));
	}
	return indices;
}

void randomize(int grid[SIZE][SIZE])
{
	int num;
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			if(grid[i][j] == 0)
			{
				while(1)
				{
					// Generate a random number and check if it present in the block
					// go to the next iteration only of filling the current black
					num = rand() % SIZE + 1;
					if(!IsInBox(grid, i - i % SquareRoot_SA, j - j % SquareRoot_SA, num))
					{
						grid[i][j] =  num;
						break;
					}
				}
			}
}

void swapCells(int src[SIZE][SIZE], int result[SIZE][SIZE])
{
	// Pick random row and column, checks its block,
	// pick another row and column within the block, swap two cells within that block 
	// return the new array
	int row1, row2, col1, col2, start_row, start_col;

	copyBoard(src, result);
	while(1)
	{
		while(1)
		{
			row1 = rand() % SIZE;
			col1 = rand() % SIZE;
			if(HardCodedValues[row1][col1] == false)
				break;
		}

		start_row = row1 - row1 % SquareRoot_SA;
		start_col = col1 - col1 % SquareRoot_SA;

		while(1)
		{
			row2 = rand() % SquareRoot_SA + start_row;
			col2 = rand() % SquareRoot_SA + start_col;
			if(HardCodedValues[row2][col2] == false)
				break;
		}
		if(row1 != row2 || col1 != col2)
			break;
	}

	int temp[1][1] = {0};
	temp[0][0] = result[row1][col1];

	result[row1][col1] = result[row2][col2];
	result[row2][col2] = temp[0][0];
}

/*
void swapCells(int src[SIZE][SIZE], int result[SIZE][SIZE])
{
	// Pick a random block, swap two cells within that block 
	// return the new array

//	cout<<endl<<"Parent:";
//	printBoard(src);

	copyBoard(src, result);
	//srand (time(NULL));
	int rand_row = rand() % SIZE;
	//srand (time(NULL));
	int rand_col = rand() % SIZE;

	int start_row = rand_row - rand_row % SquareRoot_SA;
	int start_col = rand_col - rand_col % SquareRoot_SA;

	int row1, row2, col1, col2;
	
	while(1)
	{
		//srand (time(NULL));
		while(1)
		{
		//	srand (time(NULL));
			row1 = rand() % SquareRoot_SA + start_row;
		//	srand (time(NULL));
			col1 = rand() % SquareRoot_SA + start_col;
			if(HardCodedValues[row1][col1] == false)
				break;
		}
		while(1)
		{
		//	srand (time(NULL));
			row2 = rand() % SquareRoot_SA + start_row;
		//	srand (time(NULL));
			col2 = rand() % SquareRoot_SA + start_col;
			if(HardCodedValues[row2][col2] == false)
				break;
		}
		if(row1 != row2 || col1 != col2)
			break;
	}

	int temp[1][1] = {0};
	temp[0][0] = result[row1][col1];

	result[row1][col1] = result[row2][col2];
	result[row2][col2] = temp[0][0];
//	cout<<endl<<"Result: ";
//	printBoard(result);
//	cout<<"("<<row1<<","<<col1<<")  ("<<row2<<","<<col2<<")";
}
*/
/*void CheckLocalMinimum(int grid[SIZE][SIZE])
{
	int count = 1;
	int index_2 = 0;

	// Check row
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			count = 1;
			for(int k = 0; k < SIZE; k++)
			{
				if((grid[i][j] == grid[i][k]) && (k != j))
				{
					index_2 = k;
					count++;
				}
			}
			if(count >= 2)
			{
				grid[i][j] = UNASSIGNED;
				grid[i][index_2] = UNASSIGNED;
				for(int num = 1; num <= SIZE; num++)
				{
					if(isSafe(grid, i, j, num))
					{
						grid[i][j] = num;
						break;
					}
				}

				for(int num = 1; num <= SIZE; num++)
				{
					if(isSafe(grid, i, index_2, num))
					{
						grid[i][index_2] = num;
						break;
					}
				}
				if(grid[i][j] == UNASSIGNED || grid[i][index_2] == UNASSIGNED)
					randomize(grid);
			}
		}
	}

	// Check column
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			count = 1;
			for(int k = 0; k < SIZE; k++)
			{
				if((grid[j][i] == grid[k][i]) && (k != j))
				{
					index_2 = k;
					count++;
				}
			}
			if(count >= 2)
			{
				grid[i][j] = UNASSIGNED;
				grid[i][index_2] = UNASSIGNED;
				for(int num = 1; num <= SIZE; num++)
				{
					if(isSafe(grid, i, j, num))
					{
						grid[i][j] = num;
						break;
					}
				}

				for(int num = 1; num <= SIZE; num++)
				{
					if(isSafe(grid, i, index_2, num))
					{
						grid[i][index_2] = num;
						break;
					}
				}
				if(grid[i][j] == UNASSIGNED || grid[i][index_2] == UNASSIGNED)
					randomize(grid);
			}
		}
	}
}
*/

bool FixLocalMinimum(int grid[SIZE][SIZE])
{
	int row, col;

	if(!FindEmptyCell(grid, row, col))
		return true;

	for(int num = 1; num <= SIZE; num++)
	{
		if(isSafe(grid, row, col, num))
		{
			grid[row][col] = num;

			if(FixLocalMinimum(grid))
				return true;

			grid[row][col] = UNASSIGNED;
		}
	}
	return false;
}

void CheckLocalMinimum(int grid[SIZE][SIZE])
{
	int count = 1;
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			count = 1;
			for(int k = 0; k < SIZE; k++)
			{
				if((grid[i][j] == grid[i][k]) && (k != j))
				{
					grid[i][k] = UNASSIGNED;
					count++;
				}
			}
			if(count >= 2)
				grid[i][j] = UNASSIGNED;
		}
	}

	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			count = 1;
			for(int k = 0; k < SIZE; k++)
			{
				if((grid[j][i] == grid[k][i]) && (k != j))
				{
					grid[k][i] = UNASSIGNED;
					count++;
				}
			}
			if(count >= 2)
				grid[j][i] = UNASSIGNED;
		}
	}
	printBoard(grid);
	FixLocalMinimum(grid);
}

bool SolvePuzzle_SA(int board[SIZE][SIZE])
{
	printBoard(board);
	randomize(board);
	
	int temp_board[SIZE][SIZE];
	int swaped_board[SIZE][SIZE] = {0};
	copyBoard(board, temp_board);
	int currentScore = BoardCost(board);
	int bestScore = currentScore;
	int swapedScore = 0;
	double delta;

	double t = 0.5;
	int count = 0;

	cout<<endl<<"Processing...";
	while(count < 10000000)
	{
		try
		{
			//if((count % 1000) == 0)
			//	cout<<endl<<"Iteration "<<count<<" \tT= "<<t<<" \tBest Score= "<<bestScore<<"\tcurrent_score= "<<currentScore;
			memset(swaped_board, 0, sizeof(swaped_board));
			swapCells(board, swaped_board);
			swapedScore = BoardCost(swaped_board);
			delta = double(currentScore - swapedScore);
	
			if(exp((delta/t)) - rand() > 0)
			{
				copyBoard(swaped_board, board);
				currentScore = swapedScore;
			}
			
			if(currentScore < bestScore)
			{
				copyBoard(board, temp_board);
				bestScore = BoardCost(temp_board);
			}

			if(swapedScore == -162)
			{
				board = swaped_board;
				break;
			}

			t = 0.99999 * t;
			count++;
		}
		catch(exception e)
		{
		}
	}
	if(swapedScore == -162)
	{
	//	printBoard(board);
		return true;
	}
	else
		return false;
}

void CallSimulatedAnnealing_Solver(const char *fname)
{
	int puzzle[SIZE][SIZE];

	ReadPuzzle(fname);
	GetPuzzle(puzzle);

	Initialize(puzzle);

	if(SolvePuzzle_SA(puzzle) == true)
		printBoard(puzzle);

	printBoard(puzzle);
}