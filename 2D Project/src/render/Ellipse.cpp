#include "Ellipse.h"

Ellipse::Ellipse(glm::vec2 cent, int size, glm::vec4 c, bool f) : FreeformLine(size, c), center(cent), xRad(0), yRad(0), fill(f) {}

Ellipse::~Ellipse() {}

void Ellipse::refresh()
{
    const float incr = PI / 100;

    if (fill)
    {
        vert(center, color);
        for (float theta = 0; theta <= 2*PI; theta += incr)
        {
            vert(center + glm::vec2(xRad * std::cos(theta), yRad * std::sin(theta)), color);
        }
        vert(center + glm::vec2(xRad, 0), color);
    }
    else
    {
        points.clear();

        for (float theta = 0; theta <= 2*PI; theta += incr)
        {
            points.push_back(center + glm::vec2(xRad * std::cos(theta), yRad * std::sin(theta)));
        }

        // Make sure we close the loop
        points.push_back(center + glm::vec2(xRad, 0));
        points.push_back(center + glm::vec2(xRad * std::cos(incr), yRad * std::sin(incr)));

        FreeformLine::refresh();
    }
}

void Ellipse::setCenter(glm::vec2 c)
{
    center = c;
    load();
}

void Ellipse::setRadii(float x, float y)
{
    xRad = x;
    yRad = y;
    load();
}

GLuint Ellipse::getDrawMode() const
{
    return fill ? GL_TRIANGLE_FAN : FreeformLine::getDrawMode();
}
