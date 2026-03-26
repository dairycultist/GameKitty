.PHONY: demo clean

GameKitty: game_kitty.c asm_to_bin.c
	gcc -o GameKitty game_kitty.c asm_to_bin.c -lSDL2_image $(shell sdl2-config --cflags) $(shell sdl2-config --libs)

demo: GameKitty
	./GameKitty demo.txt demo.png

clean:
	rm GameKitty