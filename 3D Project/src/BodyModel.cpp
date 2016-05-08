#include "BodyModel.h"

BodyModel::BodyModel(Models *m, glm::dvec3 pos, double mass) : Drawable(m->getMaterial()), Body(pos, mass), model(m)
{
    children.push_back(model);
}

BodyModel::~BodyModel()
{
    //dtor
}

void BodyModel::draw(glm::mat4 pvm)
{
    Drawable::draw(pvm);
}

void BodyModel::applyForce(double tickDiff)
{
    Body::applyForce(tickDiff);
}

glm::mat4 BodyModel::getModelMat()
{
    return glm::translate(Drawable::getModelMat(), glm::vec3(pos));
}
