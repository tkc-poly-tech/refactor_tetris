#include "utils.h"
#include "piece.h"
#include "random.h"
#include "view.h"
#include "control.h"
#include "validation.h"
#include "score.h"
#include "timer.h"

char Table[ROWS_TABLE][COLS_TABLE] = {0};
Piece Current;

static int canGameContinue()
{
	return isValidPosition(Current, Table);
}

static void initialize()
{
	initializeRandom();
	initializeWindow();
	resetTimer();
	spawnNewPiece(&Current);
	printTable(Current, Table, getScore());
}

static void run()
{
	while (canGameContinue())
	{
		const int c = getch();
		if (c != ERR)
			control(&Current, &Table, c);
		printTable(Current, Table, getScore());
		if (hasIntervalPassed())
		{
			control(&Current, &Table, 's');
			printTable(Current, Table, getScore());
			resetTimer();
		}
	}
}

static void finalize()
{
	deletePiece(Current);
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
