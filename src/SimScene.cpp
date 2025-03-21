#include "Scene.hpp"
#include "raygui.h"
#include "main.hpp"
#include <iostream>

// Constructeur de la scène de la Simulation
SimScene::SimScene(Game &game, int gridWidth, int gridHeight)
 : Scene(game), _grid(gridWidth, gridHeight), _panel(10, 10, _evolutionSpeed)
{
    _camera.target = {0, 0};
    _camera.offset = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
    _camera.rotation = 0.0f;
    _camera.zoom = 1.0f;

    _evolutionSpeed = 0.5f;
    _lastUpdateTime = GetTime();
}

// Initialisation de la scène
void SimScene::init()
{ }

// Gestion des inputs
void SimScene::handleInputs()
{
    // Gestion du zoom avec la molette
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        _camera.zoom += wheel * 0.1f;
        if (_camera.zoom < 0.1f) _camera.zoom = 0.1f;
        if (_camera.zoom > 3.0f) _camera.zoom = 3.0f;
        
        if (_camera.zoom < 0.5f) {
            _grid.setLinesVisible(false);
        } else {
            _grid.setLinesVisible(true);
        }
    }

    // Mouvements de la caméra
    if (IsKeyDown(KEY_W)) _camera.target.y -= 10 / _camera.zoom;
    if (IsKeyDown(KEY_S)) _camera.target.y += 10 / _camera.zoom;
    if (IsKeyDown(KEY_A)) _camera.target.x -= 10 / _camera.zoom;
    if (IsKeyDown(KEY_D)) _camera.target.x += 10 / _camera.zoom;

    // Déplacements avec clique droit
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        Vector2 delta = GetMouseDelta();
        _camera.target.x -= delta.x / _camera.zoom;
        _camera.target.y -= delta.y / _camera.zoom;
    }

    // Inverser l'état d'une cellule avec le clique gauche si editMode = true
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && _panel.isEditMode() && !_panel.isMouseOver()) {
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), _camera);
        Vector2 cellPos = _grid.worldToCellPos(mouseWorldPos);
        if (_grid.isCellInGrid(cellPos.x, cellPos.y)) {
            _grid.toggleCell(static_cast<int>(cellPos.x), static_cast<int>(cellPos.y));
        }
    }

    // Vider la grille si boutton cliqué sur le panel
    if (_panel.isClearGridPressed()) {
        _grid.clearGrid();
    }

    // Générer de la soupe si boutton cliqué sur le panel
    if (_panel.isGenerateSoupPressed()) {
        _grid.generateSoup();
    }
}

// Update de la scène
void SimScene::update()
{
    _panel.update();
    handleInputs();

    // Générer la nouvelle génération
    if (_panel.isPaused() && _panel.isNextGenerationPressed()) {
        _lastUpdateTime = GetTime();
        _grid.nextGeneration();
    }

    // Défillement auto des générations si pause = false
    if (!_panel.isPaused() && GetTime() - _lastUpdateTime >= _evolutionSpeed) {
        _grid.nextGeneration();
        _lastUpdateTime = GetTime();
    }
}

// Affichage de la scène
void SimScene::draw()
{
    ClearBackground(LIGHTGRAY);

    BeginMode2D(_camera);
        _grid.draw();
    EndMode2D();

    _panel.draw();
}