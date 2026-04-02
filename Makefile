.PHONY: demo clean

GameKitty: game_kitty.c
	gcc -o GameKitty game_kitty.c -lSDL2_image $(shell sdl2-config --cflags) $(shell sdl2-config --libs)

demo: GameKitty
	./GameKitty

clean:
	rm GameKitty