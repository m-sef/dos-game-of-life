CC = wcc
CFLAGS = -bt=dos -q -wx -ml -i=pdcurses
LINK = wlink
LDFLAGS = op q sys dos
LIBCURSES = pdcurses\dos\pdcurses.lib
SRCDIR = src
RM = del

all: gol.exe

clean
	$(RM) *.obj
	$(RM) *.err
	$(RM) gol.exe

.c: $(SRCDIR)

.c.obj: .autodepend
	$(CC) $(CFLAGS) $<

gol.exe: main.obj alarm.obj game.obj ruleset.obj grid.obj
	$(LINK) $(LDFLAGS) n $@ f *.obj l $(LIBCURSES)