// This file is intentionally left unlicensed under Apache License, Version 2.0.

#include "gk/game_kitty.h"

static Event test_scene[] = {
	{
		TYPE_TEXT, "HELLO!"
	},
	{
		TYPE_SET_BACKGROUND, "assets/forest.png"
	},
	{
		TYPE_TEXT, "NOW WE'RE IN A FOREST."
	},
	{
		TYPE_SET_PERSON_LEFT, "assets/person.png"
	},
	{
		TYPE_TEXT, "HERE'S A GUY."
	},
	{
		TYPE_SET_PERSON_RIGHT, "assets/person_angry.png"
	},
	{
		TYPE_TEXT, "HERE'S ANOTHER ONE, BUT ANGRY."
	},
	{
		TYPE_SET_PERSON_LEFT, "assets/person_angry.png"
	},
	{
		TYPE_TEXT, "NOW THEY'RE BOTH ANGRY."
	},
	{
		TYPE_TEXT, "LEFT: IM SO ANGRY OMG!!"
	},
	{
		TYPE_TEXT, "RIGHT: SAME LMFAO!! THAT'S SO\nCRAZY??"
	},
	{
		TYPE_SET_BACKGROUND, 0
	},
	{
		TYPE_SET_PERSON_LEFT, 0
	},
	{
		TYPE_SET_PERSON_RIGHT, 0
	},
	{
		TYPE_TEXT_UNPASSABLE, "THE END...?"
	}
};

Event *get_start_events() {
	return test_scene;
}