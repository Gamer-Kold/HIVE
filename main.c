#include "raylib.h"
#include "level.h"
#include "dlfcn.h"
#include <assert.h>
#include <stdlib.h>
#include "plug_main.h"

int main(){
	InitWindow(500, 500, "HIVE");
	GameState* state = malloc(sizeof(GameState));
	void* plugin_handle = dlopen("build/plug.so", RTLD_NOW);
	TraceLog(LOG_INFO, "%s", dlerror());
	assert((plugin_handle != NULL) && "COULD NOT LOAD S.O. TRY AGAIN");

	void (*init)(GameState*) = dlsym(plugin_handle, "plug_init");
	assert((init != NULL) && "COULD NOT LOAD S.O. TRY AGAIN");
	void (*draw)(GameState*) = dlsym(plugin_handle, "plug_draw");
	assert((draw != NULL) && "COULD NOT LOAD S.O. TRY AGAIN");
	init(state);

	while(!WindowShouldClose()){
		draw(state);
	}

	CloseWindow();
	return 0;
}
