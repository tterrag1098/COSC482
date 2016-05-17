#include "BodySphere.h"
#include "GraphicsEngine.h"

BodySphere::BodySphere(std::string n, BodyType *t, glm::dvec3 pos, float radius, double mass) : BodyDrawable(n, t, pos, radius, mass), model((new Models(t->mat)))
{
    setRadius(radius);
}

BodySphere::~BodySphere() {}

void BodySphere::draw(GraphicsEngine *ge)
{
    if (!visible) return;

    ge->updateModelMat(getModelMat());
    ge->setFullbright(fullbright);
    model->draw(ge);
    BodyDrawable::draw(ge);
}

void BodySphere::setRadius(float r)
{
    Body::setRadius(r);

    model->createSphereOBJ(r, 30, 30);
    model->load();
}
