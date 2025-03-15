#include "grid.h"

GRID* init_grid(const size_t height, const size_t width, const uint8_t default_val)
{
    GRID* new_grid = (GRID*) malloc(sizeof(GRID));
    size_t row;

    new_grid->data = (uint8_t**) malloc(height * sizeof(uint8_t*));
    for (row = 0; row < height; row++)
    {
        new_grid->data[row] = (uint8_t*) malloc(width * sizeof(uint8_t));
    }

    new_grid->height = height;
    new_grid->width = width;
    new_grid->default_val = default_val;

    clear_grid(new_grid, default_val);

    return new_grid;
}

void set_grid(GRID* grid, const size_t row, const size_t col, const uint8_t val)
{
    if (row >= grid->height || col >= grid->width)
    {
        return;
    }
    grid->data[row][col] = val;
}

uint8_t get_grid(const GRID* grid, const size_t row, const size_t col)
{
    if (row >= grid->height || col >= grid->width)
    {
        return grid->default_val;
    }
    return grid->data[row][col];
}

void clear_grid(GRID* grid, const uint8_t val)
{
    size_t row;
    size_t col;

    for (row = 0; row < grid->height; row++)
    {
        for (col = 0; col < grid->width; col++)
        {
            set_grid(grid, row, col, val);
        }
    }
}
