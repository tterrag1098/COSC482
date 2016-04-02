#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>

#include "GraphicsEngine.h"
#include "UI.h"

/**
\mainpage Beach Balls

\tableofcontents

\section intro Introduction

This program renders a bunch of different beach balls that move in different ways. Some spin on an axis, some orbit and spin around the origin. All are very bouncy.

It makes use of a uniform PVM transformation matrix in the shader which is re-applied for each beach ball.

\author    
\version   1.3
\date      Written: 2/28/2016  <BR> Revised: 3/28/2016

\section usage Usage

\subsection run Running the Program

- The program can be run through explorer by double-clicking the executable name.

\subsection options User Options

- Escape:  Ends the program.
- M: Toggles between fill mode and line mode to draw the triangles.
- R: Resets the window size to 700 X 500.
- A: Resets the window size to 600 X 600.
- B: Toggles the borders.
- F: Toggles the faces.
- W: Toggles the front face.
- C: Cycles through the culling modes.
- Q: Toggles culling on and off.
- F7: Sets the flag to draw the axes.
- F8: Sets the flag to hide the axes.
- F9: Saves a screen shot of the graphics window to a png file.
- F10: Saves a screen shot of the graphics window to a jpeg file.
- F11: Turns on the spherical camera.
- F12: Turns on the yaw-pitch-roll camera.

If the spherical camera is currently selected,

- Left: Increases the camera's theta value.
- Right: Decreases the camera's theta value.
- Up: Increases the camera's psi value.
- Down: Decreases the camera's psi value.
- Ctrl+Up: Decreases the camera's radius.
- Ctrl+Down: Increases the camera's radius.

If the yaw-pitch-roll camera is currently selected,

- Left: Increases the yaw.
- Right: Decreases the yaw.
- Up: Increases the pitch.
- Down: Decreases the pitch.

- Ctrl+Left: Increases the roll.
- Ctrl+Right: Decreases the roll.
- Ctrl+Up: Moves the camera forward.
- Ctrl+Down: Moves the camera backward.

- Shift+Left: Moves the camera left.
- Shift+Right: Moves the camera right.
- Shift+Up: Moves the camera up.
- Shift+Down: Moves the camera down.

If the spherical camera is currently selected, a click and drag with the left mouse
button will alter the theta and psi angles of the spherical camera to give the impression
of the mouse grabbing and moving the coordinate system.

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

\author    
\version   1.2
\date      Written: 2/28/2016  <BR> Revised: 3/28/2016

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

    std::string progName = "Beach Balls";
    GraphicsEngine ge(progName, 700, 500);
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
