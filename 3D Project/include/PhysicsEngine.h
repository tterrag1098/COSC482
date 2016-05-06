#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <vector>
#include <math.h>
#include <ctime>

#include <SFML/System/Clock.hpp>

#include "Body.h"

static const double G = 6.673e-11;

class PhysicsEngine
{
public:
    PhysicsEngine();
    virtual ~PhysicsEngine();

    void updateObjects();

    void addBody(Body *b);
protected:
private:
    sf::Clock clock;
    void applyForce(Body *b1, Body *b2);

    std::vector<Body*> bodies;
};

#endif // PHYSICSENGINE_H
