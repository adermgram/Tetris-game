#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
    Game();
    ~Game();

    void draw();
    void handleInput();
  
    void moveBlockDown();

    bool gameOver = false;
    int score = 0;
    Music music;

private:
    void moveBlockLeft();
    void moveBlockRight();
    Block getRandomBlock();
    std::vector<Block> getAllBlocks();
    bool isBlockOutside();
    void rotateBlock();
    void lockBlock();
    bool blockFits();
    void reset();
    void updateScore(int linesCleared, int moveDownPoints);
    Grid grid;
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    Sound rotateSound;
    Sound clearSound;

};