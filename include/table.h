#ifndef TABLE_H
#define TABLE_H

#include "utils.h"
#include "piece.h"

void updateTable(const Piece piece, char (*tablePtr)[ROWS_TABLE][COLS_TABLE]);

#endif
