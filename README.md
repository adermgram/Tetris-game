# Tetris Game

This project is a simple implementation of the classic Tetris game using the [raylib](https://www.raylib.com/) library for graphics. The game includes features like score tracking and a game over screen, and uses a custom font for text rendering.

## Features

- Classic Tetris gameplay
- Score tracking
- Next piece preview
- Music and sound effects


## screenshot
![Screenshot 2024-06-16 201116](https://github.com/adermgram/Tetris-game/assets/123532318/f452c956-16dd-4e3c-89af-f2240ea1ca92)


## Getting Started

### Prerequisites
- [CMake](https://cmake.org/download/) 3.21 or newer
- A C++ compiler: GCC/Clang on Linux and macOS, MinGW-w64 or MSVC on Windows
- An internet connection on the first build (CMake downloads raylib 5.0)
- Linux only: raylib's usual system packages (e.g. `libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev`)

No editor or IDE is required. Any editor works (VS Code, Vim, Emacs, CLion...).

### Build and run

```bash
git clone https://github.com/adermgram/Tetris-game.git
cd Tetris-game
cmake --preset default            # on Windows with MinGW use: cmake --preset mingw
cmake --build build
cmake --build build --target run  # or run build/tetris directly
```

For a debug build use `--preset debug` (output goes to `build-debug/`).
Fonts and sounds are copied next to the executable, and the game finds them
wherever it is launched from.

## Gameplay

The goal of the game is to fit the falling Tetris blocks together to complete and clear horizontal lines. As the game progresses, the blocks fall faster, increasing the challenge. 

### Controls

- **Left Arrow Key**: Move the block left
- **Right Arrow Key**: Move the block right
- **Down Arrow Key**: Soft drop the block (faster descent)
- **Up Arrow Key**: Rotate the block clockwise

### Scoring

- Each cleared line adds points to your score.
- The more lines you clear at once, the higher the score you will earn. 

## Development Notes

- The game uses the `raylib` library for graphics and audio. It is automatically fetched using CMake's `FetchContent` if not installed.
- Ensure all resources (fonts and sounds) are placed in their respective folders to avoid runtime errors.



### Acknowledgement
 - [raylib](https://www.raylib.com/) for providing an easy-to-use C++ game programming library.

Feel free to modify the code and add more features to enhance the gameplay experience. Enjoy playing Tetris!
