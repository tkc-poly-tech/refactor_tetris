#ifndef CONTROL_H
#define CONTROL_H

#include "utils.h"
#include "piece.h"

#define KEY_MOVE_DOWN 's'
#define KEY_MOVE_RIGHT 'd'
#define KEY_MOVE_LEFT 'a'
#define KEY_MOVE_ROTATE 'w'

void control(const int key, Piece *currentPtr, char (*tablePtr)[ROWS_TABLE][COLS_TABLE]);

#endif
