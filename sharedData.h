#pragma once
#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <ncursesw/ncurses.h>

extern FILE *debugOut;

extern const int BOTTOM_WIN_LINES;
extern const int MAP_COLS;
extern const int MAP_LINES;
extern const int TOTAL_LINES;
extern const int TOTAL_COLS;

extern WINDOW *mapWin;
extern WINDOW *topWin;
extern WINDOW *bottomWin;

#endif
