#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// screen size
#define WIDTH 256
#define HEIGHT 192
#define ASPECT_RATIO (WIDTH / (float) HEIGHT)

// width and height of sprites
#define SPR_DIM 16

// sprite sheet dimensions in sprites
#define SPRS_WIDTH 8
#define SPRS_HEIGHT 8

////////////////////////////////////////////////////////////////////////

static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Texture *screen_buffer;

static unsigned char clear_r, clear_g, clear_b;

static unsigned long runtime = 0; // wraps to 0 at around 4.5 years

static SDL_Texture *spritesheet;

/*
 * rendering
 */
static void set_clear_color(unsigned char r, unsigned char g, unsigned char b) {
	
	clear_r = r;
	clear_g = g;
	clear_b = b;
}

static void draw_sprite(int index, int x, int y, int flip) {

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
 * main logic
 */
int main(int argc, char **argv) {

	if (argc != 3) {
		printf("Format: %s path/to/code.txt path/to/spritesheet.png\n", argv[0]);
		return 1;
	}

	printf("Starting Berry2D\n");

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("Error initializing SDL:\n%s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow("Berry2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH * 2, HEIGHT * 2, SDL_WINDOW_RESIZABLE);

	if (!window) {
		printf("Error creating window:\n%s\n", SDL_GetError());
		return 1;
    }

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer) {
		printf("Error creating renderer:\n%s\n", SDL_GetError());
		return 1;
	}

	screen_buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT);

	if (!screen_buffer) {
		printf("Error creating screen buffer:\n%s\n", SDL_GetError());
		return 1;
	}

	spritesheet = IMG_LoadTexture(renderer, argv[2]);

	if (!spritesheet) {
		printf("Could not read spritesheet\n");
		return 1;
	}

	set_clear_color(0, 0, 0);

	// verify spritesheet is legal
	{
		int width, height;

		SDL_QueryTexture(spritesheet, NULL, NULL, &width, &height);

		if (width != SPRS_WIDTH * SPR_DIM || height != SPRS_HEIGHT * SPR_DIM) {
			printf("Sprite sheet has incorrect dimensions; expected %dx%d, got %dx%d\n", SPRS_WIDTH * SPR_DIM, SPRS_HEIGHT * SPR_DIM, width, height);
			return 1;
		}
	}

	// print controls
	printf("D-PAD: Arrow keys\n");
	printf("Action A: Z\n");
	printf("Action B: X\n");
	printf("Action X: A\n");
	printf("Action Y: S\n");

	// process events until window is closed
	SDL_Event event;
	SDL_Rect letterbox = { 0, 0, WIDTH * 2, HEIGHT * 2 };

	char running = 1;

	int up, 		up_justchanged;
	int down, 		down_justchanged;
	int left, 		left_justchanged;
	int right, 		right_justchanged;
	int action_a, 	action_a_justchanged;
	int action_b, 	action_b_justchanged;
	int action_x, 	action_x_justchanged;
	int action_y, 	action_y_justchanged;

	while (running) {

		up_justchanged       = 0;
		down_justchanged     = 0;
		left_justchanged     = 0;
		right_justchanged    = 0;
		action_a_justchanged = 0;
		action_b_justchanged = 0;
		action_x_justchanged = 0;
		action_y_justchanged = 0;

		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {

				running = 0;

			} else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {

				#define MIN(a, b) ((a) > (b) ? (b) : (a))

				// dynamically change letterbox based on screen resize
				letterbox.w = MIN(event.window.data1, event.window.data2 * ASPECT_RATIO);
				letterbox.h = MIN(event.window.data2, event.window.data1 / ASPECT_RATIO);

				letterbox.x = (event.window.data1 - letterbox.w) / 2;
				letterbox.y = (event.window.data2 - letterbox.h) / 2;

			} else if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && !event.key.repeat) {

				switch (event.key.keysym.scancode) {
					case SDL_SCANCODE_UP:
						up = event.key.state == SDL_PRESSED;
						up_justchanged = 1;
						break;
					case SDL_SCANCODE_DOWN:
						down = event.key.state == SDL_PRESSED;
						down_justchanged = 1;
						break;
					case SDL_SCANCODE_LEFT:
						left = event.key.state == SDL_PRESSED;
						left_justchanged = 1;
						break;
					case SDL_SCANCODE_RIGHT:
						right = event.key.state == SDL_PRESSED;
						right_justchanged = 1;
						break;
					case SDL_SCANCODE_Z:
						action_a = event.key.state == SDL_PRESSED;
						action_a_justchanged = 1;
						break;
					case SDL_SCANCODE_X:
						action_b = event.key.state == SDL_PRESSED;
						action_b_justchanged = 1;
						break;
					case SDL_SCANCODE_A:
						action_x = event.key.state == SDL_PRESSED;
						action_x_justchanged = 1;
						break;
					case SDL_SCANCODE_S:
						action_y = event.key.state == SDL_PRESSED;
						action_y_justchanged = 1;
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

		// process/draw
		draw_sprite(
			0,
			(int) (cos(runtime * 0.05) * 20) + 20,
			(int) (sin(runtime * 0.05) * 20) + 20,
			0
		);

		runtime++;

		SDL_SetRenderTarget(renderer, NULL); 								// reset render target back to window
		SDL_RenderCopy(renderer, screen_buffer, NULL, &letterbox); 			// render screen_buffer
		SDL_RenderPresent(renderer); 										// present rendered content to screen

		SDL_Delay(1000 / 60);
	}

	SDL_DestroyTexture(spritesheet);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}