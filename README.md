# Tetris Game

This project is a simple implementation of the classic Tetris game using the [raylib](https://www.raylib.com/) library for graphics. The game includes features like score tracking and a game over screen, and uses a custom font for text rendering.

## Features

- Classic Tetris gameplay
- Score tracking
- Next piece preview
- Game over screen
- Custom font rendering

## screenshot
![Screenshot 2024-06-16 201116](https://github.com/adermgram/Tetris-game/assets/123532318/f452c956-16dd-4e3c-89af-f2240ea1ca92)


## Getting Started

### Prerequisites

- C++ compiler (e.g., g++)
- [raylib](https://www.raylib.com/) library

### Building the Project

1. Clone the repository:

   ```sh
   git clone https://github.com/adermgram/Tetris-game.git
   cd tetris-game
   ```
2. Ensure that you have raylib installed on your system. You can install it via your package manager, or download it from the [raylib](https://www.raylib.com/)  website.
3. Compile the project and run the game

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


### Acknowledgement
 - [raylib](https://www.raylib.com/) for providing an easy-to-use C++ game programming library.

Feel free to modify the code and add more features to enhance the gameplay experience. Enjoy playing Tetris!
