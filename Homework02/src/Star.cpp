#include "Star.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <random>

namespace lib
{

Star::Star(ColorRGB* color, int points)
{
    float radius = 0.5f;
    float inner_radius = radius / 2.0f;
    for (int i = 0; i < points; i++)
    {
        float angle = (2 * i * PI) / points;
        float prev_half_angle = (2 * (i - 0.5f) * PI) / points;
        float next_half_angle = (2 * (i + 0.5f) * PI) / points;

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

        if (!color)
        {
            for (int i = 0; i < 6; i++)
            {
                varr[i].c.r = 1;
                varr[i].c.g = 1;
                varr[i].c.b = 1;
            }
        }

        verts.insert(std::end(verts), std::begin(varr), std::end(varr));
    }
}

Star::~Star() {}

}
