#include "FreeformLine.h"
#include "util/utils.h"

FreeformLine::FreeformLine(int size, glm::vec4 c) : Drawable(false), size(size / 2.0f), color(c)
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
    if (points.size() == 0)
    {
        return;
    }
    else if (points.size() == 1)
    {
        glm::vec2 p = points[0];
        vert(p + glm::vec2(size, -size), color);
        vert(p + glm::vec2(size, size), color);
        vert(p + glm::vec2(-size, -size), color);
        vert(p + glm::vec2(-size, size), color);
        return;
    }

    if (size < 1)
    {
        for (glm::vec2 p : points)
        {
            vert(p, color);
        }
    }
    else
    {
        for (int i = 0; i < points.size() - 1; i++)
        {
            glm::vec2 p1 = points[i];
            glm::vec2 p2 = points[i + 1];
            glm::vec2 diff = glm::normalize(p2 - p1) * size;
            glm::vec2 lOff = glm::mat2(0, -1, 1, 0) * diff;
            glm::vec2 rOff = glm::mat2(0, 1, -1, 0) * diff;

            if (i == 0)
            {
                vert(p1 + lOff, color);
                vert(p1 + rOff, color);
            }
            vert(p2 + lOff, color);
            vert(p2 + rOff, color);
        }
    }
}

GLuint FreeformLine::getDrawMode() const
{
    return size < 1 && points.size() > 1 ? GL_LINE_STRIP : GL_TRIANGLE_STRIP;
}
