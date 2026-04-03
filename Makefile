.PHONY: run clean

index.html: game_kitty.c
	emcc game_kitty.c -o index.html -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png","jpg"]' --embed-file spritesheet.png

run: index.html
	emrun index.html

clean:
	rm index.js index.wasm index.html