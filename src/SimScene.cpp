#include "Scene.hpp"
#include "raygui.h"
#include "main.hpp"
#include <iostream>

// Simulation scene constructor
SimScene::SimScene(Game &game, int gridWidth, int gridHeight)
 : Scene(game), _grid(gridWidth, gridHeight), _panel(10, 10, _evolutionSpeed)
{ }

// Scene init
void SimScene::init()
{
    _camera.target = {0, 0};
    _camera.offset = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
    _camera.rotation = 0.0f;
    _camera.zoom = 1.0f;

    _evolutionSpeed = 0.5f;
    _lastUpdateTime = GetTime();
}

// User input handling
void SimScene::handleInputs()
{
    // Zoom handling
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        _camera.zoom += wheel * 0.1f;
        if (_camera.zoom < 0.1f) _camera.zoom = 0.1f;
        if (_camera.zoom > 3.0f) _camera.zoom = 3.0f;
    }

    // Camera movements
    if (IsKeyDown(KEY_W)) _camera.target.y -= 10 / _camera.zoom;
    if (IsKeyDown(KEY_S)) _camera.target.y += 10 / _camera.zoom;
    if (IsKeyDown(KEY_A)) _camera.target.x -= 10 / _camera.zoom;
    if (IsKeyDown(KEY_D)) _camera.target.x += 10 / _camera.zoom;

    // Mouse right click movements
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        Vector2 delta = GetMouseDelta();
        _camera.target.x -= delta.x / _camera.zoom;
        _camera.target.y -= delta.y / _camera.zoom;
    }

    // Toggle cell state on left click (if edit mode is enabled)
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && _panel.isEditMode() && !_panel.isMouseOver()) {
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), _camera);
        Vector2 cellPos = _grid.worldToCellPos(mouseWorldPos);
        if (_grid.isCellInGrid(cellPos.x, cellPos.y)) {
            _grid.toggleCell(static_cast<int>(cellPos.x), static_cast<int>(cellPos.y));
        }
    }

    // Toggle grid
    _grid.setLinesVisible(_panel.isShowGrid());

    // Clear the grid
    if (_panel.isClearGridPressed()) {
        _grid.clearGrid();
    }

    // Generate soup
    if (_panel.isGenerateSoupPressed()) {
        _grid.generateSoup();
    }
}

// Update scene
void SimScene::update()
{
    handleInputs();

    // get the next generation if the button is pressed
    if (_panel.isPaused() && _panel.isNextGenerationPressed()) {
        _lastUpdateTime = GetTime();
        _grid.nextGeneration();
    }

    // get the next generation based on time if not paused
    if (!_panel.isPaused() && GetTime() - _lastUpdateTime >= _evolutionSpeed) {
        _grid.nextGeneration();
        _lastUpdateTime = GetTime();
    }
}

// Display the scene
void SimScene::draw()
{
    ClearBackground(LIGHTGRAY);

    BeginMode2D(_camera);
        _grid.draw();
    EndMode2D();

    _panel.draw();
}