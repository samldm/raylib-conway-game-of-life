#include "main.hpp"
#include "Game.hpp"
#include <random>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main() {
    srand(time(NULL));
    
    Game game;
    game.init();
    game.run();
    
    return 0;
}
