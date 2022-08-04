#include "view.h"

void initializeWindow()
{
	initscr();
	timeout(1);
}

void finalizeWindow()
{
	endwin();
}

static void deployPieceInTable(const Piece piece, char pieceInTable[ROWS][COLS])
{
	for (int i = 0; i < piece.width; i++)
		for (int j = 0; j < piece.width; j++)
			if (piece.array[i][j])
				pieceInTable[piece.row + i][piece.col + j] = piece.array[i][j];
}

void printTable(const Piece current, const char table[ROWS][COLS], const int score)
{
	char pieceInTable[ROWS][COLS] = {0};
	deployPieceInTable(current, pieceInTable);
	clear();
	for (int i = 0; i < COLS - 9; i++)
		printw(" ");
	printw(FORMAT_HEADER);
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
			printw("%c ", (table[i][j] + pieceInTable[i][j]) ? CHAR_PIECE : CHAR_EMPTY);
		printw("\n");
	}
	printw("\n");
	printw(FORMAT_SCORE, score);
}

void printGameOver(const char table[ROWS][COLS], const int score)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
			printf("%c ", table[i][j] ? CHAR_PIECE : CHAR_EMPTY);
		printf("\n");
	}
	printf("\n");
	printf(FORMAT_GAMEOVER);
	printf("\n");
	printf(FORMAT_SCORE, score);
}
