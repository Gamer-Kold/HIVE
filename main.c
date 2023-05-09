#include "raylib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum Tiles{
	NOTHING,
	WALL,
	PLAYER,
	WIN
};

struct Level{
	int width;
	int height;
	enum Tiles* tiles;
};


int mod(int a, int b)
{
	int div = a / b;

	return (a - (div * b));
	
}

void DrawLevel(struct Level lvl){
	for(size_t i = 0; i < 100 ; i++)
	{
		Color col;
		if(lvl.tiles[i] == WALL)
			col = GRAY;
		else if (lvl.tiles[i] == PLAYER)
			col = BLUE;
		else if (lvl.tiles[i] == WIN)
			col = GREEN;
		else 
			continue;
		int x = mod(i, 10);
		int y = i/10;

		DrawRectangle(x * 100,  y * 100, 100, 100, col);
	}
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1000;
    const int screenHeight = 1000;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    struct Level test = {10, 10, malloc(sizeof(enum Tiles) * 10 * 10)};

    for(size_t i = 0; i < 100 ; i++)
    {
	test.tiles[i] = NOTHING;
    }

    test.tiles[5] = PLAYER;

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

            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

	    DrawLevel(test);

	    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	    {
		    int x = GetMouseX() / 100;
		    int y = GetMouseY() / 100;    

		    test.tiles[(y * 10) + x] = WALL;
	    }

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

    free(test.tiles);

    return 0;
}
