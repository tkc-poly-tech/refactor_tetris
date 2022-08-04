#include "score.h"

int score = 0;

void addScore(int count_lines)
{
	score += UNIT_SCORE * count_lines;
}

int getScore()
{
	return score;
}
