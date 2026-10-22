#pragma once
#include "grid.h"
#include "blocks.cpp"
#include <string>

class Game
{
public:
    Game();
    ~Game();

    // This class is not ought to be copied or assigned!
    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator= (const Game&) = delete;
    Game& operator= (Game&&) = delete;

    bool init(const std::string& build_path);
     void reset();

    void draw() const;
    void handleInput();

    void moveBlockDown();
    void togglePause();
    float getFallInterval() const;
    void hardDrop();

    bool gameOver = false;
    int score = 0;
    int level = 1;
    bool paused = false;
    Music music;

private: // methods
    void moveBlockLeft();
    void moveBlockRight();
    const Block& getRandomBlock() const;
    const std::vector<Block>& getAllBlocks() const;
    bool isBlockOutside() const;
    void rotateBlock();
    void lockBlock();
    bool blockFits();
    bool fits(const Block& block) const;
    Block getGhostBlock() const;
    void updateScore(unsigned int linesCleared, unsigned int moveDownPoints);

private: // members
    Grid grid;
    Block currentBlock;
    Block nextBlock;
    Sound rotateSound;
    Sound clearSound;
    int totalLines = 0;

};
