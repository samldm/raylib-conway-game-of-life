#include <iostream>
#include "Game.hpp"
#include "main.hpp"

Game::Game() : _currentScene(nullptr)
{ }

Game::~Game()
{
    CloseWindow();
}

// Game init
void Game::init()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game of Life");
    SetTargetFPS(60);

    changeScene(new MenuScene(*this));
}

// Start the game
void Game::run()
{
    while(!WindowShouldClose())
    {
        this->loop();
    }
}

// Change scene
void Game::changeScene(Scene *scene)
{
    _currentScene.reset(scene);
    _currentScene->init();
}

// Main loop
void Game::loop()
{
    if (_currentScene != nullptr) _currentScene->update();
    BeginDrawing();
        if(_currentScene != nullptr) _currentScene->draw();
    EndDrawing();
}