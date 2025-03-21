#include "main.hpp"
#include "Scene.hpp"
#include "raygui.h"
#include <cstdlib>
#include <iostream>

// Menu scene constructor
MenuScene::MenuScene(Game& game) : Scene(game)
{
    this->_widthInput = "30";
    this->_heightInput = "30";
}

// Menu init
void MenuScene::init()
{
    _startSimulation = false;
    _editModeWidth = false;
    _editModeHeight = false;
}

// Update scene
void MenuScene::update()
{
    if (_startSimulation) {
        try {
            _startSimulation = false;

            int width = std::atoi(_widthInput.c_str());
            int height = std::atoi(_heightInput.c_str());
            
            if (width <= 0 || width > MAX_GRID_WIDTH || height <= 0 || height > MAX_GRID_HEIGHT) {
                _errorMessage = TextFormat("Invalid dimensions. (Max: %d/%d)", MAX_GRID_WIDTH, MAX_GRID_HEIGHT);
            } else {
                game.changeScene(new SimScene(game, width, height));
            }
        }
        catch (const std::invalid_argument& e) {
            _errorMessage = TextFormat("Invalid dimensions. (Max: %d/%d)", MAX_GRID_WIDTH, MAX_GRID_HEIGHT);
        }
        catch (const std::out_of_range& e) {
            _errorMessage = TextFormat("Invalid dimensions. (Max: %d/%d)", MAX_GRID_WIDTH, MAX_GRID_HEIGHT);
        }
    }
}

// Display the menu scene
void MenuScene::draw()
{
    ClearBackground(RAYWHITE);

    // Title
    DrawText("Game of Life", 100, 50, 26, DARKGRAY);
    DrawText("A Raylib project by Samuel L.", 100, 80, 18, GRAY);

    DrawLine(100, 110, 350, 110, LIGHTGRAY);
    
    // Grid configuration
    DrawText("Grid configuration:", 100, 120, 18, GRAY);

    // width
    DrawText("Width:", 100, 150, 20, DARKGRAY);
    if (GuiTextBox((Rectangle){ 180, 145, 100, 30 }, _widthInput.data(), _widthInput.capacity() + 1, _editModeWidth))
        _editModeWidth = !_editModeWidth;

    // height
    DrawText("Height:", 100, 200, 20, DARKGRAY);
    if (GuiTextBox((Rectangle){ 180, 195, 100, 30 }, _heightInput.data(), _heightInput.capacity() + 1, _editModeHeight))
        _editModeHeight = !_editModeHeight;

    // Display the error message
    if (!_errorMessage.empty()) {
        DrawText(_errorMessage.c_str(), 100, 240, 18, RED);
    }

    // Start the simulation
    if (GuiButton((Rectangle){ 180, 260, 120, 40 }, "Start Simulation")) 
        _startSimulation = true;

}
