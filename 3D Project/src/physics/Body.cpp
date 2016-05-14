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

float Body::getRadius() const
{
    return radius;
}

glm::vec3 Body::getPosF() const
{
    return glm::vec3(getPos());
}

glm::dvec3 Body::getPos() const
{
    return pos;
}

glm::dvec3 Body::getVelocity() const
{
    return vel;
}

void Body::setVelocity(glm::dvec3 v)
{
    vel = v;
}

glm::dvec3 Body::getForce() const
{
    return force;
}

double Body::getMass() const
{
    return mass;
}

void Body::updateForce(glm::vec3 f)
{
    force = f;
}
