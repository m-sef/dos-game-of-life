#ifndef GAME_H
#define GAME_H

#include <curses.h>

#include "alarm.h"
#include "automata.h"

#define GRID_HEIGHT 50
#define GRID_WIDTH 80
#define TICK_SPEED 3

typedef struct
{
    AUTOMATA* automata;
    WINDOW* window;
} GAME;

/* Game functions */

void start_game(WINDOW* window, char* rulestring);
void update_automata();

/* Draw functions */

void draw_hud();
void draw_grid();

#endif
