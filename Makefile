CC=gcc
STD=-std=c11

INCLUDE_PATH=-Isrc
LIBRARY_PATH=-Lpath/to/library
CFLAGS=
LFLAGS=-lSDL2

SRC=src/main.c src/render.c src/game.c
OBJ=$(SRC:src/.c=bin/.o)
EXEC=bin/pong

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(STD) $^ $(LFLAGS) $(INCLUDE_PATH) -o $@
#	$(CC) $(STD) $^ $(INCLUDE_PATH) $(LIBRARY_PATH) $(CFLAGS) $(LFLAGS) -o $@

bin/%.o: src/%.c
	$(CC) $(STD) -c $< $(LFLAGS) $(INCLUDE_PATH) -o $@

clean:
	rm -rf bin/*.o

