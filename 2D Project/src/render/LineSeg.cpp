#include "LineSeg.h"
#include <iostream>

void LineSeg::refresh()
{
    if (size < 1)
    {
        vert(pos1, color);
        vert(pos2, color);
    }
    else
    {
        glm::vec2 verts[4];
        getPerpendicularEdge(pos1, pos2, size, verts, true);
        getPerpendicularEdge(pos1, pos2, size, verts + 2);

        vert(verts[0], color);
        vert(verts[1], color);
        vert(verts[2], color);
        vert(verts[3], color);
    }
}

void LineSeg::draw()
{
    Drawable::draw();
}

bool LineSeg::contains(glm::vec2 point)
{
    return onLine(pos1, pos2, point);
}

void LineSeg::setPos2(glm::vec2 pos)
{
    pos2 = pos;
    load();
}

GLuint LineSeg::getDrawMode() const
{
    return size < 1 ? GL_LINES : GL_TRIANGLE_STRIP;
}
