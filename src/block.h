#pragma once

#include<vector>
#include<map>
#include "position.h"
#include "colors.h"

class Block
{
public:
    Block();
    void draw(int offsetX, int offsetY) const;
    void move(int rows, int columns);

    using PositionVector = std::vector<Position>;

    PositionVector getCellPositions() const;
    void rotate();
    void undoRotation();

    unsigned int getId() const {return id;}
    
protected:
    int id;
    std::map<int, PositionVector> cells;

private:
    int cellSize;
    int rotationState;
    int rowOffset;
    int columnOffset;
};
