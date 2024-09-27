#include "block.h"

Block::Block()
: id(0)
, cells()
, cellSize(30)
, rotationState(0)
, rowOffset(0)
, columnOffset(0)
{}

void Block::draw(int offsetX, int offsetY) const
{
    const auto& colors(getCellColors());
    
    const std::vector<Position> tiles = getCellPositions();
    for (const Position& item : tiles)
    {
        DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::move(int rows, int columns)
{
    rowOffset += rows;
    columnOffset += columns;
}


std::vector<Position> Block::getCellPositions() const
{
    std::vector<Position> movedTiles;

    const auto cellIt = cells.find(rotationState);
    if (cellIt != cells.end())
    {
        const std::vector<Position>& tiles(cellIt->second);
        for(const Position& item: tiles)
        {
            Position newPos = Position(item.row + rowOffset, item.column+columnOffset);
            movedTiles.push_back(newPos);
        }
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
