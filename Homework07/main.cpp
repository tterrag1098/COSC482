#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>

#include "GraphicsEngine.h"
#include "UI.h"

/**
\mainpage Homework 07

\tableofcontents

\section intro Introduction

This program can render a few different models with different materials.

It can also use either basic Phong lighting or halfway Phong lighting.

\author    
\version   1.2
\date      Written: 2/28/2016  <BR> Revised: 4/1/2016

\section usage Usage

\subsection run Running the Program

- The program can be run through explorer by double-clicking the executable name.

\subsection options User Options

- Escape:  Ends the program.
- Number keys: Selects the material
- Model Selection:
    - Z - Teapot
    - X - Sphere
    - C - Torus
    - V - Trefoil
    - B - Umbilic Torus
    - N - Braided Torus
    - M - Helical Torus
    - L - Mobius Strip
    - K - Tessellated Wall - 1x1
    - J - Tessellated Wall - 20x20

- R: Resets the window size to 700 X 500.
- A: Resets the window size to 600 X 600.
- F7: Activates the basic shader.
- F8: Activates the halfway shader.
- F9: Saves a screen shot of the graphics window to a png file.
- F10: Saves a screen shot of the graphics window to a jpeg file.
- F11: Turns on the spherical camera.
- F12: Turns on the yaw-pitch-roll camera.

Arrow Key Actions:

- F1+Left/Right: Rotates the object around the Y axis.
- F1+Up/Down: Rotates the object around the X axis.

- F2+Left/Right: Rotates the object around the Y axis.
- F2+Up/Down: Rotates the object around the Z axis.

- F3+Left/Right: Translates the object around the X axis.
- F3+Up/Down: Translates the object around the Z axis.

- F4+Left/Right: Translates the object around the Y axis.

- Alt+Left: Increases the light's theta value.
- Alt+Right: Decreases the light's theta value.
- Alt+Up: Increases the light's psi value.
- Alt+Down: Decreases the light's psi value.
- Alt+Ctrl+Up: Decreases the light's radius.
- Alt+Ctrl+Down: Increases the light's radius.

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

\author    Don Spickler
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

    std::string progName = "Homework 07";
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
