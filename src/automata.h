#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define MAX_RULESTRING_LENGTH 20

typedef struct
{
    uint8_t** data;
    uint16_t height;
    uint16_t width;
} GRID;

typedef struct
{
    char rulestring[MAX_RULESTRING_LENGTH];
    uint16_t birth_flags;
    uint16_t survival_flags;
} AUTOMATA_RULES;

typedef struct
{
    GRID* grid;
    AUTOMATA_RULES* rules;
} AUTOMATA;

/* GRID */

GRID* init_grid(const uint16_t height, const uint16_t width);
void set_grid(GRID* grid, const uint16_t row, const uint16_t col, const uint8_t val);
uint8_t get_grid(const GRID* grid, const uint16_t row, const uint16_t col);
void clear_grid(GRID* grid, const uint8_t val);
void randomize_grid(GRID* grid, const uint8_t range);

/* AUTOMATA_RULES */

AUTOMATA_RULES* init_automata_rules(char* rulestring);
void parse_rulestring(AUTOMATA_RULES* rules, char* rulestring);
void set_birth(AUTOMATA_RULES* rules, const uint8_t n);
bool get_birth(const AUTOMATA_RULES* rules, const uint8_t n);
void set_survival(AUTOMATA_RULES* rules, const uint8_t n);
bool get_survival(const AUTOMATA_RULES* rules, const uint8_t n);

/* AUTOMATA */

void set_cell(AUTOMATA* automata, const uint16_t row, const uint16_t col, const uint8_t val);
uint8_t get_cell(const AUTOMATA* automata, const uint16_t row, const uint16_t col);
uint8_t get_alive_neighbors(const AUTOMATA* automata, const uint16_t row, const uint16_t col);

#endif
