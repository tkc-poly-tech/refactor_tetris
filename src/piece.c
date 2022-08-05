#include "tetris.h"

const Piece pieceTemplates[7] = {
	{(char *[]){(char[]){0, 1, 1}, (char[]){1, 1, 0}, (char[]){0, 0, 0}}, 3, 0, 0},
	{(char *[]){(char[]){1, 1, 0}, (char[]){0, 1, 1}, (char[]){0, 0, 0}}, 3, 0, 0},
	{(char *[]){(char[]){0, 1, 0}, (char[]){1, 1, 1}, (char[]){0, 0, 0}}, 3, 0, 0},
	{(char *[]){(char[]){0, 0, 1}, (char[]){1, 1, 1}, (char[]){0, 0, 0}}, 3, 0, 0},
	{(char *[]){(char[]){1, 0, 0}, (char[]){1, 1, 1}, (char[]){0, 0, 0}}, 3, 0, 0},
	{(char *[]){(char[]){1, 1}, (char[]){1, 1}}, 2, 0, 0},
	{(char *[]){(char[]){0, 0, 0, 0}, (char[]){1, 1, 1, 1}, (char[]){0, 0, 0, 0}, (char[]){0, 0, 0, 0}}, 4, 0, 0}};

Piece getRandomPiece()
{
	return (pieceTemplates[rand() % 7]);
}

static void freeArray(int index, char **array)
{
	for (int i = index; i >= 0; i--)
		free(array[i]);
	free(array);
}

Piece copyPiece(Piece piece)
{
	Piece copied = piece;
	char **array = piece.array;
	copied.array = (char **)malloc(copied.width * sizeof(char *));
	if (!copied.array)
		exit(1);
	for (int i = 0; i < copied.width; i++)
	{
		copied.array[i] = (char *)malloc(copied.width * sizeof(char));
		if (!copied.array[i])
		{
			freeArray(i, copied.array);
			exit(1);
		}
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
