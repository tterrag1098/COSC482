#include "Body.h"

Body::Body(glm::dvec3 pos, float r, double m) : pos(pos), radius(r), mass(m)
{
    vel = glm::dvec3(0);
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

float Body::getRadius()
{
    return radius;
}

glm::vec3 Body::getPosF()
{
    return glm::vec3(getPos());
}

glm::dvec3 Body::getPos()
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
