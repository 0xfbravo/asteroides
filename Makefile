all:
	gcc -Wall engine.c -o engine -lSDL -lSDL_ttf -lSDL_image -lSDL_gfx -lm -g
