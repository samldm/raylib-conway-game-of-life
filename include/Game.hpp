#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>
#include <string>
#include <memory>

#include "Scene.hpp"

class Scene;

// Game class that manage scenes
class Game
{
public:
    Game();
    ~Game();

    // Init the game
    void init();

    // Run the game
    void run();

    // Change scene
    void changeScene(Scene *scene);

private:
    void loop();

    std::unique_ptr<Scene> _currentScene;
};


#endif