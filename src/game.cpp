#include "game.h"
#include <random>
Game::Game()
{
    grid = Grid();
    blocks = getAllBlocks();
    currentBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    gameOver = false;
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("sounds/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("sounds/rotate.mp3");
    clearSound = LoadSound("sounds/clear.mp3");
}
Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();

}

Block Game::getRandomBlock()
{
    if (blocks.empty())
    {
        blocks = getAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);

    return block;
}

std::vector<Block> Game::getAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::draw()
{
    grid.draw();
    currentBlock.draw(11, 11);
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.draw(255, 290);

        break;

    case 4:
        nextBlock.draw(255, 280);

        break;

    default:
        nextBlock.draw(270, 270);
        break;
    }
}

void Game::handleInput()
{
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0)
    {
        gameOver = false;
        reset();
    }
    switch (keyPressed)
    {
    case KEY_LEFT:
        moveBlockLeft();
        break;
    case KEY_RIGHT:
        moveBlockRight();
        break;
    case KEY_DOWN:
        moveBlockDown();
        updateScore(0, 1);
        break;
    case KEY_UP:
        rotateBlock();
        break;
    default:
        break;
    }
}

void Game::moveBlockLeft()
{
    if (!gameOver)
    {
        currentBlock.move(0, -1);
        if (isBlockOutside() || !blockFits())
        {
            currentBlock.move(0, 1);
        }
    }
}

void Game::moveBlockDown()
{
    if (!gameOver)
    {
        currentBlock.move(1, 0);
        if (isBlockOutside() || !blockFits())
        {
            currentBlock.move(-1, 0);
            lockBlock();
        }
    }
}

bool Game::isBlockOutside()
{
    std::vector<Position> tiles = currentBlock.getCellPositions();
    for (Position item : tiles)
    {
        if (grid.isCellOutside(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::moveBlockRight()
{
    if (!gameOver)
    {
        currentBlock.move(0, 1);
        if (isBlockOutside() || !blockFits())
        {

            currentBlock.move(0, -1);
        }
    }
}

void Game::rotateBlock()
{
    if (!gameOver)
    {
        currentBlock.rotate();
        if (isBlockOutside() || !blockFits())
        {
            currentBlock.undoRotation();
        }
        else
        {
            PlaySound(rotateSound);
        }
    }
}

void Game::lockBlock()
{
    std::vector<Position> tiles = currentBlock.getCellPositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if (!blockFits())
    {
        gameOver = true;
    }
    nextBlock = getRandomBlock();
    int rowsCleared = grid.clearFullRows();
    if(rowsCleared > 0)
    {
        PlaySound(clearSound);
        updateScore(rowsCleared, 0);
    }
    
}

bool Game::blockFits()
{
    std::vector<Position> tiles = currentBlock.getCellPositions();
    for (Position item : tiles)
    {
        if (!grid.isCellEmpty(item.row, item.column))
        {
            return false;
        }
    }

    return true;
}

void Game::reset()
{
    grid.initialize();
    blocks = getAllBlocks();
    currentBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    score = 0;
}

void Game::updateScore(int linesCleared, int moveDownPoints)
{
    switch (linesCleared)
    {
    case 1:
        score += 100;
        break;

    case 2:
        score += 300;
        break;

    case 3:
        score += 500;
        break;

    default:
        break;
    }
    score += moveDownPoints;
}
