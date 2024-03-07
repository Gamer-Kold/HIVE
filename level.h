#ifndef level_h_INCLUDED
#define level_h_INCLUDED

#define LEVEL_SIDE_LENGTH 25
#define TILE_SIZE_PIXELS 40
#define PLAYER_ARRAY_SIZE  5
#include <stdbool.h>
typedef enum Tiles { NOTHING, WALL, WIN } Tiles;
typedef enum Dir { UP, LEFT, RIGHT, DOWN } Dir;


typedef struct LevelState{
    enum Tiles *level;
    int players[PLAYER_ARRAY_SIZE];
} LevelState;
typedef struct LevelEditorState{
    enum Tiles mode;
    bool player_mode;
    // don't need to store this after level has begun, only when saving level
    int level_players[PLAYER_ARRAY_SIZE]; 
    int player_index;
    struct LevelState level_state;
    int levelScreenLength;

} LevelEditorState;



int GetFinalSlidingPointInDirection(int starting_point, Tiles *level,
                                    Dir dir); 
void DrawLevel(LevelState state);
void UpdateLevelState(LevelState *state);
void LevelEditorUpdate(LevelEditorState *state);
void LoadLevel(LevelState *level);
#endif // level_h_INCLUDED
