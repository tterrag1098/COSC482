#include "LineSeg.h"
#include <iostream>

void LineSeg::refresh()
{
    vert(pos1, color);
    vert(pos2, color);
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
    return GL_LINES;
}
