// This file is intentionally left unlicensed under Apache License, Version 2.0.

#include "GameKitty/game_kitty.h"
#include "stdlib.h"
#include "string.h"

static int px = (WIDTH - SPR_DIM) / 2;
static int py = (HEIGHT - SPR_DIM) / 2;

static SpriteGrid test;

void GK_init() {

	set_clear_color(10, 40, 130);

	test.sprites = malloc(sizeof(sprite_t) * 16);
	test.w = 4;
	test.h = 4;

	for (int i = 0; i < 16; i++) {
		test.sprites[i] = i + 16;
	}
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

	draw_sprite_grid(&test, px, py);
}