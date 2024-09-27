#include "grid.h"
#include <iostream>
#include "colors.h"

Grid::Grid() : numRows(20), numCols(10), cellSize(30)
{
    initialize();
}

void Grid::initialize()
{
    for (unsigned int row = 0; row < numRows; ++row)
    {
        for (unsigned int col = 0; col < numCols; ++col)
        {
            _grid[row][col] = 0;
        }
    }
}

void Grid::print()
{
    for (unsigned int row = 0; row < numRows; ++row)
    {
        for (unsigned int col = 0; col < numCols; ++col)
        {
            std::cout << _grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::draw() const
{
    const auto& colors(getCellColors());
    for (unsigned int row = 0; row < numRows; ++row)
    {
        for (unsigned int col = 0; col < numCols; ++col)
        {
            int cellValue = _grid[row][col];
            DrawRectangle(col * cellSize + 11, row * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}

bool Grid::isCellOutside(unsigned int row, unsigned int column) const
{
    return !(row >= 0 && row < numRows && column >= 0 && column < numCols);
}

bool Grid::isCellEmpty(unsigned int row, unsigned int column) const
{
    return (0 == _grid[row][column ]);
}

unsigned int Grid::clearFullRows()
{
    unsigned int completed = 0;
    for(int row = numRows-1; row>=0; --row)
    {
        if(isRowFull(row))
        {
            clearRow(row);
            completed++;
        }
        else if(completed > 0)
        {
            moveRowDown(row, completed);
        }
    }
    return completed;
}

bool Grid::isRowFull(unsigned int row) const
{
    bool isFull = true;
    for(unsigned int column = 0; column < numCols ; ++column)
    {
        if(_grid[row][column] == 0)
        {
            isFull = false;
            break;
        }
    }
    return isFull;
}

void Grid::clearRow(unsigned int row)
{
    for(unsigned int column = 0; column < numCols ; ++column)
    {
        _grid[row][column] = 0;
    }
}

void Grid::moveRowDown(unsigned int row, unsigned int numRows)
{
    for(unsigned int column = 0; column < numCols; ++column)
    {
        _grid[row + numRows][column] = _grid[row][column];
        _grid[row][column] = 0;
    }

}
