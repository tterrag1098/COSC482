#include "GraphicsEngine.h"

/**
\file GraphicsEngine.cpp
\brief Main graphics driver for the program.

This class extends sf::RenderWindow.

\version   1.2
\date      Written: 1/9/2016  <BR> Revised: 1/9/2016

*/

GLuint GraphicsEngine::defaultShader = 0;

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
    texIdx = 1;

    // Turn on GLEW
    if (glewInit())
    {
        std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;
        exit(EXIT_FAILURE);
    }

    //  Load the shaders
    defaultShader = LoadShadersFromFile("AspectRatioVert.glsl", "PassThroughFrag.glsl");

    if (!defaultShader)
    {
        std::cerr << "Could not load Shader programs." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Turn on the shader & get location of transformation matrix.
    glUseProgram(defaultShader);
    useTextureLoc = glGetUniformLocation(defaultShader, "useTex");

    mode = GL_FILL;
    sscount = 1;

    if (SetVS)
        setVerticalSyncEnabled(true);
    else
        setFramerateLimit(0);

    clear(sf::Color::White);

    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Find the location of the projection matrix.
    projLoc = glGetUniformLocation(defaultShader, "Projection");
    setProjectionMatrix();

    // Make it the active window for OpenGL calls
    setActive();
    resize();
}

GLuint GraphicsEngine::loadTexture(std::string path)
{
    sf::Image texture;
    bool texloaded = texture.loadFromFile(path);

    if (!texloaded)
    {
        std::cerr << "Could not load texture." << std::endl;
        exit(EXIT_FAILURE);
    }

    GLuint texID;
    glGenTextures(1, &texID);
    glUniform1i(glGetUniformLocation(defaultShader, "tex"), 0);

//  Load the texture into texture memory.
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.getSize().x, texture.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.getPixelsPtr());
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texID;
}

void GraphicsEngine::activateTexture(int texId)
{
    if (texId >= 0)
    {
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(useTextureLoc, 1);
        glBindTexture(GL_TEXTURE_2D, texId);
    }
    else
    {
        glUniform1i(useTextureLoc, 0);
    }
}

/**
\brief Destructor

Currently empty, no allocated memory to clear.

*/

GraphicsEngine::~GraphicsEngine() {}

void GraphicsEngine::addObject(Drawable *obj, bool removable)
{
    obj->load();
    objects.push_back(obj);
    std::stable_sort(objects.begin(), objects.end(), [](const Drawable* a, const Drawable* b) { return a->sortIndex() < b->sortIndex(); });

    if (removable)
    {
        undoStack.push_back(obj);
        redoStack.clear();
    }
}

/**
\brief The function responsible for drawing to the OpenGL frame buffer.

This function clears the screen and calls the draw functions of the box and circle.

*/

void GraphicsEngine::display()
{
    // Clear the screen (Frame Buffer)
    glClear(GL_COLOR_BUFFER_BIT);

    //bg->draw();

    glLineWidth(2);
    glPointSize(3);

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

void GraphicsEngine::undo()
{
    if (!undoStack.empty())
    {
        objects.erase(std::find(objects.begin(), objects.end(), undoStack.back()));
        redoStack.push_back(undoStack.back());
        undoStack.pop_back();
    }
}

void GraphicsEngine::redo()
{
    if (!redoStack.empty())
    {
        Drawable *obj = redoStack.back();
        obj->load();
        objects.push_back(obj);
        std::stable_sort(objects.begin(), objects.end(), [](const Drawable* a, const Drawable* b) { return a->sortIndex() < b->sortIndex(); });
        redoStack.pop_back();
        undoStack.push_back(obj);
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

/**
\brief Handles the resizing events of the window.

*/

void GraphicsEngine::resize()
{
    glViewport(0, 0, getSize().x, getSize().y);

    for (Drawable *d : objects)
    {
        d->resized(getSize());
    }

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
    float w = getSize().x;
    float h = getSize().y;
    glm::mat4 ProjectionMatrix = glm::ortho(0.0f, w, h, 0.0f);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
}
