#include "types.h"
#include "stb_image.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>


Level LoadLevelFromFile(const char* filename){
	const uint32_t NONE_COL = 0x000000FF;
	const uint32_t WALL_COL = 0xFFFFFFFF;
	const uint32_t BEE_COL = 0xFFFF00FF;
	const uint32_t FLOWER_COL = 0xFF83EAFF;
	int x,y,n; 
	unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
	size_t size = x * y;
	assert((data != NULL) && "Data should not be null");
	assert((n == 4) && "The level format requires 4 colors");

	Tiles*    lvl_tiles = malloc(sizeof(Tiles) * size);
	uint16_t* bees = malloc(sizeof(uint16_t) * size);
	size_t bee_count = 0;
	uint16_t* flowers = malloc(sizeof(uint16_t) * size);
	size_t flower_count = 0;

	for(size_t i = 0; i < size; i++){
		size_t base_index = i * 4; // index of the start of the pixel data
		uint32_t red = data[base_index];
		uint32_t blue = data[base_index + 1];
		uint32_t green = data[base_index + 2];
		uint32_t alpha = data[base_index + 3];
		uint32_t pixel_color = (red << 24) | (blue << 16) | (green << 8) | alpha;
		if(pixel_color == NONE_COL) lvl_tiles[i] = NONE;
		else if(pixel_color == WALL_COL) lvl_tiles[i] = WALL;
		else if(pixel_color == BEE_COL){ 
			lvl_tiles[i] = NONE;
			bees[bee_count] = i;
			bee_count++;
		}
		else if(pixel_color == FLOWER_COL){ 
			lvl_tiles[i] = NONE;
			flowers[flower_count] = i;
			flower_count++;
		}
		else assert(0 && "INCORRECT COLOR INPUTTED");
	}
	uint16_t* bees_final = malloc(sizeof(uint16_t) * bee_count);
	memcpy(bees_final, bees, bee_count * sizeof(uint16_t));
	free(bees);
	uint16_t* flowers_final = malloc(sizeof(uint16_t) * flower_count);
	memcpy(flowers_final, flowers, flower_count * sizeof(uint16_t));
	free(flowers);
	Level lvl = {
		.level = lvl_tiles,
		.flowers = flowers_final,
		.number_of_flowers = flower_count,
		.bees = bees_final,
		.number_of_bees = bee_count,
		.width = x,
		.height = y,
	};
	stbi_image_free(data);
	return lvl;
}


