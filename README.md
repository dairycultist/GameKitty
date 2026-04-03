# GameKitty

Game framework in C that compiles to WASM for lightweight 2D games.

## Installation

1. GameKitty relies on Emscripten, SDL2, and SDL2 Image. These can be installed __on Mac/Linux__ with the following commands:

```
brew install emscripten
brew install sdl2
brew install sdl2_image
```

2. Then, set up the build environment.

```
git clone https://github.com/dairycultist/GameKitty
cd GameKitty
```

3. Finally, build and launch the demo game.

```
sudo make run
```