#include "../types.h"
LevelState InitLevelState(const char* level_file);
void UpdateLevelState(LevelState* lvl_state, InputState input);
void DrawLevel(LevelState lvl_state);

