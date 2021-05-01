CC=gcc
STD=-std=c11

INCLUDE_PATH=-Isrc
LIBRARY_PATH=-Lpath/to/library
CFLAGS=-O3
LFLAGS=-lSDL2

SRC=src/main.c src/render.c src/game.c src/utils.c src/game_constants.c
OBJ=$(SRC:src/.c=bin/.o)
EXEC=bin/pong

all: $(EXEC)

$(EXEC): $(OBJ)
	mkdir -p bin/
	$(CC) $(STD) $(CFLAGS) $^ $(LFLAGS) $(INCLUDE_PATH) -o $@

bin/%.o: src/%.c
	$(CC) $(STD) $(CFLAGS) -c $< $(LFLAGS) $(INCLUDE_PATH) -o $@

clean:
	rm -f bin/*.o
