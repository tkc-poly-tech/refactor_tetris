#include "tetris.h"
#include "view.h"

void initialView()
{
	initscr();
	timeout(1);
}

void printTable(Piece current, char table[ROWS][COLS], int score)
{
	char buffer[ROWS][COLS] = {0};
	int i, j;
	for (i = 0; i < current.width; i++)
	{
		for (j = 0; j < current.width; j++)
		{
			if (current.array[i][j])
				buffer[current.row + i][current.col + j] = current.array[i][j];
		}
	}
	clear();
	for (i = 0; i < COLS - 9; i++)
		printw(" ");
	printw("42 Tetris\n");
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			printw("%c ", (table[i][j] + buffer[i][j]) ? '#' : '.');
		}
		printw("\n");
	}
	printw("\nScore: %d\n", score);
}

void printGameOver(char table[ROWS][COLS], int score)
{
	int i, j;
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
			printf("%c ", table[i][j] ? '#' : '.');
		printf("\n");
	}
	printf("\nGame over!\n");
	printf("\nScore: %d\n", score);
}