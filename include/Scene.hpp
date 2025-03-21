#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include "Game.hpp"
#include "Grid.hpp"
#include "Panel.hpp"

class Game;

// Scene interface
class Scene {
public:
    Scene(Game& game) : game(game) {}
    
    // Init scene
    virtual void init() = 0;
    
    // Update scene
    virtual void update() = 0;
    
    // Draw scene
    virtual void draw() = 0;

    virtual ~Scene() {}

protected:
    // Game reference
    Game& game;
};

// Menu scene for grid configuration
class MenuScene : public Scene {
public:
    MenuScene(Game& game);
    void init() override;
    void update() override;
    void draw() override;

private:
    bool _startSimulation = false;

    std::string _widthInput;
    std::string _heightInput;
    bool _editModeWidth = false;
    bool _editModeHeight = false;

    std::string _errorMessage = "";
};

// Simulation scene
class SimScene : public Scene {
public:
    SimScene(Game& game, int gridWidth, int gridHeight);
    void init() override;
    void update() override;
    void draw() override;

private:
    Grid _grid;
    Panel _panel;
    Camera2D _camera;
    
    float _evolutionSpeed;
    double _lastUpdateTime;

    void handleInputs();
};
    
#endif
