#pragma once


enum WALL_SIDE {
	LEFT_WALL,
	RIGHT_WALL,
};

typedef struct Keys {
	bool E_KEY;
	bool D_KEY;
	bool UP_KEY;
	bool DOWN_KEY;
} Keys;

typedef struct Entity_ {
	float x;
	float y;
	float dx;
	float dy;
	int   w;
	int   h;
	float speed;
	Color color;
} Entity;

typedef struct Game_ {
	bool    is_running;
	Keys    keys;
	int     lscore;
	int     rscore;
	Entity *lpaddle;
	Entity *rpaddle;
	Entity *ball;
} Game;
