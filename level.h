
#include <stdint.h>
typedef enum{
	EMPTY,
	BEE,
	FLOWER,
	WALL,
} Tiles;

typedef struct{
	Tiles* level;
	uint8_t width;
	uint8_t height;
} Level;


/// Gets Level from the ones defined in code.
Level GetLevel(int index);
