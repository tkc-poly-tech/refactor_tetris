#include "timer.h"

suseconds_t graceTime = INIT_GRACE_TIME;
int decrease = INIT_DECREASE;
t_timeval settedTime;

void decreaseGraceTime()
{
	graceTime -= decrease--;
}

static suseconds_t convertToSuseconds(t_timeval time)
{
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void resetTimer()
{
	gettimeofday(&settedTime, NULL);
}

int hasGraceTimeExceeded()
{
	t_timeval now;
	gettimeofday(&now, NULL);
	suseconds_t passedTime = convertToSuseconds(now) - convertToSuseconds(settedTime);
	return (passedTime > graceTime);
}
