
#include <stddef.h>
#include <stdint.h>

#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED
typedef enum{
	NONE,
	WALL,
} Tiles;

typedef struct{
	Tiles* level;
	uint16_t* bees;
	size_t number_of_bees;
	uint16_t* flowers;
	size_t number_of_flowers;
	uint8_t width;
	uint8_t height;
} Level;


/// Gets Level from a Level file
Level LoadLevelFromFile(char* filename);
#endif
