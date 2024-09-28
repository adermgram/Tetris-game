#pragma once
#include<vector>
#include <raylib.h>

class Grid
{
public:
    Grid();
    
    void initialize();
    void print();
    void draw() const;
    bool isCellOutside(unsigned int row, unsigned int column) const;
    bool isCellEmpty(unsigned int row, unsigned int column) const;
    unsigned int clearFullRows();

    unsigned int& grid(unsigned int row, unsigned int column)
    {
        return _grid[row][column];
    }
    
private:
    bool isRowFull(unsigned int row) const;
    void clearRow(unsigned int row);
    void moveRowDown(unsigned int row, unsigned int numRows);

private:
    int numRows = 20;
    int numCols = 10;
    int cellSize = 30;

    unsigned int _grid[20][10];

};
