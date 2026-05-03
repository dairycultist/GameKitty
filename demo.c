// This file is intentionally left unlicensed under Apache License, Version 2.0.

#include "gk/game_kitty.h"

static Event test_scene[] = {
	{
		TYPE_TEXT, "HELLO"
	},
	{
		TYPE_TEXT, "DOES THIS WORK"
	},
	{
		TYPE_TEXT_UNPASSABLE, "YOU CANT PASS ME"
	},
};

Event *get_start_events() {
	return test_scene;
}