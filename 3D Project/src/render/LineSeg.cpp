#include "LineSeg.h"
#include "utils.h"

LineSeg::LineSeg(glm::vec3 s, glm::vec3 e) : Drawable(Material(), false), start(s), end(e)
{
    useLighting = false;
}

LineSeg::~LineSeg() {}

void LineSeg::refresh()
{
    vert(start, WHITE);
    vert(end, WHITE);
}

void LineSeg::setStart(glm::vec3 s)
{
    start = s;
    load();
}

void LineSeg::setEnd(glm::vec3 e)
{
    end = e;
    load();
}

GLuint LineSeg::getDrawMode() const
{
    return GL_LINES;
}
