#include <curses.h>

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#include "version.h"
#include "game.h"

static void display_usage()
{
	puts("usage: gol.exe [options][rulestring]");
}

static void display_help()
{
	display_usage();
	puts("options:");
	printf("  -%-14s --%-18s %s\n", "h", "help", "Show help.");
	printf("  -%-14s --%-18s %s\n", "s <seed>", "seed <seed>", "Set seed.");
	printf("  -%-14s --%-18s %s\n", "v", "version", "Show version.");
	puts("rulestring examples:");
	puts("  B3/S23          Conway's Game Of Life");
	puts("  B35678/S5678    Diamoeba");
}

static void display_version()
{
	puts("gol " VERSION);
}

static WINDOW* configure_window(WINDOW* window)
{
	nodelay(window, true);
	noecho();
	return window;
}

extern int main(const int argc, char** argv)
{
	WINDOW* window;
	uint16_t seed = time(NULL);
	int opt = 0;

	while ((opt = getopt(argc, argv, "hsv")) != -1)
	{
		switch (opt)
		{
		case 'h':
			display_help();
			exit(EXIT_SUCCESS);
		case 's':
			seed = atoi(optarg);
			break;
		case 'v':
			display_version();
			exit(EXIT_SUCCESS);
		default:
			display_usage();
			exit(EXIT_FAILURE);
		}
	}

	srand(seed);

	window = configure_window(initscr());
	start_game(window, argv[argc - 1]);

	endwin();
	return EXIT_SUCCESS;
}
