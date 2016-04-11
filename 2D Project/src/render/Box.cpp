#include "render/Box.h"

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

\version   1.3
\date      Written: 1/9/2016  <BR> Revised: 2/26/2016

*/

/**
\brief Constructor

\param c --- Position of the top left corner.

\param w --- The width of the box.

\param h --- The height of the box.

Creates a box object, loads the attributes, enables GLEW, generates the needed buffers
and IDs, and finally loads the object data up to the graphics card.

*/

Box::Box(glm::vec2 c, GLfloat w, GLfloat h, glm::vec4 col) : Drawable(true), corner(c), width(w), height(h), color(col) {}

/**
\brief Destructor

Clears the graphics memory used for the rectangle.

*/

Box::~Box()
{

}

/**
\brief Loads the box data to the graphics card.

Creates an array of vertex positions and colors from the data stored in the object,
creates an index array, allocates graphics memory for the arrays and loads the arrays
into graphics memory. Finally, it sets up pointers to the vertex and color data in
the two arrays.

*/

void Box::refresh()
{
    vert({corner.x, corner.y + height}, color);
    vert({corner.x + width, corner.y + height}, color);
    vert({corner.x + width, corner.y}, color);
    vert({corner.x, corner.y}, color);

    indices = {0, 3, 2, 0, 2, 1};
}

/**
\brief Checks if the box contains the given point.

Based on screen coordinates, not pixel coordinates.

\param p The point to check.
*/
bool Box::contains(glm::vec2 p)
{
    bool ret = p.x > corner.x && p.x < corner.x + width && p.y > corner.y && p.y < corner.y + height;
    return ret;
}

/**
\brief Resets the width of the box.

\param w --- The width of the box.

Resets the width of the box and then calls the data loading method.

*/

void Box::setWidth(GLfloat w)
{
    width = w;
    load();
}

/**
\brief Resets the height of the box.

\param h --- The height of the box.

Resets the height of the box and then calls the data loading method.

*/

void Box::setHeight(GLfloat h)
{
    height = h;
    load();
}

/**
\brief Resets the center of the box.

\param c --- Position of the center.

Resets the center of the box and then calls the data loading method.

*/

void Box::setCorner(glm::vec2 c)
{
    corner = c;
    load();
}

/**
\brief Changes the color of the box.

\param c The color to change to.

*/

void Box::setColor(glm::vec4 c)
{
    color = c;
    load();
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

glm::vec2 Box::getCorner()
{
    return corner;
}
