#include <iostream>
#include "Game.hpp"
#include "main.hpp"

Game::Game() : _currentScene(nullptr)
{ }

Game::~Game()
{
    CloseWindow();
}

void Game::init()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game of Life");
    SetTargetFPS(60);

    changeScene(new MenuScene(*this));
}

void Game::run()
{
    while(!WindowShouldClose())
    {
        this->loop();
    }
}

void Game::changeScene(Scene *scene)
{
    _currentScene.reset(scene);
    _currentScene->init();
}

void Game::loop()
{
    if (_currentScene != nullptr) _currentScene->update();
    BeginDrawing();
        if(_currentScene != nullptr) _currentScene->draw();
    EndDrawing();
}