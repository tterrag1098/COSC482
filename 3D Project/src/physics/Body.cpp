#include "Body.h"

BodyType *STAR = new BodyType{"Star"};
BodyType *EARTH = new BodyType{"Earth"};

BodyType *BARREN1 = new BodyType{"Barren Planet 1"};
BodyType *BARREN2 = new BodyType{"Barren Planet 2"};
BodyType *BARREN3 = new BodyType{"Barren Planet 3"};

BodyType *ALIEN1 = new BodyType{"Alien Planet 1"};
BodyType *ALIEN2 = new BodyType{"Alien Planet 2"};

BodyType *MOON = new BodyType{"Moon"};

const std::vector<BodyType*> ALL_BODY_TYPES = {STAR, EARTH, MOON, BARREN1, BARREN2, BARREN3, ALIEN1, ALIEN2};

Body::Body(std::string n, glm::dvec3 pos, float r, double m) : name(n), pos(pos), radius(r), mass(m)
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

std::string Body::getName() const
{
    return name;
}

void Body::setName(std::string n)
{
    name = n;
}

float Body::getRadius() const
{
    return radius;
}

void Body::setRadius(float r)
{
    radius = r;
}

glm::vec3 Body::getPosF() const
{
    return glm::vec3(getPos());
}

glm::dvec3 Body::getPos() const
{
    return pos;
}

void Body::setPosition(glm::dvec3 p)
{
    pos = p;
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

void Body::setMass(double m)
{
    mass = m;
}

void Body::updateForce(glm::vec3 f)
{
    force = f;
}
