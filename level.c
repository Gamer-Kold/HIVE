#include "level.h"
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void SaveLevel(struct LevelState state)
{
    FILE *level_file = fopen("level.txt", "w");
    if(level_file == NULL)
    {
        fprintf(stderr, "error loading file");  
        return;
    }

    for(int i = 0; i < 5; i++)
        fprintf(level_file, "%d\n", state.players[i]); 

    for (int i = 0; i < (LEVEL_SIDE_LENGTH * LEVEL_SIDE_LENGTH); i++) {
        fprintf(level_file, "%d\n", state.level[i]);
    }

    fclose(level_file);
}

void LoadLevel(struct LevelState *state)
{

    FILE *level_file = fopen("level.txt", "r");
    if(level_file == NULL)
    {
        fprintf(stderr, "error loading file");  
        return;
    }

    for(int i = 0; i < 5; i++)
        fscanf(level_file, "%d\n", state->players + i);

    for (int i = 0; i < (LEVEL_SIDE_LENGTH * LEVEL_SIDE_LENGTH); i++) {
        fscanf(level_file, "%d\n", (state->level + i));
    }

    fclose(level_file);
}

void LevelEditorUpdate(struct LevelEditorState *state) {
  // memory safety is a bitch
  struct LevelState level_state = state->level_state;
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && GetMouseX() > 0 &&
      GetMouseX() < state->levelScreenLength && GetMouseY() > 0 &&
      GetMouseY() < state->levelScreenLength) {
    SaveLevel(level_state);
    int index = (GetMouseY() / TILE_SIZE_PIXELS) * LEVEL_SIDE_LENGTH +
                (GetMouseX() / TILE_SIZE_PIXELS);
    if (state->player_mode) {
      level_state.players[state->player_index] = index;
      if (state->player_index == 4) {
        state->player_index = 0;
      } else {
        state->player_index++;
      }
    } else
      level_state.level[index] = state->mode;
  }

  if (IsKeyDown(KEY_ONE)) {
    state->mode = WALL;
    state->player_mode = false;
  } else if (IsKeyDown(KEY_TWO)) {
    state->mode = WIN;
    state->player_mode = false;
  } else if (IsKeyDown(KEY_THREE)) {
    state->mode = NOTHING;
    state->player_mode = false;
  } else if (IsKeyDown(KEY_FOUR)) {
    state->player_mode = true;
  }

  state->level_state = level_state;
}

int GetFinalSlidingPointInDirection(int starting_point, enum Tiles *level,
                                    enum Dir dir) {

  int i = 0;
  const int levelSize = LEVEL_SIDE_LENGTH * LEVEL_SIDE_LENGTH;
  const int offsets[] = {-LEVEL_SIDE_LENGTH, -1, 1, LEVEL_SIDE_LENGTH};
  while ((i + starting_point) < levelSize && (i + starting_point) >= 0) {
    if (level[starting_point + i] == WALL)
      break;
    i = i + offsets[dir];
  }
  return starting_point + i - offsets[dir];
}

int mod(int a, int b) {
  int div = a / b;

  return (a - (div * b));
}

void DrawLevel(struct LevelState state) {

  const Color col[] = {GRAY, GREEN};
  enum Tiles *lvl = state.level;
  for (size_t i = 0; i < (LEVEL_SIDE_LENGTH * LEVEL_SIDE_LENGTH); i++) {
    if (lvl[i] == NOTHING)
      continue;

    int x = mod(i, LEVEL_SIDE_LENGTH);
    int y = i / LEVEL_SIDE_LENGTH;

    DrawRectangle(x * TILE_SIZE_PIXELS, y * TILE_SIZE_PIXELS,
                  TILE_SIZE_PIXELS, TILE_SIZE_PIXELS, col[lvl[i] - 1]);
  }
  for (size_t i = 0; i < PLAYER_ARRAY_SIZE; i++) {
    if (state.players[i] >= 0) {
      // Draw Players
      DrawRectangle(
          mod(state.players[i], LEVEL_SIDE_LENGTH) * TILE_SIZE_PIXELS + 1,
          (state.players[i] / LEVEL_SIDE_LENGTH) * TILE_SIZE_PIXELS + 1,
          TILE_SIZE_PIXELS - 2, TILE_SIZE_PIXELS - 2, BLUE);

      }
    }
}

void UpdateLevelState(struct LevelState *state) {
  enum Dir direction = -1;
  bool player_moved = true;

  if (IsKeyPressed(KEY_W)) {
    direction = UP;

  } else if (IsKeyPressed(KEY_A)) {
    direction = LEFT;

  } else if (IsKeyPressed(KEY_S)) {
    direction = DOWN;

  } else if (IsKeyPressed(KEY_D)) {
    direction = RIGHT;

  } else {
    player_moved = false;
  }

  bool player_won = true;
  if (player_moved) {
    for (size_t i = 0; i < PLAYER_ARRAY_SIZE; i++) {
      if (state->players[i] >= 0)
        state->players[i] = GetFinalSlidingPointInDirection(
            state->players[i], state->level, direction);
    }
  }

  for (size_t i = 0; i < PLAYER_ARRAY_SIZE; i++) {
    if (state->players[i] >= 0) {
      // Draw Players
      DrawRectangle(
          mod(state->players[i], LEVEL_SIDE_LENGTH) * TILE_SIZE_PIXELS + 1,
          (state->players[i] / LEVEL_SIDE_LENGTH) * TILE_SIZE_PIXELS + 1,
          TILE_SIZE_PIXELS - 2, TILE_SIZE_PIXELS - 2, BLUE);

      // Check if all players are on a WIN block
      if (player_won) {
        player_won = (state->level[state->players[i]] == WIN);
      }
    }

    if (player_won) {
    }
  }
}



