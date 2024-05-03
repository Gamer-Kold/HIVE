
#include <stddef.h>
#include <stdint.h>
typedef enum{
	NONE,
	WALL,
} Tiles;

typedef struct{
	Tiles* level;
	int* bees;
	size_t number_of_bees;
	int* flowers;
	size_t number_of_flowers;
	uint8_t width;
	uint8_t height;
} Level;


/// Gets Level from the ones defined in code.
Level GetLevel(int index);
