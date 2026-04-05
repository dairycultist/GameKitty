.PHONY: run clean

build: *.c
	mkdir -p build
	emcc $^ -o build/index.html -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' --embed-file spritesheet.png
	sudo chmod -R 777 build
	cp index.html build/index.html

run: build
	emrun build/index.html --no_browser

clean:
	rm build/index.js build/index.wasm build/index.html