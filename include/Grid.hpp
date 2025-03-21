#ifndef GRID_HPP
#define GRID_HPP

#include "raylib.h"
#include <vector>

class Grid
{
public:
    Grid(int width, int height, float _cellSize = 20.0f);

    void toggleCell(int x, int y);
    void nextGeneration();
    int countAliveNeighbors(int x, int y);
    bool isCellInGrid(int x, int y);
    void setLinesVisible(bool areVisible = true);
    Vector2 worldToCellPos(Vector2 worldPos);
    
    void clearGrid();
    void generateSoup();

    void draw();
    
    int getWidth() const { return _width; }
    int getHeight() const { return _height; }
private:
    int _width;
    int _height;
    float _cellSize;
    bool _linesVisible = true;

    std::vector<std::vector<bool>> _cells;
    std::vector<std::vector<bool>> _cellsCopy;
};

#endif