#include "Arrow.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>

/**
\file Arrow.cpp

\brief Contains the implementations for Arrow.h
*/

namespace lib
{

/** \return returns a random float value between 0 and 1. Does *not* call srand. */
float rand_float()
{
    return rand() / (static_cast <float> (RAND_MAX));
}

/**

\brief Constructs a new Arrow.

\param points The number of points the arrow will have along the center line. Cannot be less than 2.
\param radius The radius of the arrow, where 1.0f will have the arrow touch the edge of the screen.

*/
Arrow::Arrow(int points, float radius)
{
    if (points < 2)
    {
        throw std::bad_exception();
    }

    points--;

    float mid = -radius + 0.6f;

    // Set the rand seed so we get unique values
    srand(static_cast <unsigned> (time(0)));

    Vertex2D top;
    top.p.x = -radius;
    top.p.y = radius;

    Vertex2D bottom;
    bottom.p.x = -radius;
    bottom.p.y = -radius;

    for (int i = 0; i < points; i++)
    {
        float prog = mid + ((static_cast <float> (i) / points) * (radius - mid));
        float next = mid + ((static_cast <float> (i + 1) / points) * (radius - mid));

        // Each section needs 2 triangles, each with 3 vertices.
        Vertex2D varr[6];
        varr[0] = top;
        varr[3] = bottom;

        varr[1].p.x = varr[4].p.x = prog;
        varr[2].p.x = varr[5].p.x = next;

        for (int i = 0; i < 6; i++)
        {
            // Assign 3 random color values
            varr[i].c.r = rand_float();
            varr[i].c.g = rand_float();
            varr[i].c.b = rand_float();
        }

        verts.insert(std::end(verts), std::begin(varr), std::end(varr));
    }
}

/**
\brief Arrow destructor. Does nothing.
*/
Arrow::~Arrow() {}

}
