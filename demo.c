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
		TYPE_SET_PERSON_LEFT, "assets/person.png"
	},
	{
		TYPE_TEXT, "HERES A GUY"
	},
	{
		TYPE_SET_PERSON_RIGHT, "assets/person_angry.png"
	},
	{
		TYPE_TEXT, "HERES ANOTHER ONE BUT ANGRY"
	},
	{
		TYPE_SET_PERSON_LEFT, "assets/person_angry.png"
	},
	{
		TYPE_TEXT, "NOW THEYRE BOTH ANGRY"
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
		TYPE_TEXT_UNPASSABLE, "THERES NO MORE TEXT"
	}
};

Event *get_start_events() {
	return test_scene;
}