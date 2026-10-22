#include "game.h"
#include <ctime>
#include <random>
#include <cassert>

Game::Game()
: grid()
, currentBlock(getRandomBlock())
, nextBlock(getRandomBlock())
, rotateSound()
, clearSound()
{}

Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
}

bool Game::init(const std::string& build_path)
{
    bool success = false;
    InitAudioDevice();
    music = LoadMusicStream((build_path + "sounds/music.mp3").c_str());
    assert(music.ctxData);
    if (music.ctxData)
    {
        PlayMusicStream(music);
        rotateSound = LoadSound((build_path + "sounds/rotate.mp3").c_str());
        assert(rotateSound.frameCount > 0 );
        if (rotateSound.frameCount > 0)
        {
            clearSound = LoadSound((build_path + "sounds/clear.mp3").c_str());
            assert(clearSound.frameCount > 0 );
            if (clearSound.frameCount > 0)
            {
                success = true;
            }
            else
            {
                UnloadSound(rotateSound);
                UnloadMusicStream(music);
            }
        }
        else
        {
            UnloadMusicStream(music);
        }
    }
    return success;
}

const Block& Game::getRandomBlock() const
{
    const std::vector<Block>& blocks(getAllBlocks());
    const int randomIndex (rand() % blocks.size());
    return blocks[randomIndex];
}

const std::vector<Block>& Game::getAllBlocks() const
{
    static std::vector<Block> sAllBlocks{IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
    return sAllBlocks;
}

void Game::draw() const
{
    grid.draw();
    getGhostBlock().drawGhost(11, 11);
    currentBlock.draw(11, 11);
    switch (nextBlock.getId())
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
    if (keyPressed == KEY_P && !gameOver)
    {
        togglePause();
        return;
    }
    if (paused)
    {
        return;
    }
    if (gameOver && keyPressed != 0)
    {
        gameOver = false;
        reset();
        return;
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
    case KEY_SPACE:
        hardDrop();
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

bool Game::isBlockOutside() const
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
        grid.grid(item.row, item.column) = currentBlock.getId();
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
        totalLines += rowsCleared;
        level = 1 + totalLines / 10;
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
    currentBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    score = 0;
    totalLines = 0;
    level = 1;
    paused = false;
    gameOver = false;
}

void Game::updateScore(unsigned int linesCleared, unsigned int moveDownPoints)
{
    switch (linesCleared)
    {
    case 1:
        score += 100 * level;
        break;

    case 2:
        score += 300 * level;
        break;

    case 3:
        score += 500 * level;
        break;

    case 4:
        score += 800 * level;
        break;

    default:
        break;
    }
    score += moveDownPoints;
}

bool Game::fits(const Block& block) const
{
    for (const Position& item : block.getCellPositions())
    {
        if (grid.isCellOutside(item.row, item.column) || !grid.isCellEmpty(item.row, item.column))
        {
            return false;
        }
    }
    return true;
}

Block Game::getGhostBlock() const
{
    Block ghost(currentBlock);
    while (true)
    {
        ghost.move(1, 0);
        if (!fits(ghost))
        {
            ghost.move(-1, 0);
            return ghost;
        }
    }
}

void Game::hardDrop()
{
    if (!gameOver)
    {
        const int before = currentBlock.getCellPositions().front().row;
        currentBlock = getGhostBlock();
        const int rowsDropped = currentBlock.getCellPositions().front().row - before;
        lockBlock();
        updateScore(0, rowsDropped * 2);
    }
}

void Game::togglePause()
{
    paused = !paused;
    if (paused)
    {
        PauseMusicStream(music);
    }
    else
    {
        ResumeMusicStream(music);
    }
}

float Game::getFallInterval() const
{
    // 0.2s at level 1, 15% faster each level, never faster than 0.05s.
    float interval = 0.2f;
    for (int i = 1; i < level && interval > 0.05f; ++i)
    {
        interval *= 0.85f;
    }
    return interval > 0.05f ? interval : 0.05f;
}

