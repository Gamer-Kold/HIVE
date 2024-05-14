#include "level.h"
#include "raylib.h"

typedef enum {
	DIR_UP,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_DOWN,
} Dir;

typedef struct{
	bool is_key_pressed;
	/// Input direction that the player has pressed down
	Dir input_dir;
} InputState;

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
	// Draw flowers
	for(size_t i = 0; i < level.number_of_flowers; i++){
		unsigned int x = level.flowers[i] % level.height;
		unsigned int y = (level.flowers[i] - x) / level.height;

		DrawRectangle(x * 50, y * 50, 50, 50, PINK);
	}
	// Draw Bees
	for(size_t i = 0; i < level.number_of_bees; i++){
		unsigned int x = level.bees[i] % level.height;
		unsigned int y = (level.bees[i] - x) / level.height;

		DrawRectangle(x * 50, y * 50, 50, 50, YELLOW);
	}
}

uint16_t GetNextOpenSpaceInDirection(Level lvl, uint16_t initial_position, Dir direction){
	const int32_t offsets[4] = {-lvl.width, -1, +1, lvl.width};
	uint16_t pos = initial_position;
	do {
		pos += offsets[direction];
	}
	while(pos < (lvl.width * lvl.height) && lvl.level[pos] != WALL);
	// we subtract the offset here because we've gone one over the obstacle
	return pos - offsets[direction];
}

void UpdateGameState(GameState* state, InputState input){
	if(input.is_key_pressed){
		size_t number_of_bees_on_flowers = 0;
		for(uint16_t i = 0; i < state->current_level.number_of_bees; i++){
			uint16_t bee_pos = state->current_level.bees[i];
			bee_pos = GetNextOpenSpaceInDirection(state->current_level, bee_pos, input.input_dir); 
			state->current_level.bees[i] = bee_pos;
			// Check if a bee is now on a flower
			bool bee_on_flower = false;
			for(uint16_t j = 0; j < state->current_level.number_of_flowers; j++){
				if(state->current_level.flowers[j] == bee_pos){
					bee_on_flower = true;
				}
			}
			if(bee_on_flower) number_of_bees_on_flowers++;
		}
		if(number_of_bees_on_flowers == state->current_level.number_of_bees){
			TraceLog(LOG_INFO, "-----------------");
			TraceLog(LOG_INFO, "We won!!");
			TraceLog(LOG_INFO, "-----------------");
		}
	}
}

InputState GetInputState(){
	InputState state = {0};
	state.is_key_pressed = true;
	if(IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){
		state.input_dir = DIR_UP;
	}
	else if(IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)){
		state.input_dir = DIR_DOWN;
	}
	else if(IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)){
		state.input_dir = DIR_LEFT;
	}
	else if(IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)){
		state.input_dir = DIR_RIGHT;
	} else state.is_key_pressed = false;
	return state;
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

		InputState input_state = GetInputState();
		UpdateGameState(game_state, input_state);
		ClearBackground(RED);
		DrawLevel(game_state->current_level);
		EndDrawing();
	}
	CloseWindow();
	return 0;

}
