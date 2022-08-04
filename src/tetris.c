#include "tetris.h"

char Table[ROWS][COLS] = {0};
char canGameContinue = TRUE;

Piece current;

int checkPosition(Piece piece) // check position of copied piece
{
	char **array = piece.array;
	int i, j;
	for (i = 0; i < piece.width; i++)
	{
		for (j = 0; j < piece.width; j++)
		{
			if ((piece.col + j < 0 || piece.col + j >= COLS || piece.row + i >= ROWS))
			{					 // out of borders
				if (array[i][j]) // but is it just a phantom?
					return FALSE;
			}
			else if (Table[piece.row + i][piece.col + j] && array[i][j])
				return FALSE;
		}
	}
	return TRUE;
}

void getNewPiece() // return s rondom piece
{
	Piece new = copyPiece(getRandomPiece());
	new.col = rand() % (COLS - new.width + 1);
	new.row = 0;
	deletePiece(current);
	current = new;
	if (!checkPosition(current))
	{
		canGameContinue = FALSE;
	}
}

void writeToTable()
{
	int i, j;
	for (i = 0; i < current.width; i++)
	{
		for (j = 0; j < current.width; j++)
		{
			if (current.array[i][j])
				Table[current.row + i][current.col + j] = current.array[i][j];
		}
	}
}

int isLineFilled(int row, char table[ROWS][COLS])
{
	int i;
	for (i = 0; i < COLS; i++)
		if (table[row][i] == 0)
			return FALSE;
	return TRUE;
}

void deleteLine(int row)
{
	int i, j;
	for (i = row; i >= 1; i--)
		for (j = 0; j < COLS; j++)
			Table[i][j] = Table[i - 1][j];
	for (j = 0; j < COLS; j++)
		Table[0][j] = 0;
}

void checkLines()
{
	int i, count = 0;
	for (i = 0; i < ROWS; i++)
	{
		if (isLineFilled(i, Table))
		{
			count++;
			deleteLine(i);
			decreaseGraceTime();
		}
	}
	addScore(count);
}

void manipulateCurrent(int action)
{
	Piece tmp = copyPiece(current);
	switch (action)
	{
	case 's':
		tmp.row++; // move down
		if (checkPosition(tmp))
			current.row++;
		else
		{
			writeToTable();
			checkLines(); // check full lines, after putting it down
			getNewPiece();
		}
		break;
	case 'd':
		tmp.col++; // move right
		if (checkPosition(tmp))
			current.col++;
		break;
	case 'a':
		tmp.col--; // move left
		if (checkPosition(tmp))
			current.col--;
		break;
	case 'w':
		rotatePiece(tmp);
		if (checkPosition(tmp))
			rotatePiece(current);
		break;
	}
	deletePiece(tmp);
	printTable(current, Table, getScore());
}

int main()
{
	srand(time(0));
	int c;
	initializeWindow();
	resetTimer();
	getNewPiece();
	printTable(current, Table, getScore());
	while (canGameContinue)
	{
		if ((c = getch()) != ERR)
		{
			manipulateCurrent(c);
		}
		if (hasGraceTimeExceeded())
		{
			resetTimer();
			manipulateCurrent('s');
		}
	}
	deletePiece(current);
	finalizeWindow();
	printGameOver(Table, getScore());
	return 0;
}
