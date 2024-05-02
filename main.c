#include "raylib.h"
#include "level.h"



const Color level_colors[] = {BLACK, YELLOW, PINK, WHITE};
void DrawLevel(Level level){
	for(int i = 0; i < level.width; i++){
		for(int j = 0; j < level.height; j++){
			Tiles tile = level.level[(i * level.width) + j];
			DrawRectangle(i * 100, j * 100, 100, 100, level_colors[tile]);
		}
	}
}


int main(){
	InitWindow(500, 500, "HIVE");
	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(RED);
		DrawLevel(GetLevel(0));
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
