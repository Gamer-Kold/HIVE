CC := cc
CFLAGS := -g -fPIC -I./include -Wall -Wextra -lraylib -lm -L./lib

build/plug.so: build/plug_main.o build/level.o
	$(CC) $^ -shared -o build/plug.so $(CFLAGS) 

build/main: main.c
	$(CC) $< -o $@ -Wall -Wextra -g -I./include

build/plug_main.o: plug_main.c types.h
	$(CC) $(CFLAGS) -c $< -o $@ 
build/level.o: level.c types.h
	$(CC) $(CFLAGS) -c $< -o $@ 

run: build/main build/plug.so
	./build/main
debug: build/main build/plug.so
	gdb ./build/main

clean: 
	rm ./build/*
