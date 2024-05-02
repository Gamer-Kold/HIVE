CC := cc
CFLAGS := -g -I./include -lraylib -lm -L./lib


build/main: build/main.o build/level.o
	$(CC) $^ -o build/main $(CFLAGS) 

build/main.o: main.c
	$(CC) -c $< -o $@ $(CFLAGS)

build/level.o: level.c
	$(CC) -c $< -o $@ $(CFLAGS)

run: build/main
	./build/main
