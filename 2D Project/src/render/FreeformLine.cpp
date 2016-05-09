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
        if (onLine(points[i], points[i + 1], point, size))
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
            glm::vec2 verts[2];

            if (i == 0)
            {
                getPerpendicularEdge(points[i], points[i + 1], size, verts, true);

                vert(verts[0], color);
                vert(verts[1], color);
            }

            getPerpendicularEdge(points[i], points[i + 1], size, verts);

            vert(verts[0], color);
            vert(verts[1], color);
        }
    }
}

GLuint FreeformLine::getDrawMode() const
{
    return size < 1 && points.size() > 1 ? GL_LINE_STRIP : GL_TRIANGLE_STRIP;
}
