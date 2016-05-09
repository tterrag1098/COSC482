#include "BodyDrawable.h"

BodyDrawable::BodyDrawable(Material mat, glm::dvec3 pos, double mass) : Drawable(mat, false), Body(pos, mass)
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

GLuint BodyDrawable::getDrawMode() const
{
    return GL_LINE_STRIP;
}
