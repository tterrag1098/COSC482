#include "PhysicsEngine.h"
#include <iostream>

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::addBody(Body *b)
{
    bodies.push_back(b);
}

void PhysicsEngine::updateObjects()
{
    if (firstTick)
    {
        clock.restart();
        firstTick = false;
        return;
    }

    for (int i = 0; i < bodies.size(); i++)
    {
        Body *b1 = bodies[i];
        for (int j = i + 1; j < bodies.size(); j++)
        {
            Body *b2 = bodies[j];
            applyForce(b1, b2);
        }
    }
    double time = clock.getElapsedTime().asMilliseconds() / 1000.0;
    for (Body *b : bodies)
    {
        b->applyForce(time);
    }
    clock.restart();
}

void PhysicsEngine::applyForce(Body *b1, Body *b2)
{
    double EPS = 10;      // softening parameter (just to avoid infinities)
    double fScale = 1000;
    glm::dvec3 p1 = b1->getPos();
    glm::dvec3 p2 = b2->getPos();

    double dist = glm::distance(p1, p2);

    double fmag = (G * b1->getMass() * b2->getMass()) / (dist * dist + EPS * EPS);
    fmag *= fScale;

    glm::dvec3 f1 = b1->getForce();
    glm::dvec3 f2 = b2->getForce();

    glm::dvec3 f = (p2 - p1) / dist;
    f *= fmag;

    f1 += f;
    f2 -= f;

    b1->updateForce(f1);
    b2->updateForce(f2);
}
