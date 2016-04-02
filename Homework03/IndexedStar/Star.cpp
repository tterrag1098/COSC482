#include "Star.h"
#include "utils.h"
#include <random>
#include <ctime>

using namespace lib;

/**
\file Star.cpp
\brief Simple star object for drawing

Simple star object with OpenGL data loading and drawing interfaces.  The vertex data that
is being stored is a single array of floats that represent the center vertex and then vertices
around the center, one vertex for each side with the first and last being the same vertex.
The colors are stored as (r, g, b) values in an array of floats, one set for each vertex.
These blocks of data are transferred to a single array buffer on the graphics card in two
separate locations (that is the data is not intermixed) and hence we can set up the reading
pointers as having tightly packed data.

\author    Don Spickler
\version   1.2
\date      Written: 1/11/2016  <BR> Revised: 1/12/2016

*/

/**
\brief Constructor

\param c --- Position of the center.

\param r --- Radius of the polygon.

\param p --- The number of points of the polygon.

Creates a polygon object, loads the attributes, enables GLEW, generates the needed buffers
and IDs, and finally loads the object data up to the graphics card.

*/

Star::Star(Point2D c, GLfloat r, GLint p)
{
    center = c;
    radius = r;
    points = p;
    color = new ColorRGB{1, 0, 0};

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

Star::~Star()
{
    glBindVertexArray(PolygonVAO);
    glDeleteBuffers(1, &ArrayBuffer);
    glDeleteBuffers(1, &PolygonEBO);

    delete color;
}

/**
\brief Loads the box data to the graphics card.

Creates an array of vertex positions and colors from the data stored in the object,
creates an index array, allocates graphics memory for the arrays and loads the arrays
into graphics memory.  Finally, it sets up pointers to the vertex and color data
positions in the array.

*/

void Star::LoadDataToGraphicsCard()
{
    vPosition = 0;
    vColor = 1;

    // Vertex and Color data for the box, using two triangles.

    // The radius to use for the "inner" vertices
    float inner_radius = radius / 2.5f;
    // Set the rand seed so we get unique values
    srand(static_cast <unsigned> (clock()));

    int num_verts = points * 2 + 1;
    Point2D verts[num_verts];
    ColorRGB colors[num_verts];
    verts[num_verts - 1] = center;
    if (color) colors[num_verts - 1] = *color;
    else colors[num_verts - 1] = {rand_float(), rand_float(), rand_float()};
    int idx = 0;
    for (int i = 0; i < points; i++, idx++)
    {
        // Calculate angles of the vertices for this point.
        float angle = (2 * i * PI) / points;

        // First loop, add outer points
        verts[idx].x = radius * std::cos(angle);
        verts[idx].y = radius * std::sin(angle);
        if (color) colors[idx] = *color;
        else colors[idx] = {rand_float(), rand_float(), rand_float()};
    }

    for (int i = 0; i < points; i++, idx++)
    {
        float half_angle = (2 * (i + 0.5f) * PI) / points;

        verts[idx].x = inner_radius * std::cos(half_angle);
        verts[idx].y = inner_radius * std::sin(half_angle);
        if (color) colors[idx] = *color;
        else colors[idx] = {rand_float(), rand_float(), rand_float()};
    }

    GLuint indices[points * 6];
    for (int i = 0; i < points; i++)
    {
        int p = i * 6;
        indices[p] = indices[p + 3] = num_verts - 1;
        indices[p + 2] = indices[p + 5] = i;

        indices[p + 1] = points + i;

        int ni = points + i - 1;
        if (ni < points)
        {
            // Wraparound
            indices[p + 4] = num_verts - 2;
        }
        else
        {
            indices[p + 4] = ni;
        }
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

/**
\brief Resets the radius of the polygon.

\param r --- The radius of the polygon.

Resets the radius and then calls the data loading method.

*/

void Star::setRadius(GLfloat r)
{
    radius = r;
    LoadDataToGraphicsCard();
}

/**
\brief Resets the number of points of the polygon.

\param r --- The number of points of the polygon.

Resets the number of points of the polygon and then calls the data loading method.

*/

void Star::setPoints(GLint s)
{
    points = s;
    LoadDataToGraphicsCard();
}

/**
\brief Resets the center of the polygon.

\param cx --- X position of the center.

\param cx --- Y position of the center.

Resets the center of the polygon and then calls the data loading method.

*/

void Star::setCenter(Point2D point)
{
    center = point;
    LoadDataToGraphicsCard();
}

/**
\brief Changes the color of the polygon.

\param r --- Red intensity for the polygon.

\param g --- Green intensity for the polygon.

\param b --- Blue intensity for the polygon.

Resets the color of the polygon to the new (r, g, b) value and calls the data loading method.

*/

void Star::setColor(ColorRGB* color)
{
    this->color = color;

    LoadDataToGraphicsCard();
}

ColorRGB* Star::getColor()
{
    return color;
}

/**
\brief Returns the radius of the polygon.

*/

GLfloat Star::getRadius()
{
    return radius;
}

/**
\brief Returns the number of points of the polygon.

*/

GLint Star::getPoints()
{
    return points;
}

/**
\brief Populates the array c with the (x, y) coordinates of the center.

The array c must have length at least two.

*/

void Star::getCenter(Point2D* c)
{
    c->x = center.x;
    c->y = center.y;
}

/**
\brief Draws the polygon to the OpenGL window.

*/

void Star::draw()
{
    glBindVertexArray(PolygonVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, PolygonEBO);
    glDrawElements(GL_TRIANGLE_FAN, points * 6, GL_UNSIGNED_INT, NULL);
}
