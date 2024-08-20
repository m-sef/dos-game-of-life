#include "game.h"

GAME* game;

void start_game(const uint16_t seed, char* rulestring)
{
    WINDOW* window = initscr();
    char pressed = 0;

    game = (GAME*) malloc(sizeof(GAME));

    srand(seed);

    nodelay(window, true);
    noecho();

    install_timer_isr();

    // Initialize
    game->ruleset = init_ruleset(rulestring);
    game->grid = init_grid(GRID_HEIGHT, GRID_WIDTH);

    randomize_grid();
    update_game();
    draw_grid();

    // TODO: Find definition for CTRL-C
    while (pressed != 0x03)
    {
        update_alarms();

        pressed = wgetch(window);
    }

    restore_old_timer_isr();

    endwin();
}

void set_cell(const size_t row, const size_t col, const uint8_t val)
{
    set_grid(game->grid, row, col, val);
}

uint8_t get_cell(const size_t row, const size_t col)
{
    return get_grid(game->grid, row, col);
}

uint8_t get_alive_neighbors(const size_t row, const size_t col)
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

            alive_neighbors += get_cell(row + row_offset, col + col_offset) & 1;
        }
    }

    return alive_neighbors;
}

void update_game()
{
    size_t row;
    size_t col;
    uint8_t alive_neighbors;
    uint8_t cell;

    for (row = 0; row < GRID_HEIGHT; row++)
    {
        for (col = 0; col < GRID_WIDTH; col++)
        {
            alive_neighbors = get_alive_neighbors(row, col);
            cell = get_cell(row, col);
            
            if (!cell && get_birth_flag(game->ruleset, alive_neighbors))
            {
                set_cell(row, col, cell | 0x02);
            }

            if (cell && get_survival_flag(game->ruleset, alive_neighbors))
            {
                set_cell(row, col, cell | 0x02);
            }
        }
    }

    for (row = 0; row < GRID_HEIGHT; row++)
    {
        for (col = 0; col < GRID_WIDTH; col++)
        {
            cell = get_cell(row, col);
            set_cell(row, col, cell >> 1);
        }
    }
    

    register_alarm(&update_game, TICK_SPEED);
}

void randomize_grid()
{
    size_t row;
    size_t col;

    for (row = 0; row < GRID_HEIGHT; row++)
    {
        for (col = 0; col < GRID_WIDTH; col++)
        {
            set_cell(row, col, rand() & 1);
        }
    }
}

void draw_hud()
{

}

void draw_grid()
{
    size_t row;
    size_t col;
    uint8_t cell;

    for (row = 0; row < GRID_HEIGHT / 2; row++)
    {
        for (col = 0; col < GRID_WIDTH; col++)
        {
            cell = get_cell(row * 2, col);
            cell |= get_cell((row * 2) + 1, col) << 1;

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

    register_alarm(&draw_grid, TICK_SPEED);
}
