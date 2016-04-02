#include "GraphicsEngine.h"

/**
\file GraphicsEngine.cpp
\brief Main graphics driver for the program.

This class extends sf::RenderWindow.

\author    , 
\version   1.0
\date      Written: 2/12/2016  <BR> Revised: 2/12/2016

*/

/**
\brief Constructor

\param title --- Title to be placed in the titlebar of the graphics window.

Creates rendering window and enables GLEW.

*/

GraphicsEngine::GraphicsEngine(string title) :
    sf::RenderWindow(sf::VideoMode(600, 600),
                     title,
                     sf::Style::Default,
                     sf::ContextSettings(24, 8, 4, 3, 3))
{
    setVerticalSyncEnabled(true);
    sscount = 1;

    VAOs = NULL;
    Buffers = NULL;

    // Make it the active window for OpenGL calls
    setActive();

    // Turn on GLEW
    if (glewInit())
    {
        cerr << "Unable to initialize GLEW ... exiting" << endl;
        exit(EXIT_FAILURE);
    }
}

/**
\brief Destructor

Deletes the VAO and Buffers address arrays.

*/

GraphicsEngine::~GraphicsEngine()
{
    if (VAOs != NULL)
        delete VAOs;

    if (Buffers != NULL)
        delete Buffers;
}

/**
\brief The initialization function.

This function loads vertex and color data to the graphics card, loads the
shader programs from the disk to the graphics card, and links the data
stream to the vertex/color data.

*/

void GraphicsEngine::init()
{
    Triangles = 0;
    NumVAOs = 1;
    ArrayBuffer = 0;
    NumBuffers = 1;
    mode = GL_FILL;
    vPosition = 0;
    vColor = 1;

    VAOs = new GLuint[NumVAOs];
    Buffers = new GLuint[NumBuffers];

    // Generate and bind (turn on) a vertex array.
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);

    // Generate and bind (turn on) a buffer (storage location).
    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);

    // The master list of all vertices
    std::vector<lib::Vertex2D> vertices;

    // For each drawable, add all its vertices into the master list
    for (lib::Drawable* d : todraw)
    {
        vertices.insert(vertices.end(), d->verts.begin(), d->verts.end());
    }

    NumVertices = vertices.size();

    std::cout << "Loaded " << NumVertices << " vertices from Drawable objects." << std::endl;

    // Transfer the vertex information to the buffer.
    // Note the use of &vertices[0] rather than &vertices. vectors may have data before the actual array.
    glBufferData(GL_ARRAY_BUFFER, sizeof(lib::Vertex2D) * NumVertices, &vertices[0], GL_STATIC_DRAW);

    // Setup vertex data position information.
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, sizeof(lib::Vertex2D), BUFFER_OFFSET(0));

    // Setup color data position information.
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_TRUE, sizeof(lib::Vertex2D), BUFFER_OFFSET(sizeof(lib::Point2D)));

    // Set position indexes for shader streams.
    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vColor);

    //  Load the shaders
    GLuint program = LoadShadersFromFile("PassThroughVert.glsl", "PassThroughFrag.glsl");

    if (!program)
    {
        cerr << "Could not load Shader programs." << endl;
        exit(EXIT_FAILURE);
    }

    glUseProgram(program);
}

/**
\brief The function responsible for drawing to the OpenGL frame buffer.

This function clears the screen, binds the vertex array containing the
vertex/color data and then draws the array.

*/

void GraphicsEngine::display()
{
    // Clear the screen (Frame Buffer)
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the triangles.
    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    sf::RenderWindow::display();
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

/**
\brief Adds a Drawable object to the engine.

\param drawable A pointer to the object to add, and subsequently draw when display() is called.
*/
void GraphicsEngine::add(lib::Drawable* drawable)
{
    todraw.push_back(drawable);
}
