#include "PointBlob.h"

PointBlob::PointBlob(glm::vec4 c, std::vector<glm::vec2> points) : Drawable(false), color(c), points(points) {}

PointBlob::~PointBlob() {}

void PointBlob::refresh()
{
    for (glm::vec2 point : points)
    {
        vert(point, color);
    }
}

void PointBlob::addPoint(glm::vec2 p)
{
    points.push_back(p);
    load();
}

void PointBlob::addPoints(std::vector<glm::vec2> ps)
{
    for (glm::vec2 p : ps)
    {
        points.push_back(p);
    }
    load();
}

bool PointBlob::contains(glm::vec2 point)
{
    return std::find(points.begin(), points.end(), point) != points.end();
}

GLuint PointBlob::getDrawMode() const
{
    return GL_POINTS;
}
