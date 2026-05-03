// This file is intentionally left unlicensed under Apache License, Version 2.0.

#include "gk/game_kitty.h"

static Event test_scene[] = {
	{
		TYPE_TEXT, "HELLO"
	},
	{
		TYPE_SET_BACKGROUND, "assets/forest.png"
	},
	{
		TYPE_TEXT, "NOW WERE IN A FOREST"
	},
	{
		TYPE_TEXT_UNPASSABLE, "THERES NO MORE TEXT"
	},
};

Event *get_start_events() {
	return test_scene;
}