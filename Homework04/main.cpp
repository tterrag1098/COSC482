#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>

#include "GraphicsEngine.h"
#include "UI.h"

/**
\mainpage Homework 04

\tableofcontents

\section intro Introduction

This program allows the user to create and remove boxes on the screen, as well as manipulate them using the mouse and keyboard.

\author    Don Spickler, 
\version   1.2
\date      Written: 1/9/2016  <BR> Revised: 2/26/2016

\section usage Usage

\subsection run Running the Program

- The program can be run through explorer by double-clicking the executable name.

\subsection options User Options

If no modifier keys are pressed:

- Right Click: Adds a new box at the cursor position

- Left Click and Drag: Grabs all boxes under the cursor and drags them.

- C: Clears the boxes from the screen.

- P: Toggles secret mode.

- Escape:  Ends the program.

- M: Toggles between fill mode and line mode to draw the triangles.

- R: Resets the window size to 700 X 500.

- A: Resets the window size to 600 X 600.

- F9: Saves a screen shot of the graphics window to a png file.

- F10: Saves a screen shot of the graphics window to a jpeg file.

- Left: Moves the boxes to the left.

- Right: Moves the boxes to the right.

- Up: Moves the boxes up.

- Down: Moves the boxes down.

If the control key is down:

- Right Click: Deletes any boxes underneath the cursor.

\section output Output

The console window will display your graphics card OpenGL version support and the
graphics window will display a blank screen.  The title bar of the window will also
display the number of frames per second for the last second. Upon right clicking, a
new box is created at the cursor position. The user can click and drag any box on
the screen around. The arrow keys will move all boxes at once.

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

This is the main program driver that sets up the graphics engine, the user interface
class, and links the two.

\author    Don Spickler, 
\version   1.2
\date      Written: 1/9/2016  <BR> Revised: 2/26/2016

*/


/**
\brief The Main function, program entry point.

\return Standard EXIT_SUCCESS return on successful run.

This is the main function, responsible for initializing GLEW and setting up
the SFML interface for OpenGL.

*/

int main()
{
    std::string progName = "Homework #4";
    GraphicsEngine ge(progName, 700, 500);
    UI ui(&ge);
    long framecount = 0;

    //  Display OpenGL version.  Not needed in general, just a check.
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    sf::Clock clock;
    sf::Time time = clock.restart();

    // Start the Game/GUI loop
    while (ge.isOpen())
    {
        // Process any events.
        ui.processEvents();

        // Call the display function to do the OpenGL rendering.
        ge.display();

        //  Increment frame counts
        framecount++;

        //  Get Elapsed Time
        float timesec = clock.getElapsedTime().asSeconds();
        char titlebar[128];

        //  If another second has elapsed, display the FPS and total FPS.
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
