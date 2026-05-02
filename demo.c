// This file is intentionally left unlicensed under Apache License, Version 2.0.

#include "GameKitty/game_kitty.h"
#include "stdlib.h"
#include "string.h"

static int px = (WIDTH) / 2;
static int py = (HEIGHT) / 2;

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

	draw_string("APPLES\nAND PEARS", px, py);
}