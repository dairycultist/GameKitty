// This file is intentionally left unlicensed under Apache License, Version 2.0.

#include "GameKitty/game_kitty.h"

static int px = (WIDTH) / 2;
static int py = (HEIGHT) / 2;

// TODO scene system is a queue; each time a scene is loaded, it pushes all the dialogue, visuals-changes, and finally the dialogue options to the queue
// Scene struct
// SceneEvent union
// and we can use pointers to Scenes for transitions, nice