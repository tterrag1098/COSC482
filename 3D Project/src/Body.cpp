#include "Body.h"

Body::Body(glm::dvec3 pos, double mass) : pos(pos), mass(mass)
{
}

Body::~Body()
{
    //dtor
}

void Body::applyForce(double tickDiff)
{
    vel += (tickDiff * force) / mass;
    pos += tickDiff * vel;
    force *= 0; // Clear out applied forces
}

glm::dvec3& Body::getPos()
{
    return pos;
}

glm::dvec3& Body::getVelocity()
{
    return vel;
}

glm::dvec3& Body::getForce()
{
    return force;
}

double Body::getMass()
{
    return mass;
}

void Body::updateForce(glm::vec3 f)
{
    force = f;
}
