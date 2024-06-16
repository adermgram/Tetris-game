#include "block.h"

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = getCellColors();
    rowOffset = 0;
    columnOffset = 0;
}

void Block::draw(int offsetX, int offsetY)
{
    std::vector<Position> tiles = getCellPositions();
    for (Position item : tiles)
    {
        DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::move(int rows, int columns)
{
    rowOffset += rows;
    columnOffset += columns;
}


std::vector<Position> Block::getCellPositions()
{
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;
    for(Position item: tiles) 
    {
        Position newPos = Position(item.row + rowOffset, item.column+columnOffset);
        movedTiles.push_back(newPos);
    }

    return movedTiles;
}

void Block::rotate()
{
    rotationState ++;
    if(rotationState == (int)cells.size())
    {
        rotationState = 0;
    }
}

void Block::undoRotation()
{
    rotationState --;
    if(rotationState == -1)
    {
        rotationState = cells.size() - 1;
    }
}
