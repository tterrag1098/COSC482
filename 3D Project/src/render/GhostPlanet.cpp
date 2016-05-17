#include "GhostPlanet.h"

GhostPlanet::GhostPlanet() : BodySphere("Ghost", EARTH, {0, 0, 0}, 0, 0)
{
    fullbright = true;
    model->setColor(1, 1, 1, 0.25f);

    velVec = new LineSeg(pos, pos);
}

GhostPlanet::~GhostPlanet() {}

void GhostPlanet::setProps(BodyProperties *p)
{
    props = p;
}

void GhostPlanet::setVelocity(glm::dvec3 vel)
{
    BodySphere::setVelocity(vel);

    velVec->setStart(getPosF());
    velVec->setEnd(glm::vec3(getPos() + getVelocity()));
}

void GhostPlanet::draw(GraphicsEngine *ge)
{
    if (!visible) return;

    velVec->draw(ge);
    BodySphere::draw(ge);
}
