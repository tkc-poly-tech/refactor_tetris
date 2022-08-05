#include "score.h"

int Score = 0;

void addScore()
{
	Score += UNIT_SCORE;
}

int getScore()
{
	return Score;
}
