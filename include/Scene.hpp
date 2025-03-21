#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include "Game.hpp"
#include "Grid.hpp"
#include "Panel.hpp"

class Game;

class Scene {
protected:
    Game& game;
public:
    Scene(Game& game) : game(game) {}
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    virtual ~Scene() {}
};

class MenuScene : public Scene {
private:
    bool _startSimulation = false;

    std::string _widthInput;
    std::string _heightInput;
    bool _editModeWidth = false;
    bool _editModeHeight = false;

    std::string _errorMessage = "";
public:
    MenuScene(Game& game);
    void init() override;
    void update() override;
    void draw() override;
};


class SimScene : public Scene {
private:
    Grid _grid;
    Panel _panel;
    Camera2D _camera;
    
    float _evolutionSpeed;
    double _lastUpdateTime;

    void handleInputs();
public:
    SimScene(Game& game, int gridWidth, int gridHeight);
    void init() override;
    void update() override;
    void draw() override;
};
    
#endif
