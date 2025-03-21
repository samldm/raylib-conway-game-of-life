#include "Grid.hpp"
#include <random>

// Constructeur de la grille
Grid::Grid(int width, int height, float cellSize) : _width(width), _height(height), _cellSize(cellSize)
{
    _cells = std::vector<std::vector<bool>>(_height, std::vector<bool>(_width, false));
}

// Basculer l'état d'une cellule
void Grid::toggleCell(int x, int y) {
    if (x >= 0 && x < _width && y >= 0 && y < _height) {
        _cells[y][x] = !_cells[y][x];
    }
}

// Générer la prochaine génération de cellules
void Grid::nextGeneration()
{
    _cellsCopy = _cells;
    
    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            int alive = countAliveNeighbors(x, y);
            if(_cells[y][x] == true) { // Si la cellule est en vie
                _cellsCopy[y][x] = (alive == 2 || alive == 3); // Elle reste en vie si elle a 2 ou 3 voisine en vie
            } else { // Si la cellule est morte
                _cellsCopy[y][x] = (alive == 3); // Elle prend vie si elle a trois voisine en simple
            }
        }
    }

    _cells = _cellsCopy;
}

// Récupérer le nombre de cellules en vie voisine
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

// Renvoie true si la position donnée est dans la grille
bool Grid::isCellInGrid(int x, int y)
{
    return (x >= 0 && x < _width && y >= 0 && y < _height);
}

// Récupérer la position d'une cellule depuis une position du monde 2D
Vector2 Grid::worldToCellPos(Vector2 worldPos) {
    float startX = -(_width * _cellSize) / 2.0f;
    float startY = -(_height * _cellSize) / 2.0f;

    int cellX = static_cast<int>((worldPos.x - startX) / _cellSize);
    int cellY = static_cast<int>((worldPos.y - startY) / _cellSize);

    return { static_cast<float>(cellX), static_cast<float>(cellY) };
}

// Affichage de la grille et des cellules
void Grid::draw()
{
    // Origine de la grille pour qu'elle soit centrée sur le X/Y 0 0
    float startX = -(_width * _cellSize) / 2.0f;
    float startY = -(_height * _cellSize) / 2.0f;

    // Affichage des cellules
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            float posX = startX + x * _cellSize;
            float posY = startY + y * _cellSize;

            Color cellColor = _cells[y][x] ? BLACK : WHITE;

            DrawRectangle(posX, posY, _cellSize, _cellSize, cellColor);
        }
    }

    // Affichage des lignes si elle doivent etre visibles
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

// Changer la visibilité des lignes
void Grid::setLinesVisible(bool areVsible)
{
    _linesVisible = areVsible;
}

// Vider la grille
void Grid::clearGrid()
{
    _cells = std::vector<std::vector<bool>>(_height, std::vector<bool>(_width, false));
}

// Générer de la soupe
void Grid::generateSoup()
{
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            _cells[y][x] = rand() % 2 == 1;
        }
    }
}