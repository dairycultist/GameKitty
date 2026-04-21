// This file is intentionally left unlicensed under Apache License, Version 2.0.

#include "GameKitty/game_kitty.h"
#include "stdlib.h"
#include "string.h"

static int px = (WIDTH - SPR_DIM) / 2;
static int py = (HEIGHT - SPR_DIM) / 2;

static SpriteGrid test;

void GK_init() {

	set_clear_color(10, 40, 130);

	test.sprites = malloc(sizeof(sprite_t) * 4);
	test.sprites[0] = 16;
	test.sprites[1] = 17;
	test.sprites[2] = 18;
	test.sprites[3] = 19;
	test.w = 2;
	test.h = 2;
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

	draw_sprite_grid(&test, 10, 10);
}