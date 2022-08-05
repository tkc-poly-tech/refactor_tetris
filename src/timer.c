#include "timer.h"

suseconds_t Interval = INIT_INTERVAL;
int Decrease = INIT_DECREASE;
t_timeval SettedTime;

void reduceInterval()
{
	Interval -= Decrease;
	Decrease--;
}

static suseconds_t convertToSuseconds(const t_timeval time)
{
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void resetTimer()
{
	gettimeofday(&SettedTime, NULL);
}

int hasIntervalPassed()
{
	t_timeval now;
	gettimeofday(&now, NULL);
	const suseconds_t passedTime = convertToSuseconds(now) - convertToSuseconds(SettedTime);
	return (passedTime > Interval);
}
