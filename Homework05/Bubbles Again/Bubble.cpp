#include "Bubble.h"
#include "utils.h"
#include <random>
#include <ctime>

using namespace lib;

/**
\file Bubble.cpp
\brief Simple bubble object for drawing

Simple bubble object with OpenGL data loading and drawing interfaces.  The vertex data that
is being stored is a single array of floats that represent the the vertices around the center,
one vertex for each side with the first and last being the same vertex. The colors are stored
as (r, g, b) values in an array, one set for each vertex. These blocks of data are
transferred to a single array buffer on the graphics card in two separate locations
(that is the data is not intermixed) and hence we can set up the reading pointers as having
tightly packed data.

\author    Don Spickler
\version   1.2
\date      Written: 1/11/2016  <BR> Revised: 1/12/2016

*/

/**
\brief Constructor

\param m --- Motion vector of the bubble.

\param c --- Position of the center of the bubble.

\param col --- Color of the bubble.

\param r --- Radius of the bubble.

Creates a bubble object, loads the attributes, enables GLEW, generates the needed buffers
and IDs, and finally loads the object data up to the graphics card.

*/

Bubble::Bubble(sf::Vector2f m, lib::Point2D c, lib::ColorRGB col, GLfloat r)
{
    motion = m;
    center = lastTickPos = c;
    radius = r;
    color = col;

    // Turn on GLEW
    if (glewInit())
        std::cerr << "Unable to initialize GLEW." << std::endl;

    glGenVertexArrays(1, &PolygonVAO);
    glGenBuffers(1, &ArrayBuffer);
    glGenBuffers(1, &PolygonEBO);

    LoadDataToGraphicsCard();
}

/**
\brief Destructor

Clears the graphics memory used for the rectangle.

*/

Bubble::~Bubble()
{
    glBindVertexArray(PolygonVAO);
    glDeleteBuffers(1, &ArrayBuffer);
    glDeleteBuffers(1, &PolygonEBO);
}

/**
\brief Loads the box data to the graphics card.

Creates an array of vertex positions and colors from the data stored in the object,
creates an index array, allocates graphics memory for the arrays and loads the arrays
into graphics memory.  Finally, it sets up pointers to the vertex and color data
positions in the array.

*/

void Bubble::LoadDataToGraphicsCard()
{
    vPosition = 0;
    vColor = 1;

    // Vertex and Color data for the box, using two triangles.

    // The radius to use for the "inner" vertices
    float inner_radius = radius / 2.5f;

    const int num_verts = 40;
    Point2D verts[num_verts];
    ColorRGB colors[num_verts];
    for (int i = 0; i < num_verts; i++)
    {
        // Calculate angles of the vertices for this point.
        float angle = (2 * i * PI) / num_verts;

        // First loop, add outer points
        verts[i].x = center.x + radius * std::sin(angle);
        verts[i].y = center.y + radius * std::cos(angle);
        colors[i] = color;
    }

    GLuint indices[num_verts];
    for (int i = 0; i < num_verts; i++)
    {
        indices[i] = i % num_verts;
    }

    // Bind (turn on) a vertex array.
    glBindVertexArray(PolygonVAO);

        // Load the indexing array on the graphics card.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, PolygonEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Bind (turn on) the vertex buffer (storage location).
    glBindBuffer(GL_ARRAY_BUFFER, ArrayBuffer);

    // Allocate space for the vertex and color data. Do not load data at this point.
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts) + sizeof(colors), NULL, GL_DYNAMIC_DRAW);

    // Load the vertex data.
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);

    // Load the color data.
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(verts), sizeof(colors), colors);

    // Setup vertex data position information. Note that the 5th parameter is 0, indicating tightly packed.
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    // Setup color data position information. Note that the 5th parameter is 0, indicating tightly packed.
    glVertexAttribPointer(vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(verts)));

    // Set position indexes for shader streams.
    glEnableVertexAttribArray(vPosition);
    glEnableVertexAttribArray(vColor);
}

/** \brief Returns the radius of the bubble. */
GLfloat Bubble::getRadius()
{
    return radius;
}

/** \brief Returns the center position of the bubble. */
Point2D Bubble::getCenter()
{
    return center;
}

/** \brief Returns the center position of the bubble on the previous tick. Used for animation. */
Point2D Bubble::getCenterPrev()
{
    return lastTickPos;
}

/** \brief Sets the center position of the bubble */
void Bubble::setCenter(Point2D c)
{
    center = c;
    LoadDataToGraphicsCard();
}

/** \brief Returns the motion vector of the bubble */
sf::Vector2f* Bubble::getMotion()
{
    return &motion;
}

/** \brief Updates the bubble's "real" position to its current animation position */
void Bubble::tick()
{
    lastTickPos = center;
}

/** \brief Draws the polygon to the OpenGL window. */
void Bubble::draw()
{
    glBindVertexArray(PolygonVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, PolygonEBO);
    glDrawElements(GL_LINE_LOOP, 40, GL_UNSIGNED_INT, NULL);
}
