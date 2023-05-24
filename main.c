#include "level.h"
#include "raylib.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 1000;
  const int screenHeight = 1000;

  enum Tiles *level = malloc(sizeof(enum Tiles) * LEVEL_SIDE_LENGTH * LEVEL_SIDE_LENGTH);

  for (size_t i = 0; i < (LEVEL_SIDE_LENGTH * LEVEL_SIDE_LENGTH); i++) {
    level[i] = NOTHING;
  }

  struct LevelState level_state = {level, {-1, -1, -1, -1, -1}};
  struct LevelEditorState editor_state = {WALL, false, 0, level_state, 1000};
  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  // Set our game to run at 60 frames-per-second
  SetTargetFPS(60);
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    ClearBackground(RAYWHITE);

    LevelEditorUpdate(&editor_state);
    DrawLevel(&(editor_state.level_state));
    EndDrawing();

    //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
                 //--------------------------------------------------------------------------------------
  free(level);
  return 0;
}
