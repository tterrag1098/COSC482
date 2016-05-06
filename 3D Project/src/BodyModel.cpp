#include "BodyModel.h"

BodyModel::BodyModel(Models *m, glm::dvec3 pos, double mass) : Body(pos, mass), model(m)
{
    children.push_back(model);
}

BodyModel::~BodyModel()
{
    //dtor
}

void BodyModel::draw(glm::mat4 pvm)
{
    glm::mat4 model = glm::translate(glm::mat4(1.0), glm::vec3(pos));
    glUniformMatrix4fv(GraphicsEngine::ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(GraphicsEngine::PVMLoc, 1, GL_FALSE, glm::value_ptr(pvm * model));

    glm::mat3 nM(model);
    nM = glm::transpose(glm::inverse(nM));
    glUniformMatrix3fv(GraphicsEngine::NormalLoc, 1, GL_FALSE, glm::value_ptr(nM));

    Drawable::draw(pvm);
}

void BodyModel::applyForce(double tickDiff)
{
    Body::applyForce(tickDiff);
}
