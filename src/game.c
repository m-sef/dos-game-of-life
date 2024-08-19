#include "game.h"

GAME game;

void start_game(WINDOW* window, char* rulestring)
{
    char pressed = 0;

    install_timer_isr();

    // Initialize
    game.automata->grid = init_grid(GRID_HEIGHT, GRID_WIDTH);
    game.automata->rules = init_automata_rules(rulestring);

    randomize_grid(game.automata->grid, 2);

    register_alarm(&update_automata, TICK_SPEED);
    register_alarm(&draw_grid, TICK_SPEED);

    // TODO: Find definition for CTRL-C
    while (pressed != 0x03)
    {
        update_alarms();

        pressed = wgetch(window);
    }

    restore_old_timer_isr();
}

void update_automata()
{
    int row;
    int col;
    uint8_t alive_neighbors;
    uint8_t cell;

    for (row = 0; row < GRID_HEIGHT; row++)
    {
        for (col = 0; col < GRID_WIDTH; col++)
        {
            alive_neighbors = get_alive_neighbors(game.automata, row, col);
            cell = get_cell(game.automata, row, col);

            if (!cell && get_birth(game.automata->rules, alive_neighbors))
            {
                set_cell(game.automata, row, col, cell | 0x02);
            }

            if (cell && get_survival(game.automata->rules, alive_neighbors))
            {
                set_cell(game.automata, row, col, cell | 0x02);
            }
        }
    }

    for (row = 0; row < GRID_HEIGHT; row++)
    {
        for (col = 0; col < GRID_WIDTH; col++)
        {
            cell = get_cell(game.automata, row, col);
            set_cell(game.automata, row, col, cell >> 1);
        }
    }

    register_alarm(&update_automata, TICK_SPEED);
}

void draw_hud()
{

}

void draw_grid()
{
    int row;
    int col;
    uint8_t cell;

    for (row = 0; row < GRID_HEIGHT / 2; row++)
    {
        for (col = 0; col < GRID_WIDTH; col++)
        {
            cell = get_cell(game.automata, row * 2, col);
            cell |= get_cell(game.automata, (row * 2) + 1, col) << 1;

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
