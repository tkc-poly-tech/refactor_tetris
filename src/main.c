#include <time.h>
#include "utils.h"
#include "piece.h"
#include "view.h"
#include "control.h"
#include "validation.h"
#include "score.h"
#include "timer.h"

char Table[ROWS_TABLE][COLS_TABLE] = {0};
Piece current;

static int canGameContinue(const Piece current, char table[ROWS_TABLE][COLS_TABLE])
{
	return isValidPosition(current, table);
}

static void initialize()
{
	srand(time(0));
	initializeWindow();
	resetTimer();
	spawnNewPiece(&current);
	printTable(current, Table, getScore());
}

static void run()
{
	while (canGameContinue(current, Table))
	{
		const int c = getch();
		if (c != ERR)
			control(&current, &Table, c);
			printTable(current, Table, getScore());
		if (hasIntervalPassed())
		{
			control(&current, &Table, 's');
			printTable(current, Table, getScore());
			resetTimer();
		}
	}
}

static void finalize()
{
	deletePiece(current);
	finalizeWindow();
	printResult(Table, getScore());
}

int main()
{
	initialize();
	run();
	finalize();
	return 0;
}
