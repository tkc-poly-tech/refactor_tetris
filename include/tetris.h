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
void decreaseGraceTime();
void resetTimer();
int hasGraceTimeExceeded();

// score.c
void addScore();
int getScore();

// view.c
void initializeWindow();
void finalizeWindow();
void printTable(Piece current, char table[ROWS][COLS], int score);
void printGameOver(char table[ROWS][COLS], int score);

#endif
