#include "LineSeg.h"
#include <iostream>

void LineSeg::refresh()
{
    vert(pos1, color);
    vert(pos2, color);
}

void LineSeg::draw() const
{
    glLineWidth(2);
    Drawable::draw();
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
