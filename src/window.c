#include "window.h"

void initializeWindow()
{
	initscr();
	timeout(DELAY_MS);
}

void finalizeWindow()
{
	endwin();
}

void clearWindow()
{
	clear();
}

int printWindow(const char *args, ...)
{
	return printw(args);
}

int getInputKey()
{
	return getch();
}

int inputKeyExists(int key)
{
	return key != ERR;
}
