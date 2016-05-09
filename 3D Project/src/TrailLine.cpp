#include "TrailLine.h"

TrailLine::TrailLine() : Drawable(Materials::fullbright, false)
{
    clock.restart();
    useLighting = false;
    useTexture = false;
}

TrailLine::~TrailLine() {}

void TrailLine::update(glm::dvec3 pos)
{
    bool pathUpdated = false;

    if (path.empty() || glm::distance(path.front().pos, pos) > 0.1)
    {
        path.push_front({pos, clock.getElapsedTime().asMilliseconds()});
        pathUpdated = true;
    }

    while (!path.empty() && clock.getElapsedTime().asMilliseconds() - path.back().timestamp > PATH_TIMEOUT)
    {
        path.pop_back();
        pathUpdated = true;
    }

    if (pathUpdated)
    {
        load();
    }
}

void TrailLine::refresh()
{
    for (PathPoint p : path)
    {
        float age = (clock.getElapsedTime().asMilliseconds() - p.timestamp) / PATH_TIMEOUT;
        float a = 1 - (3 * age * age) + 2;
        a = std::min(1.0f, a);
        vert(glm::vec3(p.pos), glm::vec4(1, 1, 1, a));
    }
}

GLuint TrailLine::getDrawMode() const
{
    return GL_LINE_STRIP;
}
