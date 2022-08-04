#include "tetris.h"

char Table[ROWS][COLS] = {0};
char GameOn = TRUE;

Piece current;

const Piece pieceTemplates[7] = {
	{(char *[]){(char[]){0, 1, 1}, (char[]){1, 1, 0}, (char[]){0, 0, 0}}, 3, 0, 0},
	{(char *[]){(char[]){1, 1, 0}, (char[]){0, 1, 1}, (char[]){0, 0, 0}}, 3, 0, 0},
	{(char *[]){(char[]){0, 1, 0}, (char[]){1, 1, 1}, (char[]){0, 0, 0}}, 3, 0, 0},
	{(char *[]){(char[]){0, 0, 1}, (char[]){1, 1, 1}, (char[]){0, 0, 0}}, 3, 0, 0},
	{(char *[]){(char[]){1, 0, 0}, (char[]){1, 1, 1}, (char[]){0, 0, 0}}, 3, 0, 0},
	{(char *[]){(char[]){1, 1}, (char[]){1, 1}}, 2, 0, 0},
	{(char *[]){(char[]){0, 0, 0, 0}, (char[]){1, 1, 1, 1}, (char[]){0, 0, 0, 0}, (char[]){0, 0, 0, 0}}, 4, 0, 0}};

Piece copyPiece(Piece piece)
{
	Piece copied = piece;
	char **array = piece.array;
	copied.array = (char **)malloc(copied.width * sizeof(char *));
	int i, j;
	for (i = 0; i < copied.width; i++)
	{
		copied.array[i] = (char *)malloc(copied.width * sizeof(char));
		for (j = 0; j < copied.width; j++)
		{
			copied.array[i][j] = array[i][j];
		}
	}
	return copied;
}

void deletePiece(Piece piece)
{
	int i;
	for (i = 0; i < piece.width; i++)
	{
		free(piece.array[i]);
	}
	free(piece.array);
}

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
	Piece new = copyPiece(pieceTemplates[rand() % 7]);
	new.col = rand() % (COLS - new.width + 1);
	new.row = 0;
	deletePiece(current);
	current = new;
	if (!checkPosition(current))
	{
		GameOn = FALSE;
	}
}

void rotatePiece(Piece piece) // rotates clockwise
{
	Piece tmp = copyPiece(piece);
	int i, j, k, width;
	width = piece.width;
	for (i = 0; i < width; i++)
	{
		for (j = 0, k = width - 1; j < width; j++, k--)
		{
			piece.array[i][j] = tmp.array[k][i];
		}
	}
	deletePiece(tmp);
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

void checkLines()
{
	int n, m, sum, count = 0;
	for (n = 0; n < ROWS; n++)
	{
		sum = 0;
		for (m = 0; m < COLS; m++)
		{
			sum += Table[n][m];
		}
		if (sum == COLS)
		{
			count++;
			int l, k;
			for (k = n; k >= 1; k--)
				for (l = 0; l < COLS; l++)
					Table[k][l] = Table[k - 1][l];
			for (l = 0; l < COLS; l++)
				Table[k][l] = 0;
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
	initscr();
	timeout(1);
	resetTimer();
	getNewPiece();
	printTable(current, Table, getScore());
	while (GameOn)
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
	endwin();
	printGameOver(Table, getScore());
	return 0;
}
