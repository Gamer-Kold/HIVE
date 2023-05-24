#ifndef level_h_INCLUDED
#define level_h_INCLUDED

#define LEVEL_SIDE_LENGTH 25
#define TILE_SIZE_PIXELS 40
#define PLAYER_ARRAY_SIZE  5
#include <stdbool.h>
enum Tiles { NOTHING, WALL, WIN };
enum Dir { UP, LEFT, RIGHT, DOWN };


struct LevelState{
    enum Tiles *level;
    int players[5];
};
struct LevelEditorState{
    enum Tiles mode;
    bool player_mode;
    int player_index;
    struct LevelState level_state;
    int levelScreenLength;

};



int GetFinalSlidingPointInDirection(int starting_point, enum Tiles *level,
                                    enum Dir dir); 
void DrawLevel(struct LevelState state);
void UpdateLevelState(struct LevelState *state);
void LevelEditorUpdate(struct LevelEditorState *state);
void LoadLevel(struct LevelState *level);
#endif // level_h_INCLUDED
