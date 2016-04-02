#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>

#include "UI.h"
#include "GraphicsEngine.h"

/**
\mainpage Box and Polygon: Packed, One Buffer & Indexed

\tableofcontents

\section intro Introduction

This program will display a simple screen with animated bubbles. These bubbles
have random sizes and colors, and will bounce off the edges of the window.

It maintains the aspect ratio, so changing the size of the window will change
the area the bubbles can bounce off of. The bubbles are animated irrespective
of framerate, so switching VSync on/off should have minimal effect on the animation
speed.

\author    Don Spickler, 
\version   1.3
\date      Written: 1/11/2016  <BR> Revised: 3/4/2016

\section usage Usage

\subsection run Running the Program

- The program can be run through explorer by double-clicking the executable name.

\subsection options User Options

- Escape:  Ends the program.

- F1: Enables vsync.

- F2: Disables vsync.

- F9: Saves a screen shot of the graphics window to a png file.

- F10: Saves a screen shot of the graphics window to a jpeg file.

- R: Resets the window size to 700 X 500.

- A: Resets the window size to 600 X 600.

- C: Clears the bubbles from the screen.

\section output Output

The console window will display your graphics card OpenGL version support and the
graphics window will display 20 randomized and animated bubbles. The title bar of
the window will also display the number of frames per second for the last second.

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

\author    Don Spickler, 
\version   1.3
\date      Written: 1/11/2016  <BR> Revised: 3/4/2016

*/

/**
\brief The Main function, program entry point.

\return Standard EXIT_SUCCESS return on successful run.

This is the main function, responsible for initializing GLEW and setting up
the SFML interface for OpenGL.

*/

int main()
{
    std::string progName = "Bubbles Again";
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
