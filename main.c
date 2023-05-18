#include "raylib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

const int levelSideLength = 25;
const int tilesSizeInPixels = 40;


enum Tiles{
	NOTHING,
	WALL,
	WIN
};

enum Dir{
    UP,
    LEFT,
    RIGHT,
    DOWN
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

int GetFinalSlidingPointInDirection(int starting_point, enum Tiles* level, enum Dir dir)
{

    int i = 0;
    const int levelSize = levelSideLength * levelSideLength;
    const int offsets[] = {-levelSideLength, -1, 1, levelSideLength};
    while(i < levelSize && (i + starting_point) >= 0){
        if(level[starting_point + i] == WALL)
            break;
        i = i + offsets[dir];
        fprintf(stderr, "Progression:%d", i);
    }
    return starting_point + i - offsets[dir];
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
	int players[] = {70, -1, -1, -1 , -1};
	const int players_size = 5;

	for (size_t i = 0; i < (levelSideLength * levelSideLength); i++) {
		level[i] = NOTHING;
	}

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");



	enum Tiles mode = WALL;


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

		// memory safety is a bitch
		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && GetMouseX() > 0 && GetMouseX() < screenWidth && GetMouseY() > 0 && GetMouseY() < screenHeight )
			level[(GetMouseY()/tilesSizeInPixels) * levelSideLength + (GetMouseX() / tilesSizeInPixels)] = mode;
		if(IsKeyDown(KEY_ONE))
			mode = WALL;
		if(IsKeyDown(KEY_TWO))
			mode = WIN;
		if(IsKeyDown(KEY_THREE))
			mode = NOTHING;

    	enum Dir direction = -1;
    	bool player_moved = false;


        if(IsKeyPressed(KEY_W))
		{
    		direction = UP;
    		player_moved = true;
        }		
        if(IsKeyPressed(KEY_A))
		{
    		direction = LEFT;
    		player_moved = true;
        }		
        if(IsKeyPressed(KEY_S))
		{
    		direction = DOWN;
    		player_moved = true;
        }		
        if(IsKeyPressed(KEY_D))
		{
    		direction = RIGHT;
    		player_moved = true;
        }


        if(player_moved)
        {
            for(size_t i = 0;i < players_size; i++)
            {
                if(players[i] >= 0)
                    players[i] = GetFinalSlidingPointInDirection(players[i], level, direction);
            }
        }

        for(size_t i = 0;i < players_size; i++)
        {
            if(players[i] >= 0)
                DrawRectangle( mod(players[i], levelSideLength) * tilesSizeInPixels, (players[i] / levelSideLength) * tilesSizeInPixels, tilesSizeInPixels, tilesSizeInPixels, BLUE);
        }

		DrawLevel(level);
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
			      //--------------------------------------------------------------------------------------
	return 0;
}
