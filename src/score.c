#include "score.h"

int score = 0;

void addScore()
{
	score += UNIT_SCORE;
}

int getScore()
{
	return score;
}
