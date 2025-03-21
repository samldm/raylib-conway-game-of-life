#include "Panel.hpp"

// Panel constructor
Panel::Panel(int x, int y, float& evolutionSpeed)
 : _bounds{ (float) x, (float) y, 160, 250 }, _evolutionSpeed(evolutionSpeed)
{ }

// Display the panel
void Panel::draw()
{
    // Background
    DrawRectangleRec(_bounds, Fade(BLACK, 0.25f));
    DrawRectangleLines(_bounds.x, _bounds.y, _bounds.width, _bounds.height, BLACK);
    
    float y = _bounds.y;

    // Title
    DrawText("Panel", _bounds.x + 10, (y += 10), 18, BLACK);
    y += 20;
    
    // EditMode
    if (GuiButton({ _bounds.x + 10, y, 140, 30}, _editMode ? "Edit Mode: ON" : "Edit Mode: OFF"))
        _editMode = !_editMode;
    y += 30;
    
    // Show grid
    if (GuiButton({ _bounds.x + 10, (y += 5), 140, 30}, _showGrid ? "Grid: ON" : "Grid: OFF"))
        _showGrid = !_showGrid;
    y += 30;
    
    // Speed handling
    DrawText(TextFormat("Speed: %.2f sec/gen", _evolutionSpeed), _bounds.x + 11, (y += 7), 12, BLACK);
    y += 15;
    GuiSlider({ _bounds.x + 10, (y += 5), 140, 20 }, "", "", &_evolutionSpeed, 0.01f, 1.0f);
    y += 20;

    // Pause
    if (GuiButton({ _bounds.x + 10, (y += 5), 140, 30}, _paused ? "Start Simulation" : "Pause Simulation"))
        _paused = !_paused;
    y += 30;

    // Next generation
    _nextGenerationPressed = GuiButton({ _bounds.x + 10, (y += 5), 140, 30}, "Next Generation");
    y += 30;

    // clear the grid
    _clearGrid = GuiButton({ _bounds.x + 10, (y += 5), 140, 30}, "Clear Grid");
    y += 30;

    // generate soup
    _generateSoup = GuiButton({ _bounds.x + 10, (y += 5), 140, 30}, "Generate Soup");
    y += 30;

    _bounds.height = y;
}

// Returns true if the mouse if over the panel
bool Panel::isMouseOver()
{
    Vector2 mousePos = GetMousePosition();
    return CheckCollisionRecs({mousePos.x, mousePos.y, 1, 1}, _bounds);
}
