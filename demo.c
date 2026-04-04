#include "game_kitty.h"

void GK_init() {

	set_clear_color(10, 40, 130);
}

void GK_frame(const Input *input) {

	if (!input->up)
		draw_sprite(0, 40, 40, 0);
}