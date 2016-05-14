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

    void setSimulationSpeed(double speed);

    void pauseUnpause(); ///< Toggles the pause state;
    void setPaused(bool pause);
    bool isPaused() const;

    void addBody(Body *b);
    void removeBody(const Body *b);

protected:
private:
    double simSpeed = 1;
    bool paused = true;

    sf::Clock clock;
    void applyForce(Body *b1, Body *b2);

    std::vector<Body*> bodies;
};

#endif // PHYSICSENGINE_H
