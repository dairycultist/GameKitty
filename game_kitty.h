#ifndef GK_MAIN
#define GK_MAIN

// screen size
#define WIDTH 240
#define HEIGHT 160
#define ASPECT_RATIO (WIDTH / (float) HEIGHT)

// width and height of sprites
#define SPR_DIM 16

// sprite sheet dimensions in sprites
#define SPRS_WIDTH 16
#define SPRS_HEIGHT 16

typedef unsigned char sprite_t;

typedef struct {

	sprite_t *sprites;
	int w;
	int h;

} SpriteGrid; // good for multisprites and maps

typedef struct {

	int up, 		up_justchanged;
	int down, 		down_justchanged;
	int left, 		left_justchanged;
	int right, 		right_justchanged;
	int action_a, 	action_a_justchanged;
	int action_b, 	action_b_justchanged;
	int action_x, 	action_x_justchanged;
	int action_y, 	action_y_justchanged;

} Input;

// built-ins
void set_clear_color(unsigned char r, unsigned char g, unsigned char b);
void draw_sprite(sprite_t sprite, int x, int y, int flip);
void draw_sprite_grid(SpriteGrid *sprite_grid, int x, int y);

// implemented by the programmer
void GK_init();
void GK_frame(const Input *input);

#endif