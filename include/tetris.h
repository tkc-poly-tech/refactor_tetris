#ifndef TETRIS_H
#define TETRIS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define ROWS 20
#define COLS 15
#define TRUE 1
#define FALSE 0

typedef struct
{
	char **array;
	int width, row, col;
} Piece;

Piece getRandomPiece();
Piece copyPiece(Piece piece);
void deletePiece(Piece piece);
void rotatePiece(Piece piece);

// timer.c
void reduceInterval();
void resetTimer();
int hasIntervalPassed();

// score.c
void addScore();
int getScore();

// view.c
void initializeWindow();
void finalizeWindow();
void printTable(const Piece current, const char table[ROWS][COLS], const int score);
void printResult(const char table[ROWS][COLS], const int score);

// validation.c
int isValidPosition(const Piece piece, char table[ROWS][COLS]);
void spawnNewPiece(Piece *currentPtr);
void controllCurrent(Piece *currentPtr, char (*tablePtr)[ROWS][COLS], const int action);

// table.c
void updateTable(const Piece piece, char (*tablePtr)[ROWS][COLS]);

#endif
