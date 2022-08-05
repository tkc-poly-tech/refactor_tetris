#include "tetris.h"
#include "validation.h"

char Table[ROWS][COLS] = {0};
Piece current;

static int canGameContinue(const Piece current, char table[ROWS][COLS])
{
	return isValidPosition(current, table);
}

void initialize()
{
	srand(time(0));
	initializeWindow();
	resetTimer();
	spawnNewPiece(&current);
	printTable(current, Table, getScore());
}

void run()
{
	while (canGameContinue(current, Table))
	{
		const int c = getch();
		if (c != ERR)
			controllCurrent(&current, &Table, c);
		if (hasIntervalPassed())
		{
			controllCurrent(&current, &Table, 's');
			resetTimer();
		}
	}
}

void finalize()
{
	deletePiece(current);
	finalizeWindow();
	printGameOver(Table, getScore());
}

int main()
{
	initialize();
	run();
	finalize();
	return 0;
}
