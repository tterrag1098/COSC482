#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "GraphicsEngine.h"
#include "TextRendererTTF.h"

class Listener;

/**
\file UI.h

\brief Header file for UI.cpp

\author    Don Spickler
\version   1.1
\date      Written: 2/28/2016  <BR> Revised: 2/28/2016

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
    bool dragging;       ///< Boolean tracking drag state.
    TextRendererTTF *tr; ///< Text renderer instance.

    glm::ivec2 prevMousePos;   ///< Last position of the mouse on the screen.
    glm::ivec2 prevMouseClick; ///< Last position of the mouse click.

    std::vector<Listener*> listeners; ///< All listeners for UI events

    void keyPressed(sf::Event::KeyEvent keyevent);
    void textEntered(sf::Event::TextEvent textevent);
    void keyboardStateProcessing();
    void keyboardStateProcessingSphericalCamera();
    void keyboardStateProcessingYPRCamera();
    void keyboardStateProcessingLight();

    void processMouseMoved(sf::Event::MouseMoveEvent mouseMoveEvent);
    void processMouseButtonPressed(sf::Event::MouseButtonEvent mouseButtonEvent);
    void processMouseButtonReleased(sf::Event::MouseButtonEvent mouseButtonEvent);
    void processMouseScrolled(sf::Event::MouseWheelEvent mouseScrollEvent);

public:
    UI(GraphicsEngine* graph);
    ~UI();

    bool down(sf::Keyboard::Key key);
    bool anyDown(std::initializer_list<sf::Keyboard::Key> list);

    glm::ivec2 getPrevMousePos() const; ///< The position of the mouse on the previous update. Used for delta calculation in camera.
    glm::ivec2 getPrevMouseClick() const; ///< The last place the mouse was clicked. Used for delta calculation in UI.
    bool isMouseDown() const; ///< Returns a cached value of the mouse's pressed state.
    GraphicsEngine* getEngine() const; ///< Gets the [GraphicsEngine](@ref GraphicsEngine) instance.
    TextRendererTTF* getTextRenderer() const; ///< Gets the TextRenderTTF instance.

    void processEvents();

    void addListener(Listener *l); ///< Adds an object to listen to mouse events
};

#endif // UI_H_INCLUDED
