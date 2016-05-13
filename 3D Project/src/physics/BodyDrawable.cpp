#include "BodyDrawable.h"

BodyDrawable::BodyDrawable(Material mat, glm::dvec3 pos, float radius, double mass) : Drawable(mat, false), Body(pos, radius, mass)
{
    children.push_back(&trail);
}

BodyDrawable::~BodyDrawable() {}

void BodyDrawable::applyForce(double tickDiff)
{
    Body::applyForce(tickDiff);
    trail.update(pos);
}

glm::mat4 BodyDrawable::getModelMat()
{
    return glm::translate(Drawable::getModelMat(), glm::vec3(pos));
}

void BodyDrawable::assignLight(GLuint lightID)
{
    light = lightID;
}

int BodyDrawable::getLight() const
{
    return light;
}

GLuint BodyDrawable::getDrawMode() const
{
    return GL_LINE_STRIP;
}
