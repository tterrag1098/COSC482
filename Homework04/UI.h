#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "GraphicsEngine.h"

#include <ctime>
#include <random>
#include "utils.h"

/**
\file UI.h

\brief Header file for UI.cpp

\author    Don Spickler
\version   1.1
\date      Written: 1/16/2016  <BR> Revised: 1/16/2016

*/

/**
\class UI

\brief The UI class handles the user interface event processing for the program.  It
contains a pointer to the graphics engine as the communication link to the graphics
and scene objects.

*/

struct DraggingBox
{
    Box* box;
    Point2D origCenter;
};

class UI
{
private:
    GraphicsEngine* ge;  ///< Pointer to the GraphicsEngine that this processor is attached.
    bool mouseDown;      ///< Boolean tracking of the left mouse button.
    lib::Point2D pressPos; ///< Point where the mouse was pressed for this drag.
    std::vector<DraggingBox> capturedBoxes; ///< Vector of boxes captured by the current drag.
    bool secret_mode = false; ///< Press P to switch. You know you want to.

    void keyPressed(sf::Event::KeyEvent keyevent);
    void keyboardStateProcessing();
    void processMouseMoved(sf::Event::MouseMoveEvent mouseMoveEvent);
    void processMouseButtonPressed(sf::Event::MouseButtonEvent mouseButtonEvent);
    void processMouseButtonReleased(sf::Event::MouseButtonEvent mouseButtonEvent);
    lib::Point2D MouseToScreenConversion(sf::Vector2i mousePosition);

public:
    UI(GraphicsEngine* graph);
    ~UI();

    void processEvents();
};

#endif // UI_H_INCLUDED
