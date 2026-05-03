![GameKitty logo](logo.png)

Visual novel framework written in C that compiles to WASM for lightweight 2D games.

## Installation

1. GameKitty relies on Emscripten, SDL2, and SDL2 Image. These can be installed __on Mac/Linux__ with the following commands:

```
brew install emscripten
brew install sdl2
brew install sdl2_image
```

2. Then, set up the build environment.

```
cd <folder you want to be your build environment>
git clone https://github.com/dairycultist/GameKitty
cd GameKitty
```

3. Finally, build and launch the demo game.

```
sudo make run
```

`gk/` contains all the GameKitty source files. `assets/` contains all the images of your game (they MUST be in this folder, unless you choose to modify the Makefile). `demo.c` is a demo game that demonstrates the functionality of GameKitty — a good place to start!

## Uploading to Itch.io

After building, go into the `build` folder and zip `index.html`, `index.js`, and `index.wasm` together. This zip is what you will upload to Itch.io. Remember to check `This file will be played in the browser` on the uploaded file.

*Optional but recommended:* On the Itch.io edit page, under `Embed options > Viewport dimensions`, set the width/height to 512x384.

## Copyright

GameKitty is licensed under Apache License, Version 2.0. **The only files that fall under this license are** `gk/game_kitty.c` `gk/game_kitty.h` **and** `logo.png`**.** All other files are CC0.
