#include "level.h"
#include "dlfcn.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void  (*init)(void*) = NULL;
size_t (*get_plug_state_size)() = NULL;
int   (*plug_main)(void*) = NULL;
void* plugin_handle = NULL;

void ReloadGame(){
	if(plugin_handle != NULL){dlclose(plugin_handle);}

	plugin_handle = dlopen("build/plug.so", RTLD_NOW);
	assert((plugin_handle != NULL) && "COULD NOT LOAD S.O. TRY AGAIN");

	init = dlsym(plugin_handle, "game_init");
	assert((init != NULL) && "COULD NOT LOAD S.O. TRY AGAIN");
	plug_main = dlsym(plugin_handle, "game_main");
	assert((plug_main != NULL) && "COULD NOT LOAD S.O. TRY AGAIN");
	get_plug_state_size = dlsym(plugin_handle, "get_game_state_size");
	assert((get_plug_state_size != NULL) && "COULD NOT LOAD S.O. TRY AGAIN");

}

int main(){
	ReloadGame();
	size_t game_state_size = get_plug_state_size();
	void* state = malloc(game_state_size);
	init(state);

	while(true) {
		int result = plug_main(state);
		if(result == 1){ // HOT RELOAD TIME BBY
			system("make build/plug.so");
			ReloadGame();
			if(game_state_size != get_plug_state_size()){
				free(state);
				game_state_size = get_plug_state_size();
				state = malloc(game_state_size);
				init(state);
			}
		}
		else{
			break;
		}
	}

	return 0;
}
