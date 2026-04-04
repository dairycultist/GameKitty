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

// helpers
void set_clear_color(unsigned char r, unsigned char g, unsigned char b);
void draw_sprite(int index, int x, int y, int flip);

// implemented by the programmer
void GK_init();
void GK_frame();

#endif