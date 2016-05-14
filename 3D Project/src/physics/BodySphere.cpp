#include "BodySphere.h"
#include "GraphicsEngine.h"

BodySphere::BodySphere(Material m, glm::dvec3 pos, float radius, double mass) : BodyDrawable(m, pos, radius, mass), model((new Models(m)))
{
    model->createSphereOBJ(radius, 30, 30);
    model->load();
}

BodySphere::~BodySphere() {}

void BodySphere::draw(GraphicsEngine *ge)
{
    ge->updateModelMat(getModelMat());
    model->draw(ge);
    BodyDrawable::draw(ge);
}
