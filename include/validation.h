#ifndef VALIDATION_H
#define VALIDATION_H

#include "tetris.h"

int isValidPosition(const Piece piece, char table[ROWS][COLS]);
void spawnNewPiece(Piece *currentPtr);
void controllCurrent(Piece *currentPtr, char (*tablePtr)[ROWS][COLS], const int action);

#endif
