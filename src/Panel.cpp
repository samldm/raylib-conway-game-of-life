#include "Panel.hpp"

Panel::Panel(int x, int y, float& evolutionSpeed)
 : _bounds{ (float) x, (float) y, 160, 245 }, _evolutionSpeed(evolutionSpeed)
{ }

void Panel::update()
{

}

void Panel::draw()
{
    // Fond
    DrawRectangleRec(_bounds, Fade(BLACK, 0.25f));
    DrawRectangleLines(_bounds.x, _bounds.y, _bounds.width, _bounds.height, BLACK);
    
    // Titre
    DrawText("Panel", _bounds.x + 10, _bounds.y + 10, 18, BLACK);
    
    // EditMode
    if (GuiButton({ _bounds.x + 10, _bounds.y + 30, 140, 30}, _isEditMode ? "Edit Mode: ON" : "Edit Mode: OFF"))
        _isEditMode = !_isEditMode;
    
    // Gestion de la vitesse
    DrawText(TextFormat("Speed: %.2f sec/gen", _evolutionSpeed), _bounds.x + 10, _bounds.y + 65, 14, BLACK);
    GuiSlider({ _bounds.x + 10, _bounds.y + 80, 140, 20 }, "", "", &_evolutionSpeed, 0.01f, 1.0f);

    // Pause
    if (GuiButton({ _bounds.x + 10, _bounds.y + 105, 140, 30}, _isPaused ? "Start Simulation" : "Pause Simulation"))
        _isPaused = !_isPaused;
    
    // Prochaine génération
    _nextGenerationPressed = GuiButton({ _bounds.x + 10, _bounds.y + 140, 140, 30}, "Next Generation");

    // Vider la grille
    _clearGrid = GuiButton({ _bounds.x + 10, _bounds.y + 175, 140, 30}, "Clear Grid");

    // Générer de la 'soupe'
    _generateSoup = GuiButton({ _bounds.x + 10, _bounds.y + 210, 140, 30}, "Generate Soup");

}

bool Panel::isMouseOver()
{
    Vector2 mousePos = GetMousePosition();
    return CheckCollisionRecs({mousePos.x, mousePos.y, 1, 1}, _bounds);
}
