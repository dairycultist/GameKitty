.PHONY: run clean

index.html: *.c
	emcc $^ -o index.html -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --embed-file spritesheet.png

run: index.html
	emrun index.html --no_browser

clean:
	rm index.js index.wasm index.html