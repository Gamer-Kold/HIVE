#include "level.h"
#include "raylib.h"

typedef struct{
	Level current_level;
	char* current_level_file;
} GameState;

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
	for(size_t i = 0; i < level.number_of_bees; i++){
		unsigned int x = level.bees[i] % level.height;
		unsigned int y = (level.bees[i] - x) / level.height;

		DrawRectangle(x * 50, y * 50, 50, 50, YELLOW);
	}
	// Draw flowers
	for(size_t i = 0; i < level.number_of_flowers; i++){
		unsigned int x = level.flowers[i] % level.height;
		unsigned int y = (level.flowers[i] - x) / level.height;

		DrawRectangle(x * 50, y * 50, 50, 50, PINK);
	}
}

void game_init(GameState* state){
	state->current_level_file = "lvl_one.png";
	state->current_level = LoadLevelFromFile("lvl_one.png");
}

size_t get_game_state_size(){
	return sizeof(GameState);
}


int game_main(GameState* game_state){
	InitWindow(500, 500, "HIVE");
	while(!WindowShouldClose()){
		BeginDrawing();
		if(IsKeyReleased(KEY_R)){
			EndDrawing();
			CloseWindow();
			return 1; // Let the host know to hot reload
		}
		ClearBackground(RED);
		DrawLevel(game_state->current_level);
		EndDrawing();
	}
	CloseWindow();
	return 0;

}
