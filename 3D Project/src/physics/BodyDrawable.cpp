#include "BodyDrawable.h"

BodyDrawable::BodyDrawable(std::string n, BodyType *t, glm::dvec3 pos, float radius, double mass) : Drawable(t->mat, false), Body(n, pos, radius, mass),
    type(t)
{
    children.push_back(&trail);
    light = -1;
}

BodyDrawable::~BodyDrawable() {}

void BodyDrawable::applyForce(double tickDiff)
{
    Body::applyForce(tickDiff);
    trail.update(pos);
}

glm::mat4 BodyDrawable::getModelMat() const
{
    auto mat = Drawable::getModelMat();
    glm::vec3 trans = glm::vec3(pos);
    mat = glm::translate(mat, trans);
    mat = glm::rotate(mat, 90.0f * degf, glm::vec3(-1, 0, 0));
    mat = glm::scale(mat, glm::vec3(-1, -1, -1));
    return mat;
}

void BodyDrawable::assignLight(GLuint lightID)
{
    light = lightID;
}

int BodyDrawable::getLight() const
{
    return light;
}

BodyType* BodyDrawable::getType() const
{
    return type;
}

void BodyDrawable::setType(BodyType* t)
{
    type = t;
    setMaterial(t->mat);
}
