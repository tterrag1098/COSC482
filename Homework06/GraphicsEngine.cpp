#include "GraphicsEngine.h"

/**
\file GraphicsEngine.cpp
\brief Main graphics driver for the program.

This class extends sf::RenderWindow.

\author    
\version   1.3
\date      Written: 2/28/2016  <BR> Revised: 3/28/2016

*/

/**
\brief Constructor

\param title --- Title to be placed in the titlebar of the graphics window.

\param width --- The width (in pixels) of the graphics window.

\param height --- The height (in pixels) of the graphics window.

Creates rendering window, loads the shaders, and sets some initial data settings.

*/

GraphicsEngine::GraphicsEngine(std::string title, GLint width, GLint height) :
    sf::RenderWindow(sf::VideoMode(width, height),
                     title,
                     sf::Style::Default,
                     sf::ContextSettings(24, 8, 4, 3, 3))
{
    // Set the ball properties as defined in the spec
    balls[0].setPos({5, 5, 5})->setRadius(2);
    balls[1].setPos({-5, 5, -5})->setRadius(1);
    balls[2].setPos({-5, -5, -5})->setRadius(1.5f);
    balls[3].setPos({5, -5, 5})->setRadius(1.5f);
    balls[4].setPos({0, 0, 10})->setRadius(1);
    balls[5].setPos({0, 8, 0})->setRadius(1);
    balls[6].setPos({0, -6, 0})->setRadius(1);

    //  Load the shaders
    std::string vertShader =

    "#version 400 core\n"
    "layout(location = 0) in vec4 position;\n"
    "layout(location = 1) in vec4 icolor;\n"
    "uniform mat4 PVM;\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "    color = icolor;\n"
    "    gl_Position = PVM * position;\n"
    "}\n";

    std::string fragShader =

    "#version 330 core\n"
    "in  vec4 color;\n"
    "out vec4 fColor;\n"
    "void main()\n"
    "{\n"
    "    fColor = color;\n"
    "}\n";

    GLuint program = LoadShadersFromMemory(vertShader, fragShader);

    if (!program)
    {
        std::cerr << "Could not load Shader programs." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Turn on the shader & get location of transformation matrix.
    glUseProgram(program);
    PVMLoc = glGetUniformLocation(program, "PVM");

    // Initialize some data.
    mode = GL_FILL;
    sscount = 1;
    CameraNumber = 1;
    drawAxes = GL_TRUE;
    isPrespective = GL_TRUE;
    culling = GL_TRUE;

    // Set position of spherical camera
    sphcamera.setPosition(30, 30, 20);

    // Enable depth and cull face.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    if (SetVS)
    {
        setVerticalSyncEnabled(true);
        setFramerateLimit(60);
    }
    else
    {
        setVerticalSyncEnabled(false);
        setFramerateLimit(0);
    }

    // Make it the active window for OpenGL calls, resize to set projection matrix.
    setActive();
    resize();
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set view matrix via current camera.
    glm::mat4 view(1.0);
    if (CameraNumber == 1)
        view = sphcamera.lookAt();
    else if (CameraNumber == 2)
        view = yprcamera.lookAt();

    // Set axes scaling.
    glm::mat4 axesscale = glm::scale(glm::mat4(1.0), glm::vec3(10, 10, 10));

    // Load matrix product to shader.
    glUniformMatrix4fv(PVMLoc, 1, GL_FALSE, glm::value_ptr(projection*view*axesscale));

    if (drawAxes)
    {
        coords.draw();
    }

    // Preemptively convert to degrees
    float rot = animationCounter * degf;

    // Render each ball with the matrix defined by the spec
    renderBall(&balls[0], view, glm::vec3(0, 1, 0), rot);
    renderBall(&balls[1], view, glm::vec3(1, 1, 1), rot * 2);
    renderBall(&balls[2], view, glm::vec3(1, 0, 0), -rot * 3);
    renderBall(&balls[3], view, glm::vec3(0, 0, 1), -rot * 10);
    renderBall(&balls[4], view, glm::vec3(0, 0, 1), rot * 7, glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0, 1, 0)));
    renderBall(&balls[5], view, glm::vec3(0, 0, 1), rot * 7, glm::rotate(glm::mat4(1.0f), rot * 2, glm::vec3(1, 0, 0)));
    renderBall(&balls[6], view, glm::vec3(0, 0, 1), rot * 7, glm::rotate(glm::mat4(1.0f), rot * 3, glm::vec3(0, 0, 1)));

    // Increment the counter and wrap at 360 to avoid massive numbers causing precision issues
    animationCounter = (animationCounter + 1) % 360;

    sf::RenderWindow::display();
    printOpenGLErrors();
}

/**
\brief Draws a beach ball instance, using the given information.

\param ball The ball instance to draw.
\param view The current view matrix.
\param rot The rotation to apply (in degrees).
\param pre The matrix to use as a base. Defaults to the identity matrix.
*/
void GraphicsEngine::renderBall(BeachBall *ball, glm::mat4 view, glm::vec3 axis, float rot, glm::mat4 pre)
{
    auto model = glm::translate(pre, ball->getPos());
    model = glm::rotate(model, rot, axis);
    model = glm::translate(model, -ball->getPos());

    glUniformMatrix4fv(PVMLoc, 1, GL_FALSE, glm::value_ptr(projection * view * model));
    ball->draw();
}

/**
\brief Changes the fill and line mode being used.

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
\brief Toggles the front face between counterclockwise and clockwise.

*/

void GraphicsEngine::changeFrontFace()
{
    if (frontface == GL_CCW)
        frontface = GL_CW;
    else
        frontface = GL_CCW;

    glFrontFace(frontface);
}

/**
\brief Cycles the culling mode between front, back, and front and back.

*/

void GraphicsEngine::changeCullface()
{
    if (cullface == GL_FRONT)
        cullface = GL_BACK;
    else if (cullface == GL_BACK)
        cullface = GL_FRONT_AND_BACK;
    else
        cullface = GL_FRONT;

    glCullFace(cullface);
}

/**
\brief Toggles the culling.

*/

void GraphicsEngine::changeCulling()
{
    culling = !culling;
    if (culling)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);
}

/** \brief Toggles drawing the faces of the balls */
void GraphicsEngine::changeDrawFaces()
{
    drawFaces = !drawFaces;
    for (int i = 0; i < 7; i++)
    {
        balls[i].setDrawFaces(drawFaces);
    }
}

/** \brief Toggles drawing the borders of the balls */
void GraphicsEngine::changeDrawBorders()
{
    drawBorders = !drawBorders;
    for (int i = 0; i < 7; i++)
    {
        balls[i].setDrawBorder(drawBorders);
    }
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

/** \brief Sets perspective on or off. */
void GraphicsEngine::setPrespective(GLboolean b)
{
    isPrespective = b;
}

/** \brief Whether perspective is on or off. */
GLboolean GraphicsEngine::getPrespective()
{
    return isPrespective;
}

/** \brief Recalculates the perspective matrix. */
void GraphicsEngine::setProjectionMatrix()
{
    if (isPrespective)
        projection = glm::perspective(50.0f*degf, (float)getSize().x/getSize().y, 0.01f, 500.0f);
    else
    {
        if (getSize().y == 0 || getSize().x == 0)
            projection = glm::ortho(-1, 1, -1, 1, -1, 1);
        else if (getSize().x > getSize().y)
            projection = glm::ortho(-15.0f*(float)getSize().x/(float)getSize().y, 15.0f*(float)getSize().x/getSize().y, -15.0f, 15.0f, -200.0f, 200.0f);
        else
            projection = glm::ortho(-15.0f*(float)getSize().y/(float)getSize().x, 15.0f*(float)getSize().y/getSize().x, -15.0f, 15.0f, -200.0f, 200.0f);
    }
}


/**
\brief Handles the resizing events of the window.

Sets the viewport to the entire screen and recalculates the projection matrix.
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
\brief Returns a pointer to the spherical camera.

*/

SphericalCamera* GraphicsEngine::getSphericalCamera()
{
    return &sphcamera;
}

/**
\brief Returns a pointer to the yaw-pitch-roll camera.

*/

YPRCamera* GraphicsEngine::getYPRCamera()
{
    return &yprcamera;
}

/**
\brief Prints all OpenGL errors to stderr.

*/

void GraphicsEngine::printOpenGLErrors()
{
    GLenum errCode;
    const GLubyte *errString;

    while ((errCode = glGetError()) != GL_NO_ERROR)
    {
        errString = gluErrorString(errCode);

        fprintf(stderr, "OpenGL Error: %s\n", errString);
    }
}

/**
\brief Prints the glm matrix to the console window.  Remember that glm
matrices are column major.

\param m --- the glm matrix to be displayed.

*/

void GraphicsEngine::print_GLM_Matrix(glm::mat4 m)
{
    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
            printf("%7.2f", m[c][r]);

        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/**
\brief Returns true if the spherical camera is currently in use.

\return True if the spherical camera is currently in use and false otherwise.

*/

GLboolean GraphicsEngine::isSphericalCameraOn()
{
    return CameraNumber == 1;
}

/**
\brief Turns the spherical camera on.

*/

void GraphicsEngine::setSphericalCameraOn()
{
    CameraNumber = 1;
}

/**
\brief Returns true if the yaw-pitch-roll camera is currently in use.

\return True if the yaw-pitch-roll camera is currently in use and false otherwise.

*/

GLboolean GraphicsEngine::isYPRCameraOn()
{
    return CameraNumber == 2;
}

/**
\brief Turns the YPR camera on.

*/

void GraphicsEngine::setYPRCameraOn()
{
    CameraNumber = 2;
}

/**
\brief Sets the boolean to draw the axes or not.

\param b --- Draws the axes if true and not if false.

*/

void GraphicsEngine::setDrawAxes(GLboolean b)
{
    drawAxes = b;
}
