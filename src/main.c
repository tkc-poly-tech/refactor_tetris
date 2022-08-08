#include "utils.h"
#include "piece.h"
#include "window.h"
#include "random.h"
#include "score.h"
#include "timer.h"
#include "view.h"
#include "control.h"
#include "validation.h"

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
	printGame(Current, Table, getScore());
}

static void run()
{
	while (canGameContinue())
	{
		const int key = getInputKey();
		if (inputKeyExists(key))
		{
			control(key, &Current, &Table);
			printGame(Current, Table, getScore());
		}
		if (hasIntervalPassed())
		{
			control(KEY_MOVE_DOWN, &Current, &Table);
			printGame(Current, Table, getScore());
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
