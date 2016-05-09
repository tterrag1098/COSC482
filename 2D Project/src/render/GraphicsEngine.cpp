#include "GraphicsEngine.h"
#include "util/LoadShaders.h"
#include "Drawable.h"

/**
\file GraphicsEngine.cpp
\brief Main graphics driver for the program.

This class extends sf::RenderWindow.

\version   1.2
\date      Written: 1/9/2016  <BR> Revised: 1/9/2016

*/

GLuint GraphicsEngine::defaultShader = 0;
GLuint GraphicsEngine::fboShader = 0;
GLuint GraphicsEngine::fbo = 0;

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

    //  Load the shaders
    defaultShader = LoadShadersFromFile("AspectRatioVert.glsl", "PassThroughFrag.glsl");
    fboShader = LoadShadersFromFile("FBOPassthroughVert.glsl", "FBOPassthroughFrag.glsl");

    if (!defaultShader || !fboShader)
    {
        std::cerr << "Could not load Shader programs." << std::endl;
        exit(EXIT_FAILURE);
    }

    clear(sf::Color::White);

    glUseProgram(fboShader);

    glGenFramebuffers(1, &fbo);
    glGenTextures(1, &fboTex);
    glGenRenderbuffers(1, &rbo);

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fboTex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboTex, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, getSize().x, getSize().y);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glUniform1i(glGetUniformLocation(fboShader, "screenTex"), 0);

    glGenVertexArrays(1, &screenVao);
    GLuint buffer;
    glGenBuffers(1, &buffer);

    glBindVertexArray(screenVao);

    sf::Vector2u scr = getSize();
    glm::vec2 verts[6] = {{-1, -1}, {1, -1}, {-1, 1}, {-1, 1}, {1, -1}, {1, 1}};
    glm::vec2 uvs[6] = {{0, 0}, {1, 0}, {0, 1}, {0, 1}, {1, 0}, {1, 1}};

    int size = sizeof(glm::vec2) * 6;

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size * 2, NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, size, verts);
    glBufferSubData(GL_ARRAY_BUFFER, size, size, uvs);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(size));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Turn on GLEW
    if (glewInit())
    {
        std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Turn on the shader & get location of transformation matrix.
    glUseProgram(defaultShader);
    useTextureLoc = glGetUniformLocation(defaultShader, "useTex");

    mode = GL_FILL;
    sscount = 1;

    setFramerateLimit(120);

    glDisable(GL_MULTISAMPLE);
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
    glUniform1i(glGetUniformLocation(defaultShader, "tex"), 1);

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
        glActiveTexture(GL_TEXTURE0+1);
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

void GraphicsEngine::addUIElement(Drawable *obj)
{
    obj->load();
    guiElements.push_back(obj);
}

/**
\brief The function responsible for drawing to the OpenGL frame buffer.

This function clears the screen and calls the draw functions of the box and circle.

*/

void GraphicsEngine::display()
{
    // First pass
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClearColor(1, 1, 1, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We're not using stencil buffer now

    glUseProgram(defaultShader);

    for (Drawable* obj : objects)
    {
        obj->draw();
    }

    // Second pass
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(fboShader);
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(screenVao);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, fboTex);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glUseProgram(defaultShader);
    for (Drawable* obj : guiElements)
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
    for (Drawable *d : guiElements)
    {
        d->resized(getSize());
    }

    setProjectionMatrix();

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glBindTexture(GL_TEXTURE_2D, fboTex);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, getSize().x, getSize().y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, getSize().x, getSize().y);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR: Framebuffer is not complete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
