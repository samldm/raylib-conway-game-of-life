#ifndef GAME_HPP
#define GAME_HPP

#include <raylib.h>
#include <string>
#include <memory>

#include "Scene.hpp"

class Scene;

class Game
{
public:
    Game();
    ~Game();

    void init();
    void run();
    void changeScene(Scene *scene);
private:
    void loop();

    std::unique_ptr<Scene> _currentScene;
};


#endif