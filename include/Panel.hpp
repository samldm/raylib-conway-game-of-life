#ifndef PANEL_HPP
#define PANEL_HPP

#include "raylib.h"
#include "raygui.h"

// Panel class that contains tools for the simulation
class Panel {
public:
    Panel(int x, int y, float& evolutionSpeed);

    // Display the panel
    void draw();

    // Returns true if the mouse is over
    bool isMouseOver();

    // Returns true if edit mode is enabled
    bool isEditMode() const { return _editMode; } 

    // Returns true if show grid is enabled
    bool isShowGrid() const { return _showGrid; }

    // Returns true if paused
    bool isPaused() const { return _paused; }

    // Returns true if next generation button is pressed
    bool isNextGenerationPressed() const { return _nextGenerationPressed; }
    
    // Returns true if clear grid button is pressed
    bool isClearGridPressed() const { return _clearGrid; }

    // Returns true if generate soup button is pressed
    bool isGenerateSoupPressed() const { return _generateSoup; }

private:
    Rectangle _bounds;
    bool _editMode = false;
    bool _showGrid = true;
    float& _evolutionSpeed;
    bool _paused = true;
    bool _nextGenerationPressed = true;
    bool _clearGrid = false;
    bool _generateSoup = false;

};

#endif
