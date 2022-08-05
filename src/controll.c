#include "validation.h"

void spawnNewPiece(Piece *piecePtr) // return s rondom piece
{
	Piece new = copyPiece(getRandomPiece());
	new.col = rand() % (COLS - new.width + 1);
	new.row = 0;
	deletePiece(*piecePtr);
	*piecePtr = new;
}

static void fixPieceToTable(const Piece piece, char (*tablePtr)[ROWS][COLS])
{
	for (int i = 0; i < piece.width; i++)
		for (int j = 0; j < piece.width; j++)
			if (piece.array[i][j])
				(*tablePtr)[piece.row + i][piece.col + j] = piece.array[i][j];
}

static int isLineFilled(const int row, const char table[ROWS][COLS])
{
	for (int i = 0; i < COLS; i++)
		if (table[row][i] == 0)
			return FALSE;
	return TRUE;
}

static void putDownLines(const int row, char (*tablePtr)[ROWS][COLS])
{
	for (int i = row; i >= 1; i--)
		for (int j = 0; j < COLS; j++)
			(*tablePtr)[i][j] = (*tablePtr)[i - 1][j];
	for (int j = 0; j < COLS; j++)
		(*tablePtr)[0][j] = 0;
}

static void checkLines(char (*tablePtr)[ROWS][COLS])
{
	int i;
	for (i = 0; i < ROWS; i++)
	{
		if (isLineFilled(i, *tablePtr))
		{
			addScore();
			putDownLines(i, tablePtr);
			reduceInterval();
		}
	}
}

static void moveDown(Piece *currentPtr, char (*tablePtr)[ROWS][COLS])
{
	Piece tmp = copyPiece(*currentPtr);
	tmp.row++;
	if (isValidPosition(tmp, *tablePtr))
		currentPtr->row++;
	else
	{
		fixPieceToTable(*currentPtr, tablePtr);
		checkLines(tablePtr);
		spawnNewPiece(currentPtr);
	}
	deletePiece(tmp);
}

static void moveRight(Piece *currentPtr, char table[ROWS][COLS])
{
	currentPtr->col++;
	if (!isValidPosition(*currentPtr, table))
		currentPtr->col--;
}

static void moveLeft(Piece *currentPtr, char table[ROWS][COLS])
{
	currentPtr->col--;
	if (!isValidPosition(*currentPtr, table))
		currentPtr->col++;
}

static void moveRotate(Piece *currentPtr, char table[ROWS][COLS])
{
	Piece tmp = copyPiece(*currentPtr);
	rotatePiece(tmp);
	if (isValidPosition(tmp, table))
		rotatePiece(*currentPtr);
	deletePiece(tmp);
}

void controllCurrent(Piece *currentPtr, char (*tablePtr)[ROWS][COLS], const int action)
{
	switch (action)
	{
	case 's':
		moveDown(currentPtr, tablePtr);
		break;
	case 'd':
		moveRight(currentPtr, *tablePtr);
		break;
	case 'a':
		moveLeft(currentPtr, *tablePtr);
		break;
	case 'w':
		moveRotate(currentPtr, *tablePtr);
		break;
	}
	printTable(*currentPtr, *tablePtr, getScore());
}
