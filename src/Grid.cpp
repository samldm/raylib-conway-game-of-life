#include "Grid.hpp"
#include <random>

// Grid constructor
Grid::Grid(int width, int height, float cellSize) : _width(width), _height(height), _cellSize(cellSize)
{
    _cells = std::vector<std::vector<bool>>(_height, std::vector<bool>(_width, false));
}

// Toggle cell state
void Grid::toggleCell(int x, int y) {
    if (x >= 0 && x < _width && y >= 0 && y < _height) {
        _cells[y][x] = !_cells[y][x];
    }
}

// Get the next generation
void Grid::nextGeneration()
{
    _cellsCopy = _cells;
    
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            int alive = countAliveNeighbors(x, y);
            if(_cells[y][x] == true) {
                _cellsCopy[y][x] = (alive == 2 || alive == 3);
            } else {
                _cellsCopy[y][x] = (alive == 3);
            }
        }
    }

    _cells = _cellsCopy;
}

// Returns the number of alive neighbors of a cell
int Grid::countAliveNeighbors(int x, int y)
{
    int count = 0;

    int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (isCellInGrid(nx, ny) && _cells[ny][nx])
            count++;
    }
    return count;
}

// Returns true if a cell is in the grid
bool Grid::isCellInGrid(int x, int y)
{
    return (x >= 0 && x < _width && y >= 0 && y < _height);
}

// Get a cell position from a world 2D position
Vector2 Grid::worldToCellPos(Vector2 worldPos) {
    float startX = -(_width * _cellSize) / 2.0f;
    float startY = -(_height * _cellSize) / 2.0f;

    int cellX = static_cast<int>((worldPos.x - startX) / _cellSize);
    int cellY = static_cast<int>((worldPos.y - startY) / _cellSize);

    return { static_cast<float>(cellX), static_cast<float>(cellY) };
}

// Display of the grid and the cells
void Grid::draw()
{
    // Grid's origin (middle of the screen)
    float startX = -(_width * _cellSize) / 2.0f;
    float startY = -(_height * _cellSize) / 2.0f;

    // Display of cells
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            float posX = startX + x * _cellSize;
            float posY = startY + y * _cellSize;

            Color cellColor = _cells[y][x] ? BLACK : WHITE;

            DrawRectangle(posX, posY, _cellSize, _cellSize, cellColor);
        }
    }

    // Display of lines if visible
    if (_linesVisible) {
        for (int i = 0; i <= _width; ++i) {
            float x = startX + i * _cellSize;
            DrawLine(x, startY, x, startY + _height * _cellSize, BLACK);
        }
        for (int i = 0; i <= _height; ++i) {
            float y = startY + i * _cellSize;
            DrawLine(startX, y, startX + _width * _cellSize, y, BLACK);
        }
    }
}

// Change line visibility
void Grid::setLinesVisible(bool areVsible)
{
    _linesVisible = areVsible;
}

// Clear the grid
void Grid::clearGrid()
{
    _cells = std::vector<std::vector<bool>>(_height, std::vector<bool>(_width, false));
}

// Generate random soup on the grid
void Grid::generateSoup()
{
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            _cells[y][x] = rand() % 2 == 1;
        }
    }
}