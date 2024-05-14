#include "types.h"
#include "raylib.h"

const Color level_colors[] = {BLACK, WHITE};

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

void DrawMainMenu(MainMenuState state){
	ClearBackground(BLACK);
	const int scr_width = GetScreenWidth();
	const int scr_height = GetScreenHeight();
	const char* title_text = "HIVE";
	const int font_size = 60;
	DrawText(title_text, (int)(scr_width * 0.5) - (MeasureText(title_text, font_size) / 2), scr_height * 0.25, font_size, WHITE);
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
	if(input.is_key_pressed && state->tag == GAMESTATE_IN_LEVEL){
		LevelState lvl_state = state->value.lvl_state;
		size_t number_of_bees_on_flowers = 0;
		for(uint16_t i = 0; i < lvl_state.current_level.number_of_bees; i++){
			uint16_t bee_pos = lvl_state.current_level.bees[i];
			bee_pos = GetNextOpenSpaceInDirection(lvl_state.current_level, bee_pos, input.input_dir); 
			lvl_state.current_level.bees[i] = bee_pos;
			// Check if a bee is now on a flower
			bool bee_on_flower = false;
			for(uint16_t j = 0; j < lvl_state.current_level.number_of_flowers; j++){
				if(lvl_state.current_level.flowers[j] == bee_pos){
					bee_on_flower = true;
				}
			}
			if(bee_on_flower) number_of_bees_on_flowers++;
		}
		if(number_of_bees_on_flowers == lvl_state.current_level.number_of_bees){
			TraceLog(LOG_INFO, "-----------------");
			TraceLog(LOG_INFO, "We won!!");
			TraceLog(LOG_INFO, "-----------------");
		}
	}
}


void game_init(GameState* state){
	state->tag = GAMESTATE_IN_MENU;
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
		if(game_state->tag == GAMESTATE_IN_LEVEL)
			DrawLevel(game_state->value.lvl_state.current_level);
		if(game_state->tag == GAMESTATE_IN_MENU)
			DrawMainMenu(game_state->value.menu_state);
		EndDrawing();
	}
	CloseWindow();
	return 0;

}
