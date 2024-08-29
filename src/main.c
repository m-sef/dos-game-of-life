#include <curses.h>

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#include "version.h"
#include "automata.h"

static void display_usage()
{
	puts("usage: gol.exe [options][rulestring]");
}

static void display_help()
{
	display_usage();
	puts("options:");
	printf("  -%-14s --%-18s %s\n", "a", "anti", "Black/white reversal.");
	printf("  -%-14s --%-18s %s\n", "h", "help", "Show help.");
	printf("  -%-14s --%-18s %s\n", "s <seed>", "seed <seed>", "Set seed.");
	printf("  -%-14s --%-18s %s\n", "v", "version", "Show version.");
	puts("rulestrings:");
	puts("  B1357/S1357          Replicator");
	puts("  B2/S                 Seeds");
	puts("  B3/S23               Life");
	puts("  B35678/S5678         Diamoeba");
	puts("  B4678/S35678         Anneal");
	puts("  B3/S12345             Maze");
}

static void display_version()
{
	puts("gol " VERSION);
}

extern int main(const int argc, char** argv)
{
	uint16_t seed = time(NULL);
	bool anti = false;
	int opt = 0;

	while ((opt = getopt(argc, argv, "ahsv")) != -1)
	{
		switch (opt)
		{
		case 'a':
			anti = true;
			continue;
		case 'h':
			display_help();
			exit(EXIT_SUCCESS);
		case 's':
			seed = atoi(optarg);
			continue;;
		case 'v':
			display_version();
			exit(EXIT_SUCCESS);
		default:
			display_usage();
			exit(EXIT_FAILURE);
		}
	}

	init_automata(seed, argv[argc - 1], anti);
	return EXIT_SUCCESS;
}
