#include "GraphicsEngine.h"

/**
\file GraphicsEngine.cpp
\brief Main graphics driver for the program.

This class extends sf::RenderWindow.

\author    Don Spickler, 
\version   1.2
\date      Written: 1/9/2016  <BR> Revised: 3/4/2016

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
    srand(time(0));

    clock.restart();

    // Turn on GLEW
    if (glewInit())
    {
        std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Create and load shaders.
    std::string vertShade =
        "#version 330 core\n"
        "layout(location = 0) in vec4 position;\n"
        "layout(location = 1) in vec4 icolor;\n"
        "out vec4 color;\n"
        "uniform mat4 Projection;\n"
        "void main()\n"
        "{\n"
        "    color = icolor;\n"
        "    gl_Position = Projection*position;\n"
        "}\n";

    std::string fragShade =
        "#version 330 core\n"
        "in  vec4 color;\n"
        "out vec4 fColor;\n"
        "void main()\n"
        "{\n"
        "    fColor = color;\n"
        "}\n";

    program = LoadShadersFromMemory(vertShade, fragShade);

    if (!program)
    {
        std::cerr << "Could not load Shader programs." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Find the location of the projection matrix.
    projLoc = glGetUniformLocation(program, "Projection");
    setProjectionMatrix();

    refresh();

    mode = GL_FILL;
    sscount = 1;

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

This function clears the screen and calls the draw functions of the bubbles.
It also handles animating the bubbles.

*/

void GraphicsEngine::display()
{
    // Clear the screen (Frame Buffer)
    glClear(GL_COLOR_BUFFER_BIT);

    int time = clock.getElapsedTime().asMilliseconds();
    bool tick = false;

    // 20 animation ticks per second
    float partialTick = time / 50.0f;
    if (time >= 50)
    {
        // If the tick took longer than expected (this happens often with vsync) print a warning
        if (time > 50)
        {
            std::cout << "Warning! tick took " << time << " millis!" << std::endl;
        }
        // Start a new tick timer
        clock.restart();
        // Do a full tick's worth of animation
        partialTick = 1;
        // Make sure to update the bubbles' real positions
        tick = true;
    }

    // Draw the objects.
    for (Bubble *s : bubbles)
    {
        // Base animation step off the bubble's position the previous tick
        lib::Point2D c = s->getCenterPrev();
        // Copy data for new position
        lib::Point2D newCenter = {c.x, c.y};
        sf::Vector2f *motion = s->getMotion();
        // Copy motion vector for interpolation
        sf::Vector2f m = *motion * partialTick;
        newCenter.x += m.x;
        newCenter.y += m.y;

        if(newCenter.x + s->getRadius() > screenBounds[1] || newCenter.x - s->getRadius() < screenBounds[0])
        {
            // Invert the "real" motion vector, then recalculate the interp vector
            motion->x = -motion->x;
            m = *motion * partialTick;
            // Send the bubble the other way
            newCenter.x += m.x * 2;
        }
        if(newCenter.y + s->getRadius() > screenBounds[3] || newCenter.y - s->getRadius() < screenBounds[2])
        {
            // Invert the "real" motion vector, then recalculate the interp vector
            motion->y = -motion->y;
            m = *motion * partialTick;
            // Send the bubble the other way
            newCenter.y += m.y * 2;
        }

        // Update the animation center (not previous center)
        s->setCenter(newCenter);
        s->draw();

        // If this is a full tick, update the bubble's "real" position
        if (tick)
        {
            s->tick();
        }
    }

    sf::RenderWindow::display();
}

/**

\brief Restarts the screen from scratch.

Clears all bubbles on the screen and recreates them using new random values.

*/

void GraphicsEngine::refresh()
{
    bubbles.clear();
    for (int i = 0; i < 20; i++)
    {
        float radius = (lib::rand_float() * 0.1f) + 0.1f;

        sf::Vector2f motion = {lib::rand_float() * 0.04f - 0.02f, lib::rand_float() * 0.04f - 0.02f};
        // ??? Not quite right but unsure how to fix
        lib::Point2D center = {(lib::rand_float() - (radius * 2) - 0.5f) + radius, (lib::rand_float() - (radius * 2) - 0.5f) + radius};
        lib::ColorRGB color = {lib::rand_float(), lib::rand_float(), lib::rand_float()};
        Bubble *b = new Bubble(motion, center, color, radius);
        bubbles.push_back(b);
    }
}

/**
\brief Saves a screenshot of the current display to a file, using the given extension.
i.e. ScreenShot###.[ext].

\param ext The extension to use for the saved image.
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
\brief Handles the resizing events of the window, and resets the projection matrix.

*/

void GraphicsEngine::resize()
{
    glViewport(0, 0, getSize().x, getSize().y);
    setProjectionMatrix();
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
\brief Calculates the aspect ratio projection matrix for the current screen size
and loads it into the shader.

The later portion of the method calculates the "screen coordinates".

Finally it assures that no bubbles have been clipped by the resize, and if some have been,
it moves their position inside the window. If any bubbles were moved, they are ticked and
the animation clock is reset (to avoid stutter).

*/

void GraphicsEngine::setProjectionMatrix()
{
    glUseProgram(program);

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

    // Go through each bubble and check for clipping
    for (Bubble *b : bubbles)
    {
        GLfloat r = b->getRadius();
        lib::Point2D c = b->getCenter();
        // If we are outside the X bounds, move the bubble to the nearest X border.
        if (c.x - r < screenBounds[0] || c.x + r > screenBounds[1])
        {
            float min = screenBounds[0] + r;
            float max = screenBounds[1] - r;
            b->setCenter({c.x < min ? min: max, c.y});
        }

        // If we are outside the Y bounds, move the bubble to the nearest Y border.
        if (c.y - r < screenBounds[2] || c.y + r > screenBounds[3])
        {
            float min = screenBounds[2] + r;
            float max = screenBounds[3] - r;
            b->setCenter({c.x, c.y < min ? min : max});
        }

        // Prevent animation motion clipping bubbles
        b->tick();
        clock.restart();
    }
}

/** \brief Returns an array of floats representing the screen bounds in the format [l, r, b, t]. */
GLfloat* GraphicsEngine::getScreenBounds()
{
    return screenBounds;
}
