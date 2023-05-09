#include "raylib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

const int levelSideLength = 25;
const int tilesSizeInPixels = 40;


enum Tiles{
	NOTHING,
	WALL,
	PLAYER,
	WIN
};



int mod(int a, int b){
	int div = a / b;

	return (a - (div * b));
	
}


void DrawLevel(enum Tiles* lvl){
	
	const Color col[] = {GRAY, BLUE, GREEN};
	for (size_t i = 0; i < (levelSideLength * levelSideLength); i++) {
		if(lvl[i] == NOTHING)
			continue;

		int x = mod(i, levelSideLength);
		int y = i / levelSideLength;

		DrawRectangle(x * tilesSizeInPixels, y * tilesSizeInPixels, tilesSizeInPixels, tilesSizeInPixels, col[lvl[i] - 1]);
	}
}


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void){
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1000;
    const int screenHeight = 1000;


    enum Tiles level[levelSideLength * levelSideLength];


    for (size_t i = 0; i < (levelSideLength * levelSideLength); i++) {
	    level[i] = NOTHING;
    }

    level[6] = WALL;
    level[7] = PLAYER;
    level[8] = WIN;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");



    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

	    DrawLevel(level);

	    if(IsKeyDown(KEY_W))
			    printf("W");
	    if(IsKeyDown(KEY_A))
			    printf("A");
	    if(IsKeyDown(KEY_S))
			    printf("S");
	    if(IsKeyDown(KEY_D))
			    printf("D");


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}
