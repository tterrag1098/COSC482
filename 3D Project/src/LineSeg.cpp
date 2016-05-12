#include "LineSeg.h"
#include "../MaterialPresets.h"
#include "../utils.h"

LineSeg::LineSeg(glm::vec3 s, glm::vec3 e) : Drawable(Materials::fullbright, false), start(s), end(e) {}

LineSeg::~LineSeg() {}

void LineSeg::refresh()
{
    vert(start, WHITE);
    vert(end, WHITE);
}

GLuint LineSeg::getDrawMode() const
{
    return GL_LINES;
}
