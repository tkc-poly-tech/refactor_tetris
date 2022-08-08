#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>

#define DELAY_MS 1

void initializeWindow();
void finalizeWindow();
void clearWindow();
int printWindow(const char *args, ...);
int getInputKey();
int inputKeyExists(int key);

#endif
