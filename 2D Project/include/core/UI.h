#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "core/GraphicsEngine.h"
#include "render/Box.h"
#include "tool/Tool.h"

/**
\file UI.h

\brief Header file for UI.cpp

\version   1.2
\date      Written: 2/28/2016  <BR> Revised: 4/1/2016

*/

/**
\class UI

\brief The UI class handles the user interface event processing for the program.  It
contains a pointer to the graphics engine as the communication link to the graphics
and scene objects.

*/

class Tool;

class UI
{
    friend class GraphicsEngine;

private:
    GraphicsEngine* ge;  ///< Pointer to the GraphicsEngine that this processor is attached.
    bool mouseDown;      ///< Boolean tracking of the left mouse button.
    Tool *tool;          ///< The active tool.

    glm::ivec2 LastPosition;  ///< Last position of the mouse on the screen.

    void keyPressed(sf::Event::KeyEvent keyevent);
    void keyboardStateProcessing();

    bool down(sf::Keyboard::Key key);
    bool anyDown(std::initializer_list<sf::Keyboard::Key> list);

    void processMouseMoved(sf::Event::MouseMoveEvent mouseMoveEvent);
    void processMouseButtonPressed(sf::Event::MouseButtonEvent mouseButtonEvent);
    void processMouseButtonReleased(sf::Event::MouseButtonEvent mouseButtonEvent);
    void processMouseScrolled(sf::Event::MouseWheelEvent mouseScrollEvent);

    void processEvents();

public:
    UI(GraphicsEngine* graph);
    ~UI();

    glm::vec2 toScreenCoords(glm::ivec2 mousePosition) const;
    glm::ivec2 prevMousePos() const;
    bool isMouseDown() const;
    GraphicsEngine* getEngine() const;
};

#endif // UI_H_INCLUDED
