// A Backtracking program in
// C++ to solve Sudoku problem
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// UNASSIGNED is used for empty
// cells in sudoku grid
#define UNASSIGNED 0

// Global variables
int iterations = 0;
ofstream fd("protokolas.txt");
bool skip = false;

// N is used for the size of Sudoku grid.
// Size will be NxN
#define N 9

// This function finds an entry in grid
// that is still unassigned
bool FindUnassignedLocation(int grid[N][N],
	int& row, int& col);

// Checks whether it will be legal
// to assign num to the given row, col
bool isSafe(int grid[N][N], int row,
	int col, int num);

/* Takes a partially filled-in grid and attempts
to assign values to all unassigned locations in
such a way to meet the requirements for
Sudoku solution (non-duplication across rows,
columns, and boxes) */
bool SolveSudoku(int grid[N][N])
{
	int row, col;

	// If there is no unassigned location,
	// we are done
	if (!FindUnassignedLocation(grid, row, col))
	{
		// success!
		return true;
	}

	// Consider digits 1 to 9
	for (int num = 1; num <= 9; num++)
	{
		++iterations;

		if (!skip)
		{
			fd << setw(5) << iterations << ". ";
			for (int i = 0; i < row; ++i)
			{
				fd << "-";
			}
			fd << "C = " << col + 1 << ", R = "<< row + 1 << ", value = " << num;
		}
		skip = true;
		// Check if looks promising
		if (isSafe(grid, row, col, num))
		{
			fd << ". Tinka." << endl;
			skip = false;

			// Make tentative assignment
			grid[row][col] = num;

			// Return, if success
			if (SolveSudoku(grid))
			{
				return true;
			}

			// Failure, unmake & try again
			grid[row][col] = UNASSIGNED;
		}
		if (skip)
		{
			fd << "netinka." << endl;
			skip = false;
		}
	}
	
	// This triggers backtracking
	return false;
}

/* Searches the grid to find an entry that is
still unassigned. If found, the reference
parameters row, col will be set the location
that is unassigned, and true is returned.
If no unassigned entries remain, false is returned. */
bool FindUnassignedLocation(int grid[N][N],
	int& row, int& col)
{
	for (row = 0; row < N; row++)
		for (col = 0; col < N; col++)
			if (grid[row][col] == UNASSIGNED)
				return true;
	return false;
}

/* Returns a boolean which indicates whether
an assigned entry in the specified row matches
the given number. */
bool UsedInRow(int grid[N][N], int row, int num)
{
	for (int col = 0; col < N; col++)
		if (grid[row][col] == num)
		{
			fd << ". Kartojasi eiluteje, ";
			return true;
		}
	return false;
}

/* Returns a boolean which indicates whether
an assigned entry in the specified column
matches the given number. */
bool UsedInCol(int grid[N][N], int col, int num)
{
	for (int row = 0; row < N; row++)
		if (grid[row][col] == num)
		{
			fd << ". Kartojasi stulpelyje, ";
			return true;
		}
	return false;
}

/* Returns a boolean which indicates whether
an assigned entry within the specified 3x3 box
matches the given number. */
bool UsedInBox(int grid[N][N], int boxStartRow,
	int boxStartCol, int num)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (grid[row + boxStartRow]
				[col + boxStartCol] ==
				num)
			{
				fd << ". Kartojasi kvadrate, ";
				return true;
			}
	return false;
}

/* Returns a boolean which indicates whether
it will be legal to assign num to the given
row, col location. */
bool isSafe(int grid[N][N], int row,
	int col, int num)
{
	/* Check if 'num' is not already placed in
	current row, current column
	and current 3x3 box */
	if (grid[row][col] != UNASSIGNED)
	{
		fd << ". Laukas uzimtas, ";
	}
	return !UsedInRow(grid, row, num)
		&& !UsedInCol(grid, col, num)
		&& !UsedInBox(grid, row - row % 3,
			col - col % 3, num)
		&& grid[row][col] == UNASSIGNED;
}

/* A utility function to print grid */
void printGrid(int grid[N][N])
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
			cout << grid[row][col] << " ";
		cout << endl;
	}
}

// Driver Code
int main()
{
	// 0 means unassigned cells
	//int grid[N][N] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
	//				{ 5, 2, 0, 0, 0, 0, 0, 0, 0 },
	//				{ 0, 8, 7, 0, 0, 0, 0, 3, 1 },
	//				{ 0, 0, 3, 0, 1, 0, 0, 8, 0 },
	//				{ 9, 0, 0, 8, 6, 3, 0, 0, 5 },
	//				{ 0, 5, 0, 0, 9, 0, 6, 0, 0 },
	//				{ 1, 3, 0, 0, 0, 0, 2, 5, 0 },
	//				{ 0, 0, 0, 0, 0, 0, 0, 7, 4 },
	//				{ 0, 0, 5, 2, 0, 6, 3, 0, 0 } };

	int grid[N][N];
	string data = "sudoku.txt";
	// Read a Sudoku
	ifstream fp(data);
	if (!fp) {
		cout << "Klaida, failo neimanoma atidaryti!" << endl;
		return 1;
	}
	for (int row = 0; row < N; row++) {  // stop loops if nothing to read
		for (int col = 0; col < N; col++) {
			fp >> grid[row][col];
			if (!fp) {
				cout << "Klaida skaitant elementa is eilutes " << row << ", stulpelio" << col << endl;
				return 1;
			}
		}
	}

	cout << "Sudoku paimtas is failo " << data << " yra: " << endl;
	printGrid(grid);
	cout << endl;

	if (SolveSudoku(grid) == true)
	{
		cout << "Sprendimas rastas!" << endl;
		cout << "Iteraciju atlikta: " << iterations << endl;
		printGrid(grid);
	}	
	else
		cout << "Nera sprendimo";

	return 0;
}
