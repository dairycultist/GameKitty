/*
 * game_kitty.c
 * The implementation of the GameKitty framework.
 * 
 * Copyright 2026 dairycultist
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <emscripten.h>

#include "game_kitty.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

/*
 * rendering
 */
static SDL_Renderer *renderer;
static SDL_Texture *screen_buffer;
static SDL_Texture *font;

static unsigned char clear_r = 0, clear_g = 0, clear_b = 0;

void set_clear_color(unsigned char r, unsigned char g, unsigned char b) {

	clear_r = r;
	clear_g = g;
	clear_b = b;
}

static void draw_char(char c, int x, int y) {

	SDL_Rect copy_rect = { c * CHAR_W, 0, CHAR_W, CHAR_H };
	SDL_Rect paste_rect = { x, y, CHAR_W, CHAR_H };

	SDL_RenderCopyEx(renderer, font, &copy_rect, &paste_rect, 0.0, NULL, SDL_FLIP_NONE);
}

void draw_string(const char *string, int x, int y) {

	int dx = 0;
	int dy = 0;

	// draw
	while (string[0] != '\0') {

		if (string[0] == ' ') {
			dx++;
		} else if (string[0] == '\n') {
			dx = 0;
			dy++;
		} else {
			draw_char(string[0] - 'A', x + CHAR_W * dx, y + (CHAR_H + 2) * dy);
			dx++;
		}

		string++;
	}
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

	font = IMG_LoadTexture(renderer, "GameKitty/font.png");

	if (!font) {
		fprintf(stderr, "\x1b[31m[GameKitty] Could not read font\n\x1b[0m");
		return 1;
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

	// SDL_DestroyTexture(font);

	// SDL_DestroyRenderer(renderer);
	// SDL_DestroyWindow(window);
	// SDL_Quit();

	return 0;
}