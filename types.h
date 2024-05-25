
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


typedef struct{
	Level current_level;
	const char* current_level_file;
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
