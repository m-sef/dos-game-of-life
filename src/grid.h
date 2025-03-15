#ifndef GRID_H
#define GRID_H

#include <stdlib.h>
#include <stdint.h>

typedef struct {
    uint8_t** data;
    uint8_t default_val;
    size_t height;
    size_t width;
} GRID;

GRID* init_grid(const size_t height, const size_t width, const uint8_t default_val);
void set_grid(GRID* grid, const size_t row, const size_t col, const uint8_t val);
uint8_t get_grid(const GRID* grid, const size_t row, const size_t col);
void clear_grid(GRID* grid, const uint8_t val);

#endif
