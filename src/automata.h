#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <curses.h>

#include <stdint.h>
#include <stddef.h>

#include "alarm.h"
#include "ruleset.h"
#include "grid.h"

#define TICK_SPEED 3

#define DEAD 0x00
#define ALIVE 0x01
#define MASK_CURRENT_TURN 0x01
#define MASK_NEXT_TURN 0x02

#define ROWS_PER_LINE 2

void init_automata(const uint16_t seed, char* rulestring);
void update_automata();
void draw_automata();
void randomize_grid();
uint8_t get_alive_neighbors(const size_t row, const size_t col);

#endif
