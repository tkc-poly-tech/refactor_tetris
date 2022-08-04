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

void printTable(Piece current, char table[ROWS][COLS], int score)
{
	char buffer[ROWS][COLS] = {0};
	int i, j;
	for (i = 0; i < current.width; i++)
		for (j = 0; j < current.width; j++)
			if (current.array[i][j])
				buffer[current.row + i][current.col + j] = current.array[i][j];
	clear();
	for (i = 0; i < COLS - 9; i++)
		printw(" ");
	printw(FORMAT_HEADER);
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
			printw("%c ", (table[i][j] + buffer[i][j]) ? CHAR_PIECE : CHAR_EMPTY);
		printw("\n");
	}
	printw("\n");
	printw(FORMAT_SCORE, score);
}

void printGameOver(char table[ROWS][COLS], int score)
{
	int i, j;
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
			printf("%c ", table[i][j] ? CHAR_PIECE : CHAR_EMPTY);
		printf("\n");
	}
	printf("\n");
	printf(FORMAT_GAMEOVER);
	printf("\n");
	printf(FORMAT_SCORE, score);
}