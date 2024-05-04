#include "level.h"
#include "raylib.h"
#include "plug_main.h"

const Color level_colors[] = {BLACK, WHITE};
void DrawLevel(Level level){
	// Draw Level tile"
	for(int i = 0; i < level.width; i++){
		for(int j = 0; j < level.height; j++){
		Tiles tile = level.level[(j * level.height) + i];
			DrawRectangle(i * 50, j * 50, 50, 50, level_colors[tile]);
		}
	}
	// Draw Bees
	for(int i = 0; i < level.number_of_bees; i++){
		unsigned int x = level.bees[i] % level.height;
		unsigned int y = (level.bees[i] - x) / level.height;

		DrawRectangle(x * 50, y * 50, 50, 50, YELLOW);
	}
	// Draw flowers
	for(int i = 0; i < level.number_of_flowers; i++){
		unsigned int x = level.flowers[i] % level.height;
		unsigned int y = (level.flowers[i] - x) / level.height;

		DrawRectangle(x * 50, y * 50, 50, 50, PINK);
	}
}

void plug_init(GameState* state){
	state->current_level_file = "lvl_one.png";
	state->current_level = LoadLevelFromFile("lvl_one.png");
}

void plug_draw(GameState* game_state){
	ClearBackground(RED);
	DrawLevel(game_state->current_level);
}
