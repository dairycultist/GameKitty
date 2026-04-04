#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <emscripten.h>

#include "game_kitty.h"

/*
 * rendering
 */
static SDL_Renderer *renderer;
static SDL_Texture *screen_buffer;
static SDL_Texture *spritesheet;

static unsigned char clear_r = 0, clear_g = 0, clear_b = 0;

void set_clear_color(unsigned char r, unsigned char g, unsigned char b) {

	clear_r = r;
	clear_g = g;
	clear_b = b;
}

void draw_sprite(unsigned int index, int x, int y, int flip) {

	SDL_Rect copy_rect = {

		(index % SPRS_WIDTH) * SPR_DIM,
		(index / SPRS_WIDTH) * SPR_DIM,
		SPR_DIM,
		SPR_DIM
	};

	SDL_Rect paste_rect = { x, y, SPR_DIM, SPR_DIM };

	SDL_RenderCopyEx(renderer, spritesheet, &copy_rect, &paste_rect, 0.0, NULL, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

/*
 * emscripten main loop
 */
static SDL_Event event;
static SDL_Rect letterbox = { 0, 0, WIDTH * 2, HEIGHT * 2 };

static Input input;

static void main_loop() {

	input.up_justchanged       = 0;
	input.down_justchanged     = 0;
	input.left_justchanged     = 0;
	input.right_justchanged    = 0;
	input.action_a_justchanged = 0;
	input.action_b_justchanged = 0;
	input.action_x_justchanged = 0;
	input.action_y_justchanged = 0;

	while (SDL_PollEvent(&event)) {

		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {

			#define MIN(a, b) ((a) > (b) ? (b) : (a))

			// dynamically change letterbox based on screen resize
			letterbox.w = MIN(event.window.data1, event.window.data2 * ASPECT_RATIO);
			letterbox.h = MIN(event.window.data2, event.window.data1 / ASPECT_RATIO);

			letterbox.x = (event.window.data1 - letterbox.w) / 2;
			letterbox.y = (event.window.data2 - letterbox.h) / 2;

		} else if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && !event.key.repeat) {

			switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_UP:
					input.up = event.key.state == SDL_PRESSED;
					input.up_justchanged = 1;
					break;
				case SDL_SCANCODE_DOWN:
					input.down = event.key.state == SDL_PRESSED;
					input.down_justchanged = 1;
					break;
				case SDL_SCANCODE_LEFT:
					input.left = event.key.state == SDL_PRESSED;
					input.left_justchanged = 1;
					break;
				case SDL_SCANCODE_RIGHT:
					input.right = event.key.state == SDL_PRESSED;
					input.right_justchanged = 1;
					break;
				case SDL_SCANCODE_Z:
					input.action_a = event.key.state == SDL_PRESSED;
					input.action_a_justchanged = 1;
					break;
				case SDL_SCANCODE_X:
					input.action_b = event.key.state == SDL_PRESSED;
					input.action_b_justchanged = 1;
					break;
				case SDL_SCANCODE_A:
					input.action_x = event.key.state == SDL_PRESSED;
					input.action_x_justchanged = 1;
					break;
				case SDL_SCANCODE_S:
					input.action_y = event.key.state == SDL_PRESSED;
					input.action_y_justchanged = 1;
					break;
				default:
					break;
			}
		}
	}

	SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255); 					// clear window to grey
	SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, screen_buffer); 						// set render target to screen_buffer
	SDL_SetRenderDrawColor(renderer, clear_r, clear_g, clear_b, 255); 	// clear screen_buffer to clear color (default black)
	SDL_RenderClear(renderer);

	GK_frame(&input);

	SDL_SetRenderTarget(renderer, NULL); 								// reset render target back to window
	SDL_RenderCopy(renderer, screen_buffer, NULL, &letterbox); 			// render screen_buffer
	SDL_RenderPresent(renderer); 										// present rendered content to screen
}

/*
 * main logic
 */
int main(void) {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "\x1b[31m[GameKitty] Error initializing SDL:\n%s\n\x1b[0m", SDL_GetError());
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("GameKitty", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH * 2, HEIGHT * 2, SDL_WINDOW_RESIZABLE);

	if (!window) {
		fprintf(stderr, "\x1b[31m[GameKitty] Error creating window:\n%s\n\x1b[0m", SDL_GetError());
		return 1;
    }

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer) {
		fprintf(stderr, "\x1b[31m[GameKitty] Error creating renderer:\n%s\n\x1b[0m", SDL_GetError());
		return 1;
	}

	screen_buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);

	if (!screen_buffer) {
		fprintf(stderr, "\x1b[31m[GameKitty] Error creating screen buffer:\n%s\n\x1b[0m", SDL_GetError());
		return 1;
	}

	spritesheet = IMG_LoadTexture(renderer, "spritesheet.png");

	if (!spritesheet) {
		fprintf(stderr, "\x1b[31m[GameKitty] Could not read spritesheet\n\x1b[0m");
		return 1;
	}

	// verify spritesheet is legal
	{
		int width, height;

		SDL_QueryTexture(spritesheet, NULL, NULL, &width, &height);

		if (width != SPRS_WIDTH * SPR_DIM || height != SPRS_HEIGHT * SPR_DIM) {
			fprintf(stderr, "\x1b[31m[GameKitty] Sprite sheet has incorrect dimensions; expected %dx%d, got %dx%d\n\x1b[0m", SPRS_WIDTH * SPR_DIM, SPRS_HEIGHT * SPR_DIM, width, height);
			return 1;
		}
	}

	// print controls
	printf("\n[GameKitty] Good to go!\n\n");
	printf("D-PAD    : Arrow keys\n");
	printf("Action A : Z\n");
	printf("Action B : X\n");
	printf("Action X : A\n");
	printf("Action Y : S\n");

	// start program
	GK_init();
	emscripten_set_main_loop(main_loop, 0, 1);

	// this code is never reached

	// SDL_DestroyTexture(spritesheet);

	// SDL_DestroyRenderer(renderer);
	// SDL_DestroyWindow(window);
	// SDL_Quit();

	return 0;
}