#include "validation.h"

void spawnNewPiece(Piece *piecePtr)
{
	Piece new = copyPiece(getRandomPiece());
	new.col = rand() % (COLS - new.width + 1);
	new.row = 0;
	deletePiece(*piecePtr);
	*piecePtr = new;
}

static void moveDown(Piece *currentPtr, char (*tablePtr)[ROWS][COLS])
{
	Piece tmp = copyPiece(*currentPtr);
	tmp.row++;
	if (isValidPosition(tmp, *tablePtr))
		currentPtr->row++;
	else
	{
		updateTable(*currentPtr, tablePtr);
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
}
