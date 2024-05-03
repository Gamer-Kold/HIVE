#include "raylib.h"
#include "level.h"


typedef struct{} GameState;

const Color level_colors[] = {BLACK, YELLOW, PINK, WHITE};
void DrawLevel(Level level){
	for(int i = 0; i < level.width; i++){
		for(int j = 0; j < level.height; j++){
		Tiles tile = level.level[(j * level.height) + i];
			DrawRectangle(i * 50 + 5, j * 50 + 5, 50 - 10, 50 - 10, level_colors[tile]);
		}
	}
}


int main(){
	InitWindow(500, 500, "HIVE");
	GameState game_state = {0};
	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(BLACK);
		game_state = UpdateGameState(game_state);
		DrawLevel(GetLevel(0));
		DrawGameState(game_state);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
