#include "tetris.h"

Piece copyPiece(Piece piece)
{
	Piece copied = piece;
	char **array = piece.array;
	copied.array = (char **)malloc(copied.width * sizeof(char *));
	for (int i = 0; i < copied.width; i++)
	{
		copied.array[i] = (char *)malloc(copied.width * sizeof(char));
		for (int j = 0; j < copied.width; j++)
			copied.array[i][j] = array[i][j];
	}
	return (copied);
}

void deletePiece(Piece piece)
{
	for (int i = 0; i < piece.width; i++)
		free(piece.array[i]);
	free(piece.array);
}

void rotatePiece(Piece piece) // rotates clockwise
{
	Piece tmp = copyPiece(piece);
	int width = piece.width;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0, k = width - 1; j < width; j++, k--)
			piece.array[i][j] = tmp.array[k][i];
	}
	deletePiece(tmp);
}
