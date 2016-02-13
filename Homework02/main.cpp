#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>

#include "GraphicsEngine.h"
#include "Star.h"

using namespace std;

/**
\mainpage Triangles program, the "Hello World" of OpenGL/GLSL.

\tableofcontents

\section intro Introduction

This program is essentially the Hello World of computer graphics. It simply displays two
colored triangles on the screen.

\author    Don Spickler
\version   1.1
\date      Written: 11/21/2015  <BR> Revised: 11/21/2015

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
graphics window will display the two triangles.

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
\brief Triangles program.

This is the main program that displays two colored triangles on the screen.

\author    Don Spickler
\version   1.1
\date      Written: 11/21/2015  <BR> Revised: 11/21/2015

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
        ge.setSize(700, 500);
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
    GraphicsEngine ge("Triangles");

    ge.setSize(700, 500);
    ge.add(new lib::Star(NULL, 5));

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
