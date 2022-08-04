#include "timer.h"

suseconds_t interval = INIT_GRACE_TIME;
int decrease = INIT_DECREASE;
t_timeval settedTime;

void reduceInterval()
{
	interval -= decrease;
	decrease--;
}

static suseconds_t convertToSuseconds(const t_timeval time)
{
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void resetTimer()
{
	gettimeofday(&settedTime, NULL);
}

int hasIntervalPassed()
{
	t_timeval now;
	gettimeofday(&now, NULL);
	const suseconds_t passedTime = convertToSuseconds(now) - convertToSuseconds(settedTime);
	return (passedTime > interval);
}
