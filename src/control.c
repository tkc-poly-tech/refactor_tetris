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

void control(const int key, Piece *currentPtr, char (*tablePtr)[ROWS_TABLE][COLS_TABLE])
{
	switch (key)
	{
	case KEY_MOVE_DOWN:
		moveDown(currentPtr, tablePtr);
		break;
	case KEY_MOVE_RIGHT:
		moveRight(currentPtr, tablePtr);
		break;
	case KEY_MOVE_LEFT:
		moveLeft(currentPtr, tablePtr);
		break;
	case KEY_MOVE_ROTATE:
		moveRotate(currentPtr, tablePtr);
		break;
	}
}
