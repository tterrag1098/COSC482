#include "GraphicsEngine.h"

/**
\file GraphicsEngine.cpp
\brief Main graphics driver for the program.

This class extends sf::RenderWindow.

\author    Don Spickler, 
\version   1.2
\date      Written: 1/9/2016  <BR> Revised: 2/26/2016

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

    std::string vert_shader =
        "#version 330 core\n"
        "layout(location = 0) in vec4 position;\n"
        "layout(location = 1) in vec4 icolor;\n"
        "out vec4 color;\n"
        "void main(){ color = icolor; gl_Position = position; }\n";

    std::string frag_shader =
        "#version 330 core\n"
        "in  vec4 color;\n"
        "out vec4 fColor;\n"
        "void main(){ fColor = color; }\n";

    //  Load the shaders
    GLuint program = LoadShadersFromMemory(vert_shader, frag_shader);

    if (!program)
    {
        std::cerr << "Could not load Shader programs." << std::endl;
        exit(EXIT_FAILURE);
    }

    mode = GL_FILL;
    sscount = 1;
    screenBounds[0] = -1;
    screenBounds[1] = 1;
    screenBounds[2] = -1;
    screenBounds[3] = 1;

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
\brief Adds a box to the screen.

Called by UI to add new boxes when the user right clicks.

Does nothing other than add the Box to the internal vector.

\param box A pointer to the Box to add.
*/
void GraphicsEngine::addBox(Box *box)
{
    boxes.push_back(box);
}

/**
\brief Removes a box from the screen

Called by the UI to delete boxes when the user ctrl right clicks.

\param Box a pointer to the Box to remove. Checks equality by pointer address, not contents, so will only remove the exact box passed.
*/
void GraphicsEngine::removeBox(Box *box)
{
    for (auto it = boxes.begin(); it != boxes.end();)
    {
        if (*(it) == box)
        {
            it = boxes.erase(it);
            Box::index_tracker--;
        }
        else
        {
            ++it;
        }
    }
}

/**
\brief Clears the screen of boxes.
*/
void GraphicsEngine::clear()
{
    boxes.clear();
    Box::index_tracker = 1;
}

/**
\brief The function responsible for drawing to the OpenGL frame buffer.

This function clears the screen and calls the draw functions of the box and circle.

*/

void GraphicsEngine::display()
{
    // Clear the screen (Frame Buffer)
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the objects.
    for (Box *b : boxes)
    {
        b->draw();
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
