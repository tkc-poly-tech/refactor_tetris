#include "tetris.h"

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
			copied.array[i][j] = array[i][j];
	}
	return (copied);
}

void deletePiece(Piece piece)
{
	int i;
	for (i = 0; i < piece.width; i++)
		free(piece.array[i]);
	free(piece.array);
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