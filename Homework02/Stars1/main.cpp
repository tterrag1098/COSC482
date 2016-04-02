#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
#include <string>

#include "GraphicsEngine.h"
#include "Star.h"

using namespace std;

/**
\mainpage Star #1, produces a single red 5-point star.

\tableofcontents

\section intro Introduction

This program displays a single 5-point star on the screen, colored red.

\author    , 
\version   1.0
\date      Written: 2/12/2016 <BR> Revised: 2/12/2016

\section usage Usage

\subsection run Running the Program

- The program can be run through explorer by double-clicking the executable name.

\subsection options User Options

- Escape:  Ends the program.

- M: Toggles between fill mode and line mode to draw the triangles.

- R: Resets the window size back to 700 X 500.

- F10: Saves a screen shot of the graphics window to a jpeg file.

\note Note that the shader programs "PassThroughVert.glsl" and "PassThroughFrag.glsl" are expected
to be in the same folder as the executable.  Your graphics card must also be able to support
OpenGL version 3.3 to run this program.

\section output Output

The console window will display your graphics card OpenGL version support and the
graphics window will display the star.

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
\brief Star #1 program.

This is the main program that displays a red 5-point star on the screen.

\author    , 
\version   1.0
\date      Written: 2/12/2016  <BR> Revised: 2/12/2016

*/

/**
\brief The function handles the keyboard input from the user.

\param key --- The SFML key code for the key pressed.

\param ge --- graphics engine object reference.

\remark

- M: Toggles between fill mode and line mode to draw the triangles.

- R: Resets the window size to 700 X 500.

- F10: Saves a screen shot of the graphics window to a jpeg file.

*/

void keyPressed(int key, GraphicsEngine &ge)
{
    switch (key)
    {
    // If the M key is pressed toggle the display mode between Fill and Line.
    case sf::Keyboard::M:
        ge.changeMode();
        break;

    // F10 takes a screnshot.
    case sf::Keyboard::F10:
        ge.screenshot();
        break;

    case sf::Keyboard::R:
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

It also handles adding Drawable objects to the GraphicsEngine

*/

int main()
{
    // Create our graphics
    GraphicsEngine ge("Star #1");

    // Use a square size to preserve aspect ratio
    ge.setSize(600, 600);
    // Add a star, colored red, with 5 points, with a diameter of 0.9.
    ge.add(new lib::Star(&lib::RED, 5, 0.9f));

    // Run the init AFTER we add drawables
    ge.init();

    //  Display OpenGL version.  Not needed in general, just a check.
    cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;

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
    }

    return EXIT_SUCCESS;
}
