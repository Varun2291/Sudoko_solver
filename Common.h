
#define SIZE 9
#define UNASSIGNED 0

void printBoard(int board[SIZE][SIZE]);
bool FindEmptyCell(int grid[SIZE][SIZE], int &row, int &col);
bool IsInRow(int grid[SIZE][SIZE], int row, int num);
bool IsInCol(int grid[SIZE][SIZE], int col, int num);
bool IsInBox(int grid[SIZE][SIZE], int StartRow, int StartCol, int num);
bool isSafe(int grid[SIZE][SIZE], int row, int col, int num);

void ReadPuzzle(const char *fname);
void SetValues(int r, int c, int num);
void GetPuzzle(int puzzleRead[SIZE][SIZE]);