#include "Star.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>

/**
\file Star.cpp

\brief Contains the implementations for Star.h
*/

namespace lib
{

/** \return returns a random float value between 0 and 1. Does *not* call srand. */
float rand_float()
{
    return rand() / (static_cast <float> (RAND_MAX));
}

/**

\brief Constructs a new Star.

\param color A pointer to the color of the star. NULL to use random a random color for each vertex.
\param points The number of points the star will have
\param radius The radius of the star, where 1.0f will have the star touch the edge of the screen.

*/
Star::Star(const ColorRGB* color, int points, float radius)
{
    // The radius to use for the "inner" vertices
    float inner_radius = radius / 2.5f;
    // Set the rand seed so we get unique values
    srand(static_cast <unsigned> (time(0)));
    for (int i = 0; i < points; i++)
    {
        // Calculate angles of the vertices for this point.
        float angle = (2 * i * PI) / points;
        float prev_half_angle = (2 * (i - 0.5f) * PI) / points;
        float next_half_angle = (2 * (i + 0.5f) * PI) / points;

        // Each point needs 2 triangles, each with 3 vertices.
        Vertex2D varr[6];
        varr[0].p.x = radius * std::cos(angle);
        varr[0].p.y = radius * std::sin(angle);

        varr[1].p.x = inner_radius * std::cos(prev_half_angle);
        varr[1].p.y = inner_radius * std::sin(prev_half_angle);

        varr[2].p.x = varr[2].p.y = 0;

        varr[3] = varr[0];

        varr[4].p.x = inner_radius * std::cos(next_half_angle);
        varr[4].p.y = inner_radius * std::sin(next_half_angle);

        varr[5] = varr[2];

        for (int i = 0; i < 6; i++)
        {
            // If the color is null, assign 3 random values, otherwise use the passed color (dereferenced).
            if (!color)
            {
                varr[i].c.r = rand_float();
                varr[i].c.g = rand_float();
                varr[i].c.b = rand_float();
            }
            else
            {
                varr[i].c = *color;
            }
        }

        verts.insert(std::end(verts), std::begin(varr), std::end(varr));
    }
}

/**
\brief Star destructor. Does nothing.
*/
Star::~Star() {}

}
