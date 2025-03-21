#ifndef PANEL_HPP
#define PANEL_HPP

#include "raylib.h"
#include "raygui.h"

class Panel {
private:
    Rectangle _bounds;
    bool _isEditMode = false;
    float& _evolutionSpeed;
    bool _isPaused = true;
    bool _nextGenerationPressed = true;
    bool _clearGrid = false;
    bool _generateSoup = false;

public:
    Panel(int x, int y, float& evolutionSpeed);
    
    void update();
    void draw();

    bool isMouseOver();
    
    bool isEditMode() const { return _isEditMode; }
    bool isPaused() const { return _isPaused; }
    bool isNextGenerationPressed() const { return _nextGenerationPressed; }
    bool isClearGridPressed() const { return _clearGrid; }
    bool isGenerateSoupPressed() const { return _generateSoup; }
};

#endif
