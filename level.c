#include "level.h"

const Tiles level_one[] = {
	WALL, EMPTY, EMPTY, EMPTY, WALL,
	WALL, EMPTY, EMPTY, EMPTY, WALL,
	WALL, EMPTY, EMPTY, EMPTY, WALL,
	WALL, EMPTY, EMPTY, EMPTY, WALL,
	WALL, EMPTY, EMPTY, EMPTY, WALL,
};

const Level levels[] = {
	{
		.level = ((Tiles *)level_one),
		.width = 5,
		.height = 5,
	},
};

Level GetLevel(int index){
	return levels[index];
}
