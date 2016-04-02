#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>

#include "GraphicsEngine.h"

/**
\mainpage Box and Polygon: Packed, One Buffer & Indexed

\tableofcontents

\section intro Introduction

This is one of several examples showing different ways to load vertex data from the
main program to the graphics card.  In this example, we tightly pack the color and
vertex data into one array buffer on the graphics card, non-interlaced.  This example
also uses an index array for vertex and color position access.

\author    Don Spickler
\version   1.2
\date      Written: 1/11/2016  <BR> Revised: 1/12/2016

\section usage Usage

\subsection run Running the Program

- The program can be run through explorer by double-clicking the executable name.

\subsection options User Options

- Escape:  Ends the program.

- M: Toggles between fill mode and line mode to draw the triangles.

- R: Resets the window size to 700 X 500.

- A: Resets the window size to 600 X 600.

- F10: Saves a screen shot of the graphics window to a jpeg file.

\note Note that the shader programs "PassThroughVert.glsl" and "PassThroughFrag.glsl" are expected
to be in the same folder as the executable.  Your graphics card must also be able to support
OpenGL version 3.3 to run this program.

\section output Output

The console window will display your graphics card OpenGL version support and the
graphics window will display a multicolored box and a red circle.  The title bar of
the window will also display the number of frames per second for the last second and
the average number of frames per second for the entire run of the program.

---

\copyright

GNU Public License.

This software is provided as-is, without warranty of ANY KIND, either expressed or implied,
including but not limited to the implied warranties of merchant ability and/or fitness for a
particular purpose. The authors shall NOT be held liable for ANY damage to you, your computer,
or to anyone or anything else, that may result from its use, or misuse.
All trademarks and other registered names contained in this package are the property
of their respective owners.  USE OF THIS SOFTWARE INDICATES THAT YOU AGREE TO THE ABOVE CONDITIONS.

*/

/**
\file main.cpp
\brief Main driver for the program.

This is the main program driver that sets up the graphics engine and takes care of the
user interface.

\author    Don Spickler
\version   1.2
\date      Written: 1/11/2016  <BR> Revised: 1/12/2016

*/

/**
\brief The function handles the keyboard input from the user.

\param key --- The SFML key code for the key pressed.

\param ge --- graphics engine object reference.

\remark

- M: Toggles between fill mode and line mode to draw the triangles.

- R: Resets the window size to 700 X 500.

- A: Resets the window size to 600 X 600.

- F10: Saves a screen shot of the graphics window to a jpeg file.

*/

void keyPressed(int key, GraphicsEngine &ge)
{
    lib::ColorRGB *color = ge.getStar()->getColor();

    switch (key)
    {
    // If the M key is pressed toggle the display mode between Fill and Line.
    case sf::Keyboard::M:
        ge.changeMode();
        break;

    case sf::Keyboard::N:
        ge.getStar()->setColor(NULL);
        break;

    case sf::Keyboard::C:
        if (color) ge.getStar()->setColor(NULL);
        else ge.getStar()->setColor(new lib::ColorRGB{1, 0, 0});
        break;

    // F10 takes a screnshot.
    case sf::Keyboard::F10:
        ge.screenshot();
        break;

    case sf::Keyboard::R:
        ge.setSize(700, 700);
        break;

    case sf::Keyboard::A:
        ge.setSize(600, 600);
        break;

    default:
        break;
    }
}

/**
\brief The Main function, program entry point.

\return Standard EXIT_SUCCESS return on successful run.

This is the main function, responsible for initializing GLEW and setting up
the SFML interface for OpenGL.

*/

int main()
{
    GraphicsEngine ge("Indexed Star", 700, 700);
    long framecount = 0;
    long totalframecount = 0;

    //  Display OpenGL version.  Not needed in general, just a check.
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    sf::Clock clock;
    sf::Clock totalclock;

    sf::Time time = clock.restart();
    time = totalclock.restart();

    // Start the Game/GUI loop
    while (ge.isOpen())
    {
        // Process user events
        sf::Event event;
        while (ge.pollEvent(event))
        {
            // Close Window or Escape Key Pressed: exit
            if (event.type == sf::Event::Closed ||
                    (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                ge.close();

            // Key is pressed.
            if (event.type == sf::Event::KeyPressed)
                keyPressed(event.key.code, ge);

            // Window is resized.
            if (event.type == sf::Event::Resized)
                ge.resize();
        }

        // Call the display function to do the OpenGL rendering.
        ge.display();

        //  Increment frame counts
        framecount++;
        totalframecount++;

        //  Get Elapsed Time
        float timesec = clock.getElapsedTime().asSeconds();
        float totaltimesec = totalclock.getElapsedTime().asSeconds();
        char titlebar[128];

        //  If another second has elapsed, display the FPS and total FPS.
        if (timesec > 1.0)
        {
            float fps = framecount / timesec;
            float totalfps = totalframecount / totaltimesec;
            sprintf(titlebar, "Box & Circle FPS: %f     Total FPS: %f", fps, totalfps);
            ge.setTitle(titlebar);
            time = clock.restart();
            framecount = 0;
        }
    }

    return EXIT_SUCCESS;
}
