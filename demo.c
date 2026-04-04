#include "game_kitty.h"

static int px = (WIDTH - SPR_DIM) / 2;
static int py = (HEIGHT - SPR_DIM) / 2;

void GK_init() {

	set_clear_color(10, 40, 130);
}

void GK_frame(const Input *input) {

	if (input->up)
		py--;

	if (input->down)
		py++;

	if (input->left)
		px--;

	if (input->right)
		px++;

	draw_sprite(0, px, py, 0);
}