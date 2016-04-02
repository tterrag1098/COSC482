#include "UI.h"

/**
\file UI.cpp
\brief User interface processor for the program.

\author    Don Spickler, 
\version   1.2
\date      Written: 1/16/2016  <BR> Revised: 3/4/2016

*/

/**
\brief Constructor

\param graph --- Pointer to the GraphicsEngine that this interface processor is attached.

Simply stores the pointer of the GraphicsEngine.

*/

UI::UI(GraphicsEngine* graph)
{
    ge = graph;
    srand(clock());
}


/**
\brief Destructor

No implementation needed at this point.

*/

UI::~UI() {}

/**
\brief The method handles the SFML event processing and calls the keyboard state processor
method.

This method processes all events in the current SFML event queue and calls the
corresponding processing method.  At the end it calls the keyboard state processor
method, outside the event loop.

*/

void UI::processEvents()
{
    // Process user events
    sf::Event event;
    while (ge->pollEvent(event))
    {
        // Close Window or Escape Key Pressed: exit
        if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            ge->close();

        // Key is pressed.
        if (event.type == sf::Event::KeyPressed)
            keyPressed(event.key);

        // Window is resized.
        if (event.type == sf::Event::Resized)
            ge->resize();
    }
}

/**
\brief The function handles the keyboard input events from the user.

\param keyevent --- The SFML key code for the key pressed.

\remark

- F1: Enables vsync.

- F2: Disables vsync.

- F9: Saves a screen shot of the graphics window to a png file.

- F10: Saves a screen shot of the graphics window to a jpeg file.

- R: Resets the window size to 700 X 500.

- A: Resets the window size to 600 X 600.

- C: Clears the bubbles from the screen.
*/

void UI::keyPressed(sf::Event::KeyEvent keyevent)
{
    int key = keyevent.code;

    switch (key)
    {
    case sf::Keyboard::F1:
        ge->setVerticalSyncEnabled(true);
        break;

    case sf::Keyboard::F2:
        ge->setVerticalSyncEnabled(false);
        break;

    // F9 takes a png screenshot.
    case sf::Keyboard::F9:
        ge->screenshot("png");
        break;

    // F9 takes a jpg screenshot.
    case sf::Keyboard::F10:
        ge->screenshot("jpg");
        break;

    // Resets the screen size to 700 X 500.
    case sf::Keyboard::R:
        ge->setSize(700, 500);
        break;

    // Sets the screen size to 600 X 600.
    case sf::Keyboard::A:
        ge->setSize(600, 600);
        break;

    // Clears all bubbles
    case sf::Keyboard::C:
        ge->refresh();
        break;

    default:
        break;
    }
}
