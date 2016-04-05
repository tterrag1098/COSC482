#include "core/GraphicsEngine.h"

/**
\file GraphicsEngine.cpp
\brief Main graphics driver for the program.

This class extends sf::RenderWindow.

\version   1.2
\date      Written: 1/9/2016  <BR> Revised: 1/9/2016

*/

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
    GLuint program = LoadShadersFromFile("AspectRatioVert.glsl", "PassThroughFrag.glsl");

    if (!program)
    {
        std::cerr << "Could not load Shader programs." << std::endl;
        exit(EXIT_FAILURE);
    }

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

        // Find the location of the projection matrix.
    projLoc = glGetUniformLocation(program, "Projection");
    setProjectionMatrix();
}

/**
\brief Destructor

Currently empty, no allocated memory to clear.

*/

GraphicsEngine::~GraphicsEngine() {}

void GraphicsEngine::addObject(Drawable *obj)
{
    objects.push_back(obj);
}

/**
\brief The function responsible for drawing to the OpenGL frame buffer.

This function clears the screen and calls the draw functions of the box and circle.

*/

void GraphicsEngine::display()
{
    // Clear the screen (Frame Buffer)
    glClear(GL_COLOR_BUFFER_BIT);

    for (Drawable* obj : objects)
    {
        obj->draw();
    }

    sf::RenderWindow::display();
}

/**
\brief Changes the fill, line, and point mode being used.

*/

void GraphicsEngine::changeMode()
{
    if (mode == GL_FILL)
        mode = GL_LINE;
    else
        mode = GL_FILL;

    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

/**
\brief Saves a screenshot of the current display to a file, ScreenShot###.ext.

\param ext --- String holding the extension of the filename, and hence the image
data type.  The extension can be any extension of an SFML supported data type for
the saveToFile method of the sf;:Image class.

*/

void GraphicsEngine::screenshot(std::string ext)
{
    char ssfilename[100];
    sprintf(ssfilename, "ScreenShot%d.%s", sscount, ext.c_str());
    sf::Image img = capture();
    img.saveToFile(ssfilename);
    sscount++;
}

/**
\brief Saves a screenshot of the current display to a file, ScreenShot###.jpg.

*/

void GraphicsEngine::screenshotJPG()
{
    screenshot("jpg");
}

/**
\brief Saves a screenshot of the current display to a file, ScreenShot###.png.

*/

void GraphicsEngine::screenshotPNG()
{
    screenshot("png");
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

/**
\brief Returns a pointer to the screen bounds array.

*/

GLfloat* GraphicsEngine::getScreenBounds()
{
    return screenBounds;
}

/**
\brief Calculates the aspect ratio projection matrix for the current screen size
and loads it into the shader.

The later portion of the method calculates the "screen coordinates" and displays
them along with the projection matrix to the console window.

*/

void GraphicsEngine::setProjectionMatrix()
{
    glm::mat4 ProjectionMatrix = glm::mat4(1.0);

    if (getSize().x > getSize().y)
    {
        GLfloat aspratio = (GLfloat)getSize().x / getSize().y;
        ProjectionMatrix = glm::ortho(-aspratio, aspratio, -1.0f, 1.0f);
    }
    else
    {
        GLfloat aspratio = (GLfloat)getSize().y / getSize().x;
        ProjectionMatrix = glm::ortho(-1.0f, 1.0f, -aspratio, aspratio);
    }

    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));

    glm::mat4 inv = glm::inverse(ProjectionMatrix);
    glm::vec4 preImage = inv * glm::vec4(-1, 0, 0, 1);
    screenBounds[0] = preImage.x;
    preImage = inv * glm::vec4(1, 0, 0, 1);
    screenBounds[1] = preImage.x;
    preImage = inv * glm::vec4(0, -1, 0, 1);
    screenBounds[2] = preImage.y;
    preImage = inv * glm::vec4(0, 1, 0, 1);
    screenBounds[3] = preImage.y;
}
