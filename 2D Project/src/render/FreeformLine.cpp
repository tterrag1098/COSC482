#include "FreeformLine.h"

FreeformLine::FreeformLine(glm::vec4 c) : Drawable(false), color(c)
{
    //ctor
}

FreeformLine::~FreeformLine()
{
    //dtor
}

void FreeformLine::newSegment(glm::vec2 point)
{
    points.push_back(point);
    load();
}

bool FreeformLine::contains(glm::vec2 point)
{
    for (int i = 0; i < points.size() - 1; i++)
    {
        if (onLine(points[i], points[i + 1], point))
        {
            return true;
        }
    }
    return false;
}

glm::vec2 FreeformLine::currentPos()
{
    return points.back();
}

void FreeformLine::refresh()
{
    for (glm::vec2 p : points)
    {
        vert(p, color);
    }
}

GLuint FreeformLine::getDrawMode() const
{
    return points.size() > 1 ? GL_LINE_STRIP : GL_POINTS;
}
