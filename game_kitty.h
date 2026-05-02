/*
 * game_kitty.h
 * The header file of the GameKitty framework.
 * 
 * Copyright 2026 dairycultist
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GK_MAIN
#define GK_MAIN

// screen size
#define WIDTH 512
#define HEIGHT 384
#define ASPECT_RATIO (WIDTH / (float) HEIGHT)

// width and height of text characters
#define CHAR_W 16
#define CHAR_H 16

// TODO scene system is a queue; each time a scene is loaded, it pushes all the dialogue, visuals-changes, and finally the dialogue options to the queue
// and we can use pointers to Scenes for transitions, nice

typedef union {

} SceneEvent;

typedef struct {

} Scene;

Scene *get_start_scene();

#endif