#include "validation.h"
#include "utils.h"

static bool isOutofTable(const Piece piece, const int i, const int j)
{
	if ((piece.col + j < 0 || piece.col + j >= COLS_TABLE || piece.row + i >= ROWS_TABLE))
		if (piece.array[i][j])
			return true;
	return false;
}

static bool isPieceDuplicate(const Piece piece, char table[ROWS_TABLE][COLS_TABLE], const int i, const int j)
{
	return table[piece.row + i][piece.col + j] && piece.array[i][j];
}

bool isValidPosition(const Piece piece, char table[ROWS_TABLE][COLS_TABLE])
{
	for (int i = 0; i < piece.width; i++)
		for (int j = 0; j < piece.width; j++)
			if (isOutofTable(piece, i, j) || isPieceDuplicate(piece, table, i, j))
				return false;
	return true;
}
