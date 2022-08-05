#ifndef CONTROL_H
#define CONTROL_H

#include "utils.h"
#include "piece.h"

void control(Piece *currentPtr, char (*tablePtr)[ROWS_TABLE][COLS_TABLE], const int action);

#endif
