#include "types.h"
#include "level/level.h"
#include "raylib.h"


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


void UpdateGameState(GameState* state, InputState input){
	if(state->tag == GAMESTATE_IN_LEVEL){
		UpdateLevelState(&state->value.lvl_state, input);
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
