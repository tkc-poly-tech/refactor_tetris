#include "random.h"

void initializeRandom()
{
	srand(time(0));
}

int getRandomNumber()
{
	return rand();
}
