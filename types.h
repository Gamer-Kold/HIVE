
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED
typedef enum{
	NONE,
	WALL,
} Tiles;

typedef struct{
	float x;
	float y;
} EntityPosition;

typedef struct{
	Tiles* level;
	uint16_t* bees;
	size_t number_of_bees;
	uint16_t* flowers;
	size_t number_of_flowers;
	uint8_t width;
	uint8_t height;
} Level;

typedef enum {
	DIR_UP,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_DOWN,
} Dir;

typedef enum {
	GAMESTATE_IN_MENU,
	GAMESTATE_IN_LEVEL,
} GameStateTypes;


typedef enum{
	BEESTATE_STILL,
	BEESTATE_MOVING,
} BeeState;

/// Data required for the bee moving animation
typedef struct{
	EntityPosition* current_bee_pos;
	uint16_t* new_bee_pos;
	uint16_t* old_bee_pos;
	Dir direction;
	float elapsedTime;
} MovingBeeState;

typedef struct{
	/// The current level loaded in game
	Level current_level;
	/// The file the level was loaded from; used to reload the level
	const char* current_level_file;
	BeeState bee_state;
	/// IMPORTANT: THIS WILL BE NULL IF bee_state != BEESTATE_MOVING; ASSERT OFTEN DUMBASS(affectionate)
	MovingBeeState* moving_bee_state;
} LevelState;

typedef struct{
} MainMenuState;

typedef struct{
	GameStateTypes tag;
	union{
		LevelState lvl_state;
		MainMenuState menu_state;

	} value;
} GameState;


typedef struct{
	/// if *any* key is pressed
	bool is_key_pressed;
	/// Is a direction key pressed.
	bool is_dir_key_pressed;
	/// Input direction that the player has pressed down
	Dir input_dir;

} InputState;

/// Gets Level from a Level file
Level LoadLevelFromFile(const char* filename);
#endif // TYPES_H_INCLUDED
