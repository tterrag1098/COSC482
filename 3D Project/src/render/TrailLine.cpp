#include "TrailLine.h"

TrailLine::TrailLine() : Drawable(Materials::fullbright, false)
{
    useLighting = false;
    useTexture = false;
    color = to_rgb({rand_float(), 0.7f, 1, 1}).rgb();
}

TrailLine::~TrailLine() {}

void TrailLine::update(glm::dvec3 pos)
{
    bool pathUpdated = false;

    if (path.empty() || glm::distance(path.front(), pos) > 0.1)
    {
        path.push_front(pos);
        pathUpdated = true;
    }

    while (!path.empty() && path.size() > MAX_SEGMENTS)
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
    for (int i = 0; i < path.size(); i++)
    {
        float age = (float) i / MAX_SEGMENTS;
        float fadein = i / 40.0f;
        float a = fadein <= 1.0f ? ((fadein + 1) * (fadein + 1)) - 1 : 1 - (3 * age * age) + 2;
        a = std::min(1.0f, a);
        vert(glm::vec3(path[i]), glm::vec4(color, a));
    }
}

GLuint TrailLine::getDrawMode() const
{
    return GL_LINE_STRIP;
}
