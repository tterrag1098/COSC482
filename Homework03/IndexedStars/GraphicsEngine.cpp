#include "GraphicsEngine.h"

/**
\file GraphicsEngine.cpp
\brief Main graphics driver for the program.

This class extends sf::RenderWindow.

\author    Don Spickler
\version   1.1
\date      Written: 1/9/2016  <BR> Revised: 1/9/2016

*/

int NumPoints = 20;

/**
\brief Constructor

\param title --- Title to be placed in the titlebar of the graphics window.

\param width --- The width (in pixels) of the graphics window.

\param height --- The height (in pixels) of the graphics window.

Creates rendering window, enables GLEW, loads the shaders, and sets some initial
data settings.

*/

GraphicsEngine::GraphicsEngine(std::string title, GLint width, GLint height) :
    sf::RenderWindow(sf::VideoMode(width, height),
                     title,
                     sf::Style::Default,
                     sf::ContextSettings(24, 8, 4, 3, 3))
{
    // Turn on GLEW
    if (glewInit())
    {
        std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;
        exit(EXIT_FAILURE);
    }

    //  Load the shaders
    GLuint program = LoadShadersFromFile("PassThroughVert.glsl", "PassThroughFrag.glsl");

    if (!program)
    {
        std::cerr << "Could not load Shader programs." << std::endl;
        exit(EXIT_FAILURE);
    }

    refresh();

    mode = GL_FILL;
    sscount = 1;

    if (SetVS)
        setVerticalSyncEnabled(true);
    else
        setFramerateLimit(0);

    // Make it the active window for OpenGL calls
    setActive();

    // Turn on the shader.
    glUseProgram(program);
}

/**
\brief Destructor

Currently empty, no allocated memory to clear.

*/

GraphicsEngine::~GraphicsEngine() {}

/**
\brief The function responsible for drawing to the OpenGL frame buffer.

This function clears the screen and calls the draw functions of the box and circle.

*/

void GraphicsEngine::display()
{
    // Clear the screen (Frame Buffer)
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the objects.
    for (Star *s : stars)
    {
        s->draw();
    }

    sf::RenderWindow::display();
}

void GraphicsEngine::refresh()
{
    stars.clear();
    srand(time(0));
    int num_stars = rand() % 15 + 5;
    for (int i = 0; i < num_stars; i++)
    {
        float radius = lib::rand_float() * 0.25f + 0.1f;
        int points = rand() % 15 + 5;
        lib::Point2D center = {(lib::rand_float() * 2) - 1, (lib::rand_float() * 2) - 1};
        Star *star = new Star(center, radius, points);
        star->setColor(NULL);
        stars.push_back(star);
    }
}

std::vector<Star*> GraphicsEngine::getStars()
{
    return stars;
}

/**
\brief Changes the fill, line, and point mode being used.

*/

void GraphicsEngine::changeMode()
{
    mode = (mode == GL_FILL ? GL_LINE : GL_FILL);

    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

/**
\brief Saves a screenshot of the current display to a file, ScreenShot###.jpg.

*/

void GraphicsEngine::screenshot()
{
    char ssfilename[100];
    sprintf(ssfilename, "ScreenShot%d.jpg", sscount);
    sf::Image img = capture();
    img.saveToFile(ssfilename);
    sscount++;
}

/**
\brief Handles the resizing events of the window.

*/

void GraphicsEngine::resize()
{
    glViewport(0, 0, getSize().x, getSize().y);
}

/**
\brief Sets the size of the rendering window.

\param width --- the width in pixels of the new size.

\param height --- the height in pixels of the new size.

*/

void GraphicsEngine::setSize(unsigned int width, unsigned int height)
{
    sf::RenderWindow::setSize(sf::Vector2u(width, height));
}
