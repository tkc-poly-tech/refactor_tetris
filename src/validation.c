#include "validation.h"

static int isOutofTable(const Piece piece, const int i, const int j)
{
	if ((piece.col + j < 0 || piece.col + j >= COLS || piece.row + i >= ROWS)) // out of borders
	{
		if (piece.array[i][j]) // but is it just a phantom?
			return TRUE;
	}
	return FALSE;
}

static int isPieceDuplicate(const Piece piece, char table[ROWS][COLS], const int i, const int j)
{
	return table[piece.row + i][piece.col + j] && piece.array[i][j];
}

int isValidPosition(const Piece piece, char table[ROWS][COLS]) // check position of copied piece
{
	for (int i = 0; i < piece.width; i++)
	{
		for (int j = 0; j < piece.width; j++)
		{
			if (isOutofTable(piece, i, j) || isPieceDuplicate(piece, table, i, j))
				return FALSE;
		}
	}
	return TRUE;
}
