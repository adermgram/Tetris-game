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
- CMake (minimum version 3.17)
- C++ compiler (e.g., g++)

## Setup Instructions
1. Clone the repository:
   ```bash
   git clone https://github.com/adermgram/Tetris-game.git
   cd Tetris-game
   
2. Ensure you have CMake installed and accessible in your environment.

### Building the Project

3. Build the project:
  ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. Compile the project and run the game

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

- The game uses the `raylib` library for graphics and audio. It is automatically fetched using CMake's `FetchContent`.
- Ensure all resources (fonts and sounds) are placed in their respective folders to avoid runtime errors.



### Acknowledgement
 - [raylib](https://www.raylib.com/) for providing an easy-to-use C++ game programming library.

Feel free to modify the code and add more features to enhance the gameplay experience. Enjoy playing Tetris!
