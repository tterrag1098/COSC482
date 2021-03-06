#include "PhysicsEngine.h"
#include <iostream>
#include <algorithm>

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

void PhysicsEngine::removeBody(const Body *b)
{
    bodies.erase(std::find(bodies.begin(), bodies.end(), b));
}

void PhysicsEngine::setSimulationSpeed(double speed)
{
    simSpeed = speed;
}

void PhysicsEngine::pauseUnpause()
{
    setPaused(!isPaused());
}

void PhysicsEngine::setPaused(bool pause)
{
    paused = pause;
}

bool PhysicsEngine::isPaused() const
{
    return paused;
}

void PhysicsEngine::updateObjects()
{
    if (paused)
    {
        clock.restart();
        return;
    }

    for (int i = 0; i < bodies.size(); i++)
    {
        Body *b1 = bodies[i];
        // We do not need to apply forces in reverse, this is handled by applyForce.
        // So we start iteration at the next body.
        for (int j = i + 1; j < bodies.size(); j++)
        {
            Body *b2 = bodies[j];
            applyForce(b1, b2);
        }
    }

    // The base timescale is 1 second, so divide by 1000, factoring in simulation speed.
    double time = clock.getElapsedTime().asMilliseconds() / (1000 / simSpeed);
    for (Body *b : bodies)
    {
        b->applyForce(time);
    }
    clock.restart();
}

void PhysicsEngine::applyForce(Body *b1, Body *b2)
{
    const double EPS = 10;      // softening parameter (just to avoid infinities)
    const double mScale = 1000; // All masses scaled up by 1000
    const double rScale = 1000; // All distances scaled up by 1000

    glm::dvec3 p1 = b1->getPos();
    glm::dvec3 p2 = b2->getPos();

    double dist = glm::distance(p1, p2);

    // Apply Newtonian gravity
    double fmag = (G * b1->getMass() * b2->getMass() * mScale) / (dist * dist * rScale + EPS * EPS);

    glm::dvec3 f1 = b1->getForce();
    glm::dvec3 f2 = b2->getForce();

    // Calculate direction vector of the gravitational force
    glm::dvec3 f = (p2 - p1) / dist;
    // Apply the force to this direction vector
    f *= fmag;

    // Equal and opposite reactions!
    f1 += f;
    f2 -= f;

    b1->updateForce(f1);
    b2->updateForce(f2);
}
