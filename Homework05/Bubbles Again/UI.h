#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "GraphicsEngine.h"

#include <ctime>
#include <random>
#include "utils.h"

/**
\file UI.h

\brief Header file for UI.cpp

\author    Don Spickler, 
\version   1.2
\date      Written: 1/16/2016  <BR> Revised: 3/4/2016

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
    GraphicsEngine* ge;  ///< Pointer to the GraphicsEngine that this processor is attached to.

    void keyPressed(sf::Event::KeyEvent keyevent);

public:
    UI(GraphicsEngine* graph);
    ~UI();

    void processEvents();
};

#endif // UI_H_INCLUDED
