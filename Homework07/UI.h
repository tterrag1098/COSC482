#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "GraphicsEngine.h"

/**
\file UI.h

\brief Header file for UI.cpp

\author    
\version   1.2
\date      Written: 2/28/2016  <BR> Revised: 4/1/2016

*/

/**
\class UI

\brief The UI class handles the user interface event processing for the program.  It
contains a pointer to the graphics engine as the communication link to the graphics
and scene objects.

*/

class UI
{
private:
    GraphicsEngine* ge;  ///< Pointer to the GraphicsEngine that this processor is attached.
    bool mouseDown;      ///< Boolean tracking of the left mouse button.

    sf::Vector2i LastPosition;  ///< Last position of the mouse on the screen.

    void keyPressed(sf::Event::KeyEvent keyevent);
    void keyboardStateProcessing();
    void keyboardStateProcessingSphericalCamera();
    void keyboardStateProcessingYPRCamera();
    void keyboardStateProcessingLight();

    bool down(sf::Keyboard::Key key);
    bool anyDown(std::initializer_list<sf::Keyboard::Key> list);
    void updateState(int& n1, int& n2);

    void processMouseMoved(sf::Event::MouseMoveEvent mouseMoveEvent);
    void processMouseButtonPressed(sf::Event::MouseButtonEvent mouseButtonEvent);
    void processMouseButtonReleased(sf::Event::MouseButtonEvent mouseButtonEvent);
    void processMouseScrolled(sf::Event::MouseWheelEvent mouseScrollEvent);

public:
    UI(GraphicsEngine* graph);
    ~UI();

    void processEvents();
};

#endif // UI_H_INCLUDED
