#include<list>

class Index
{
public:
		int row;
		int col;

		Index() {
		}
	    Index(int row, int col) {
			this->row = row;
			this->col = col;
		}
};

class puzzle
{
public:
	class puzzleval
	{
	public:
		std::list<int> value;
	};

	puzzleval grid[SIZE][SIZE];
};

bool revise(int grid[SIZE][SIZE], Index i, Index j);
std::list<int> getDomain(int row, int col);
void removeFromDomain(int row, int col, int value);
int getDomainLength(int row, int col);
void CallBacktracking_AC3(const char *fname);