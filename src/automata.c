#include "automata.h"

RULESET* ruleset;
GRID* grid;

void init_automata(
    const uint16_t seed, 
    char* rulestring, 
    const bool anti)
{
    WINDOW* window = initscr();
    char pressed = 0;

    srand(seed);

    nodelay(window, true);
    noecho();

    install_timer_isr();

    ruleset = init_ruleset(rulestring);
    grid = init_grid(LINES * ROWS_PER_LINE, COLS, (anti) ? ALIVE : DEAD);

    if (anti)
    {
        reverse(ruleset);
    }

    randomize_grid();
    update_automata();
    draw_automata();

    while (pressed != CTRL_C)
    {
        update_alarms();

        pressed = wgetch(window);
    }

    restore_old_timer_isr();

    endwin();

    system("cls");
}


uint8_t get_alive_neighbors(
    const size_t row,
    const size_t col)
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

            alive_neighbors += get_grid(grid, row + row_offset, col + col_offset) & MASK_CURRENT_TURN;
        }
    }

    return alive_neighbors;
}

void update_automata()
{
    size_t row;
    size_t col;
    uint8_t alive_neighbors;
    uint8_t cell;

    for (row = 0; row < (LINES * ROWS_PER_LINE); row++)
    {
        for (col = 0; col < COLS; col++)
        {
            alive_neighbors = get_alive_neighbors(row, col);
            cell = get_grid(grid, row, col);
            
            if ((cell == ALIVE) && get_survive_flag(ruleset, alive_neighbors))
            {
                set_grid(grid, row, col, cell | MASK_NEXT_TURN);
            }
            else if ((cell == DEAD) && get_birth_flag(ruleset, alive_neighbors))
            {
                set_grid(grid, row, col, cell | MASK_NEXT_TURN);
            }
        }
    }

    for (row = 0; row < (LINES * ROWS_PER_LINE); row++)
    {
        for (col = 0; col < COLS; col++)
        {
            cell = get_grid(grid, row, col);
            set_grid(grid, row, col, cell >> 1);
        }
    }
    
    register_alarm(&update_automata, TICK_SPEED);
}

void draw_automata()
{
    size_t row;
    size_t col;
    uint8_t cell;

    for (row = 0; row < LINES; row++)
    {
        for (col = 0; col < COLS; col++)
        {
            cell = get_grid(grid, row * ROWS_PER_LINE, col);
            cell |= get_grid(grid, (row * ROWS_PER_LINE) + 1, col) << 1;

            switch (cell)
            {
                case 0x00:
                    mvaddch(row, col, ' ');
                    break;
                case 0x01:
                    mvaddch(row, col, 0xdf);
                    break;
                case 0x02:
                    mvaddch(row, col, 0xdc);
                    break;
                case 0x03:
                    mvaddch(row, col, 0xdb);
                    break;
            }
        }
    }

    register_alarm(&draw_automata, TICK_SPEED);
}

void randomize_grid()
{
    size_t row;
    size_t col;

    for (row = 0; row < LINES * ROWS_PER_LINE; row++)
    {
        for (col = 0; col < COLS; col++)
        {
            set_grid(grid, row, col, rand() & 1);
        }
    }
}
