#include "automata.h"

GRID* init_grid(const uint16_t height, const uint16_t width)
{
    GRID* new_grid = (GRID*) malloc(sizeof(GRID));
    int row;

    // Allocate memory for grid data
    new_grid->data = (uint8_t**) malloc(height * sizeof(uint8_t*));
    for (row = 0; row < height; row++)
    {
        new_grid->data[row] = (uint8_t*) malloc(width * sizeof(uint8_t));
    }

    new_grid->height = height;
    new_grid->width = width;

    clear_grid(new_grid, 0);

    return new_grid;
}

void set_grid(GRID* grid, const uint16_t row, const uint16_t col, const uint8_t val)
{
    if (row >= grid->height || col >= grid->width)
    {
        return;
    }
    grid->data[row][col] = val;
}

uint8_t get_grid(const GRID* grid, const uint16_t row, const uint16_t col)
{
    if (row >= grid->height || col >= grid->width)
    {
        return 0;
    }
    return grid->data[row][col];
}

void clear_grid(GRID* grid, const uint8_t val)
{
    int row;
    int col;

    for (row = 0; row < grid->height; row++)
    {
        for (col = 0; col < grid->width; col++)
        {
            set_grid(grid, row, col, val);
        }
    }
}

void randomize_grid(GRID* grid, const uint8_t range)
{
    int row;
    int col;

    for (row = 0; row < grid->height; row++)
    {
        for (col = 0; col < grid->width; col++)
        {
            set_grid(grid, row, col, rand() % range);
        }
    }
}

AUTOMATA_RULES* init_automata_rules(char* rulestring)
{
    AUTOMATA_RULES* new_automata_rules = (AUTOMATA_RULES*) malloc(sizeof(AUTOMATA_RULES));

    // Initialize values
    new_automata_rules->birth_flags = 0;
    new_automata_rules->survival_flags = 0;

    parse_rulestring(new_automata_rules, rulestring);

    return new_automata_rules;
}

void parse_rulestring(AUTOMATA_RULES* rules, char* rulestring)
{
    char* token;
    int i;

    token = strtok(rulestring, "/");
    while (token != NULL)
    {
        switch (token[0])
        {
        case 'B':
            for (i = 1; i < strlen(token); i++)
            {
                set_birth(rules, token[i] - '0');
            }

            break;
        case 'S':
            for (i = 1; i < strlen(token); i++)
            {
                set_survival(rules, token[i] - '0');
            }

            break;
        default:
            break;
        }

        token = strtok(NULL, "/");
    }
}

void set_birth(AUTOMATA_RULES* rules, const uint8_t n)
{
    rules->birth_flags |= 1 << n;
}

bool get_birth(const AUTOMATA_RULES* rules, const uint8_t n)
{
    return (rules->birth_flags >> n) & 1;
}

void set_survival(AUTOMATA_RULES* rules, const uint8_t n)
{
    rules->survival_flags |= 1 << n;
}

bool get_survival(const AUTOMATA_RULES* rules, const uint8_t n)
{
    return (rules->survival_flags >> n) & 1;
}

void set_cell(AUTOMATA* automata, const uint16_t row, const uint16_t col, const uint8_t val)
{
    set_grid(automata->grid, row, col, val);
}

uint8_t get_cell(const AUTOMATA* automata, const uint16_t row, const uint16_t col)
{
    return get_grid(automata->grid, row, col);
}

uint8_t get_alive_neighbors(const AUTOMATA* automata, const uint16_t row, const uint16_t col)
{
    uint8_t alive_neighbors = 0;
    int row_offset;
    int col_offset;

    for (row_offset = -1; row_offset <= 1; row_offset++)
    {
        for (col_offset = -1; col_offset <= 1; col_offset++)
        {
            if (!row_offset && !col_offset)
            {
                continue;
            }

            alive_neighbors += get_cell(automata, row + row_offset, col + col_offset) & 1;
        }
    }

    return alive_neighbors;
}


