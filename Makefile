.PHONY: demo clean

Berry2D: Berry2D.c
	gcc -o Berry2D Berry2D.c -lSDL2_image $(shell sdl2-config --cflags) $(shell sdl2-config --libs)

demo: Berry2D
	./Berry2D demo.txt demo.png

clean:
	rm Berry2D