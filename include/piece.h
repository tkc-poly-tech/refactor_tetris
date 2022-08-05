#ifndef PIECE_H
#define PIECE_H

typedef struct
{
	char **array;
	int width, row, col;
} Piece;

Piece getRandomPiece();
Piece copyPiece(Piece piece);
void deletePiece(Piece piece);
void rotatePiece(Piece piece); // rotates clockwise
void spawnNewPiece(Piece *piecePtr);

#endif
