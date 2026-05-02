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

typedef struct {

	int mouse_x, mouse_y, mouse_down;

} Input;

// built-ins
void set_clear_color(unsigned char r, unsigned char g, unsigned char b);
void draw_string(const char *string, int x, int y);

#endif