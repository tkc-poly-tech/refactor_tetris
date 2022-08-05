#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>

#define INIT_INTERVAL 400000;
#define INIT_DECREASE 1000;

typedef struct timeval t_timeval;

void reduceInterval();
void resetTimer();
int hasIntervalPassed();

#endif
