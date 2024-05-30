#include "types.h"
#include "raylib.h"
#include <assert.h>
#include <stdlib.h>

#define BEE_MOVE_DURATION 0.2f

const Color level_colors[] = {BLACK, WHITE};

InputState GetInputState(){
	InputState state = {0};
	state.is_key_pressed = (GetKeyPressed() != 0);
	state.is_dir_key_pressed = true;
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
	}
	else{
		state.is_dir_key_pressed = false;
	}
	return state;
}

void DrawLevel(LevelState state){
	Level level = state.current_level;
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
		float x,y;
		if(state.bee_state == BEESTATE_STILL){
			x = ((int)level.bees[i]) % level.height;
			y = (level.bees[i] - x) / level.height;
		}
		else if(state.bee_state == BEESTATE_MOVING){
			assert((state.moving_bee_state != NULL) && "moving_bee_state cannot be null when bees are moving");
			x = state.moving_bee_state->current_bee_pos[i].x;
			y = state.moving_bee_state->current_bee_pos[i].y;
		}
		else{
			assert(false && "This cannot be reached");
		}

		DrawRectangle(x * 50, y * 50, 50, 50, YELLOW);
	}
}

LevelState InitLevelState(const char* level_file){
	LevelState state = {0}; 
	state.current_level = LoadLevelFromFile(level_file);
	state.current_level_file = level_file;
	state.bee_state = BEESTATE_STILL;
	state.moving_bee_state = NULL;
	return state;
}

void DrawMainMenu(MainMenuState state){
	ClearBackground(BLACK);
	const int scr_width = GetScreenWidth();
	const int scr_height = GetScreenHeight();
	const char* title_text = "HIVE";
	const int font_size = 60;
	DrawText(title_text, (int)(scr_width * 0.5) - (MeasureText(title_text, font_size) / 2), scr_height * 0.25, font_size, WHITE);
	const char* press_text = "Press Any Key";
	DrawText(press_text, (int)(scr_width * 0.5) - (MeasureText(press_text, font_size / 3) / 2), scr_height * 0.75, font_size / 3, WHITE);
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
	if(state->tag == GAMESTATE_IN_LEVEL){
		LevelState lvl_state = state->value.lvl_state;
		if(input.is_dir_key_pressed && lvl_state.bee_state == BEESTATE_STILL){
			size_t number_of_bees_on_flowers = 0;
			MovingBeeState* moving_bee_state = malloc(sizeof(MovingBeeState));
			
			uint16_t* old_bee_pos = malloc(sizeof(uint16_t) * lvl_state.current_level.number_of_bees);
			uint16_t* new_bee_pos = malloc(sizeof(uint16_t) * lvl_state.current_level.number_of_bees);
			EntityPosition* current_bee_pos = malloc(sizeof(EntityPosition) * lvl_state.current_level.number_of_bees);

			moving_bee_state->old_bee_pos = old_bee_pos;
			moving_bee_state->new_bee_pos = new_bee_pos;
			moving_bee_state->current_bee_pos = current_bee_pos;

			moving_bee_state->direction = input.input_dir;
			moving_bee_state->elapsedTime = 0;

			const uint16_t level_height = lvl_state.current_level.height;

			for(uint16_t i = 0; i < lvl_state.current_level.number_of_bees; i++){

				uint16_t bee_pos = lvl_state.current_level.bees[i];

				uint16_t x = (bee_pos) % level_height;
				uint16_t y = (bee_pos - x) / level_height;

				EntityPosition pos = {.x = x, .y = y};
				moving_bee_state->current_bee_pos[i] = pos;
				moving_bee_state->old_bee_pos[i] = bee_pos;

				bee_pos = GetNextOpenSpaceInDirection(lvl_state.current_level, bee_pos, input.input_dir); 

				moving_bee_state->new_bee_pos[i] = bee_pos;

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

			state->value.lvl_state.bee_state = BEESTATE_MOVING;
			state->value.lvl_state.moving_bee_state = moving_bee_state;

			if(number_of_bees_on_flowers == lvl_state.current_level.number_of_bees){
				TraceLog(LOG_INFO, "-----------------");
				TraceLog(LOG_INFO, "We won!!");
				TraceLog(LOG_INFO, "-----------------");
			}

		}
		else if(lvl_state.bee_state == BEESTATE_MOVING){
			MovingBeeState* moving_bee_state = lvl_state.moving_bee_state;
			assert((moving_bee_state != NULL) && "moving_bee_state must not be NULL");

			moving_bee_state->elapsedTime += GetFrameTime();
			if(moving_bee_state->elapsedTime >= BEE_MOVE_DURATION)
			{
				state->value.lvl_state.bee_state = BEESTATE_STILL;
				free((void *)moving_bee_state);
				state->value.lvl_state.moving_bee_state = NULL;
			}
			else{
				Dir dir = moving_bee_state->direction;
				const float t = moving_bee_state->elapsedTime / BEE_MOVE_DURATION;
				if(dir == DIR_UP || dir == DIR_DOWN){
					for(size_t i = 0; i < lvl_state.current_level.number_of_bees; i++){
						const int32_t height = (lvl_state.current_level.height);
						const int32_t old_y = moving_bee_state->old_bee_pos[i] / height;
						const int32_t new_y = moving_bee_state->new_bee_pos[i] / height;
						const float dy = (new_y) - (old_y);


						state->value.lvl_state.moving_bee_state->current_bee_pos[i].y = (t * t * dy) + old_y;

					}
				}
				else if (dir == DIR_LEFT || dir == DIR_RIGHT){

					for(size_t i = 0; i < lvl_state.current_level.number_of_bees; i++){
						const int32_t height = (lvl_state.current_level.height);
						const int32_t old_x = moving_bee_state->old_bee_pos[i] % height;
						const int32_t new_x = moving_bee_state->new_bee_pos[i] % height;
						const float dx = (new_x) - (old_x);


						state->value.lvl_state.moving_bee_state->current_bee_pos[i].x = (t * t * dx) + old_x;

					}
				}
				else{
				}
			}
		}
	}
	else if(state->tag == GAMESTATE_IN_MENU){
		if(input.is_key_pressed){
			state->tag = GAMESTATE_IN_LEVEL;
			state->value.lvl_state = InitLevelState("zig-out/levels/lvl_one.png");
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
			DrawLevel(game_state->value.lvl_state);
		if(game_state->tag == GAMESTATE_IN_MENU)
			DrawMainMenu(game_state->value.menu_state);
		EndDrawing();
	}
	CloseWindow();
	return 0;

}

int main(){
	GameState state = {0};
	game_init(&state);
	game_main(&state);
}
