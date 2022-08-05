#include "control.h"
#include "validation.h"
#include "table.h"

static void moveDown(Piece *currentPtr, char (*tablePtr)[ROWS_TABLE][COLS_TABLE])
{
	currentPtr->row++;
	if (isValidPosition(*currentPtr, *tablePtr))
		return;
	currentPtr->row--;
	updateTable(*currentPtr, tablePtr);
	spawnNewPiece(currentPtr);
}

static void moveRight(Piece *currentPtr, char (*tablePtr)[ROWS_TABLE][COLS_TABLE])
{
	currentPtr->col++;
	if (isValidPosition(*currentPtr, *tablePtr))
		return;
	currentPtr->col--;
}

static void moveLeft(Piece *currentPtr, char (*tablePtr)[ROWS_TABLE][COLS_TABLE])
{
	currentPtr->col--;
	if (isValidPosition(*currentPtr, *tablePtr))
		return;
	currentPtr->col++;
}

static void moveRotate(Piece *currentPtr, char (*tablePtr)[ROWS_TABLE][COLS_TABLE])
{
	Piece tmp = copyPiece(*currentPtr);
	rotatePiece(tmp);
	if (isValidPosition(tmp, *tablePtr))
		rotatePiece(*currentPtr);
	deletePiece(tmp);
}

void control(Piece *currentPtr, char (*tablePtr)[ROWS_TABLE][COLS_TABLE], const int action)
{
	switch (action)
	{
	case 's':
		moveDown(currentPtr, tablePtr);
		break;
	case 'd':
		moveRight(currentPtr, tablePtr);
		break;
	case 'a':
		moveLeft(currentPtr, tablePtr);
		break;
	case 'w':
		moveRotate(currentPtr, tablePtr);
		break;
	}
}
