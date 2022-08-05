#include "table.h"

static int isLineFilled(const int row, const char table[ROWS][COLS])
{
	for (int i = 0; i < COLS; i++)
		if (table[row][i] == 0)
			return FALSE;
	return TRUE;
}

static void desapearLine(const int row, char (*tablePtr)[ROWS][COLS])
{
	for (int i = row; i >= 1; i--)
		for (int j = 0; j < COLS; j++)
			(*tablePtr)[i][j] = (*tablePtr)[i - 1][j];
	for (int j = 0; j < COLS; j++)
		(*tablePtr)[0][j] = 0;
}

static void desapearFilledLines(char (*tablePtr)[ROWS][COLS])
{
	for (int i = 0; i < ROWS; i++)
	{
		if (isLineFilled(i, *tablePtr))
		{
			addScore();
			desapearLine(i, tablePtr);
			reduceInterval();
		}
	}
}

static void fixPieceToTable(const Piece piece, char (*tablePtr)[ROWS][COLS])
{
	for (int i = 0; i < piece.width; i++)
		for (int j = 0; j < piece.width; j++)
			if (piece.array[i][j])
				(*tablePtr)[piece.row + i][piece.col + j] = piece.array[i][j];
}

void updateTable(const Piece piece, char (*tablePtr)[ROWS][COLS])
{
	fixPieceToTable(piece, tablePtr);
	desapearFilledLines(tablePtr);
}