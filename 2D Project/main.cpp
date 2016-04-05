#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>

#include "GraphicsEngine.h"
#include "UI.h"

/**
\file main.cpp
\brief Main driver for the program.

This is the main program driver that sets up the graphics engine, the user interface
class, and links the two.

\version   1.1
\date      Written: 2/28/2016  <BR> Revised: 2/28/2016

*/


/**
\brief The Main function, program entry point.

\return Standard EXIT_SUCCESS return on successful run.

This is the main function, responsible for initializing GLEW and setting up
the SFML interface for OpenGL.

*/

int main()
{
    sf::RenderWindow d;
    if (glewInit())
    {
        std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string progName = "Faux-Paint";
    GraphicsEngine ge(progName, 800, 600);
    UI ui(&ge);

    long framecount = 0;
    sf::Clock clock;
    sf::Time time = clock.restart();

    while (ge.isOpen())
    {
        ge.display();
        ui.processEvents();

        framecount++;
        float timesec = clock.getElapsedTime().asSeconds();
        char titlebar[128];
        if (timesec > 1.0)
        {
            float fps = framecount / timesec;
            sprintf(titlebar, "%s     FPS: %.2f", progName.c_str(), fps);
            ge.setTitle(titlebar);
            time = clock.restart();
            framecount = 0;
        }
    }

    return EXIT_SUCCESS;
}
