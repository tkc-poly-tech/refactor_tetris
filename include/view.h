#ifndef VIEW_H
#define VIEW_H

#include "utils.h"
#include "piece.h"
#include <stdio.h>
#include <ncurses.h>

#define CHAR_EMPTY '.'
#define CHAR_PIECE '#'

#define OFFSET_HEADER 9
#define FORMAT_HEADER "42 Tetris\n"
#define FORMAT_GAMEOVER "Game over!\n"
#define FORMAT_SCORE "Score: %d\n"

void initializeWindow();
void finalizeWindow();
void printTable(const Piece current, const char table[ROWS_TABLE][COLS_TABLE], const int score);
void printResult(const char table[ROWS_TABLE][COLS_TABLE], const int score);

#endif
