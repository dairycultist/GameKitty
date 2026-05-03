// This file is intentionally left unlicensed under Apache License, Version 2.0.

#include "GameKitty/game_kitty.h"

static Event test_scene[] = {
	{
		TYPE_TEXT, "HELLO"
	},
	{
		TYPE_TEXT, "DOES THIS WORK"
	},
	{
		TYPE_TEXT, "I HOPE SO"
	},
};

Event *get_start_events() {
	return test_scene;
}