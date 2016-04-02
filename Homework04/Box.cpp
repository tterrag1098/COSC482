#include "Box.h"

/**
\file Box.cpp
\brief Simple rectangle object for drawing

Simple rectangle object with OpenGL data loading and drawing interfaces.  The data that
is being stored is a created in two separate arrays, one for vertices and the other for
color.  These blocks of data are transferred to a single array buffer on the graphics
card in two separate locations (that is the data is not intermixed) and hence we can
set up the reading pointers as having tightly packed data. There is also an index array
of 6 values {0, 3, 2, 0, 2, 1} that represent the vertices that will be drawn in two
triangles.  So one triangle will use vertices (0, 3, 2) and the other will use vertices
(0, 2, 1).

\author    Don Spickler, 
\version   1.3
\date      Written: 1/9/2016  <BR> Revised: 2/26/2016

*/

/**
\brief Constructor

\param c --- Position of the center.

\param w --- The width of the box.

\param h --- The height of the box.

Creates a box object, loads the attributes, enables GLEW, generates the needed buffers
and IDs, and finally loads the object data up to the graphics card.

*/

int Box::index_tracker = 1;

using namespace lib;

Box::Box(Point2D c, GLfloat w, GLfloat h)
{
    center = c;
    width = w;
    height = h;
    color = RED;

    // Turn on GLEW
    if (glewInit())
        std::cerr << "Unable to initialize GLEW." << std::endl;

    glGenVertexArrays(1, &BoxVAO);
    glGenBuffers(1, &ArrayBuffer);
    glGenBuffers(1, &BoxEBO);

    index = index_tracker;
    index_tracker++;

    LoadDataToGraphicsCard();
}

/**
\brief Destructor

Clears the graphics memory used for the rectangle.

*/

Box::~Box()
{
    glBindVertexArray(BoxVAO);
    glDeleteBuffers(1, &ArrayBuffer);
    glDeleteBuffers(1, &BoxEBO);
}

/**
\brief Loads the box data to the graphics card.

Creates an array of vertex positions and colors from the data stored in the object,
creates an index array, allocates graphics memory for the arrays and loads the arrays
into graphics memory. Finally, it sets up pointers to the vertex and color data in
the two arrays.

*/

void Box::LoadDataToGraphicsCard()
{
    vPosition = 0;
    vColor = 1;

    // Vertex and Color data for the box, using two triangles.

    GLfloat vertices[8];

    vertices[0] = center.x - width / 2;
    vertices[1] = center.y + height / 2;

    vertices[2] = center.x + width / 2;
    vertices[3] = center.y + height / 2;

    vertices[4] = center.x + width / 2;
    vertices[5] = center.y - height / 2;

    vertices[6] = center.x - width / 2;
    vertices[7] = center.y - height / 2;

    GLuint indices[6] = {0, 3, 2, 0, 2, 1};

    ColorRGB c = (hover ? RED : color);
    // Lazy solution
    ColorRGB colors[4] = {c, c, c, c};

    // Bind (turn on) a vertex array.
    glBindVertexArray(BoxVAO);

    // Load the indexing array on the graphics card.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BoxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Bind (turn on) the vertex buffer (storage location).
    glBindBuffer(GL_ARRAY_BUFFER, ArrayBuffer);

    // Allocate space for the vertex and color data. Do not load data at this point.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_DYNAMIC_DRAW);

    // Load the vertex data.
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    // Load the color data.
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);

    // Setup vertex data position information. Note that the 5th parameter is 0, indicating tightly packed.
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    // Setup color data position information. Note that the 5th parameter is 0, indicating tightly packed.
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)));

    // Set position indexes for shader streams.
    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vColor);
}

/**
\brief Checks if the box contains the given point.

Based on screen coordinates, not pixel coordinates.

\param p The point to check.
*/
bool Box::contains(Point2D p)
{
    float w = width / 2, h = height / 2;
    bool ret = p.x > center.x - w && p.x < center.x + w && p.y > center.y - h && p.y < center.y + h;
    return ret;
}

/**
\brief Tells this box to render like it's being hovered over.

Currently, this simply makes the box render solid red.

\param h The new boolean hover state.
*/
void Box::setHover(bool h)
{
    if (h != hover)
    {
        hover = h;
        LoadDataToGraphicsCard();
    }
}

/**
\brief Resets the width of the box.

\param w --- The width of the box.

Resets the width of the box and then calls the data loading method.

*/

void Box::setWidth(GLfloat w)
{
    width = w;
    LoadDataToGraphicsCard();
}

/**
\brief Resets the height of the box.

\param h --- The height of the box.

Resets the height of the box and then calls the data loading method.

*/

void Box::setHeight(GLfloat h)
{
    height = h;
    LoadDataToGraphicsCard();
}

/**
\brief Resets the center of the box.

\param c --- Position of the center.

Resets the center of the box and then calls the data loading method.

*/

void Box::setCenter(Point2D c)
{
    center = c;
    LoadDataToGraphicsCard();
}

/**
\brief Changes the color of the box.

\param c The color to change to.

*/

void Box::setColor(ColorRGB c)
{
    color = c;
    LoadDataToGraphicsCard();
}

/**
\brief Returns the width of the rectangle.

*/

GLfloat Box::getWidth()
{
    return width;
}

/**
\brief Returns the height of the rectangle.

*/

GLfloat Box::getHeight()
{
    return height;
}

/**
\brief Returns the center of the box.
*/

Point2D Box::getCenter()
{
    return center;
}

/**
\brief Draws the rectangle to the OpenGL window.

*/

void Box::draw()
{
    glBindVertexArray(BoxVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BoxEBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}
