#ifndef GRID_HPP
#define GRID_HPP

#include "raylib.h"
#include <vector>

// Grid class that contains cells. Contains the logic of the simulation.
class Grid
{
public:
    Grid(int width, int height, float _cellSize = 20.0f);
    
    // Toggle cell state
    void toggleCell(int x, int y);

    // Get the next generation
    void nextGeneration();

    // Returns the number of alive neighbors of a cell
    int countAliveNeighbors(int x, int y);

    // Returns true if a cell is in the grid
    bool isCellInGrid(int x, int y);

    // Get a cell position from a world 2D position
    Vector2 worldToCellPos(Vector2 worldPos);

    // Display of the grid and the cells
    void draw();
    
    // Change line visibility
    void setLinesVisible(bool areVisible = true);
    
    // Clear the grid
    void clearGrid();

    // Generate random soup on the grid
    void generateSoup();

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