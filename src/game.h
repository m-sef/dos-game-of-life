#ifndef GAME_H
#define GAME_H

#include <curses.h>

#include "alarm.h"
#include "ruleset.h"
#include "grid.h"

#define GRID_HEIGHT 50
#define GRID_WIDTH 80
#define TICK_SPEED 3

typedef struct
{
    RULESET* ruleset;
    GRID* grid;
} GAME;

void start_game(const uint16_t seed, char* rulestring);
void set_cell(const size_t row, const size_t col, const uint8_t val);
uint8_t get_cell(const size_t row, const size_t col);
uint8_t get_alive_neighbors(const size_t row, const size_t col);
void update_game();
void randomize_grid();

void draw_hud();
void draw_grid();

#endif
