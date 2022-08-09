#include "table.h"
#include "utils.h"
#include "score.h"
#include "timer.h"

static bool isLineFilled(const int row, const char table[ROWS_TABLE][COLS_TABLE])
{
	for (int i = 0; i < COLS_TABLE; i++)
		if (table[row][i] == 0)
			return false;
	return true;
}

static void desapearLine(const int row, char (*tablePtr)[ROWS_TABLE][COLS_TABLE])
{
	for (int i = row; i >= 1; i--)
		for (int j = 0; j < COLS_TABLE; j++)
			(*tablePtr)[i][j] = (*tablePtr)[i - 1][j];
	for (int j = 0; j < COLS_TABLE; j++)
		(*tablePtr)[0][j] = 0;
}

static void desapearFilledLines(char (*tablePtr)[ROWS_TABLE][COLS_TABLE])
{
	for (int i = 0; i < ROWS_TABLE; i++)
	{
		if (isLineFilled(i, *tablePtr))
		{
			addScore();
			desapearLine(i, tablePtr);
			reduceInterval();
		}
	}
}

static void fixPieceToTable(const Piece piece, char (*tablePtr)[ROWS_TABLE][COLS_TABLE])
{
	for (int i = 0; i < piece.width; i++)
		for (int j = 0; j < piece.width; j++)
			if (piece.array[i][j])
				(*tablePtr)[piece.row + i][piece.col + j] = piece.array[i][j];
}

void updateTable(const Piece piece, char (*tablePtr)[ROWS_TABLE][COLS_TABLE])
{
	fixPieceToTable(piece, tablePtr);
	desapearFilledLines(tablePtr);
}
