.PHONY: demo clean

GameKitty: GameKitty.c
	gcc -o GameKitty GameKitty.c -lSDL2_image $(shell sdl2-config --cflags) $(shell sdl2-config --libs)

demo: GameKitty
	./GameKitty demo.txt demo.png

clean:
	rm GameKitty