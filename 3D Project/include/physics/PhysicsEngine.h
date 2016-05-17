#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <vector>
#include <math.h>
#include <ctime>

#include <SFML/System/Clock.hpp>

#include "Body.h"

static const double G = 6.673e-11;

/**
\class PhysicsEngine

\brief Controlling object for physics calculations. Applies all gravitational forces to objects.

This class maintains a clock, which is used to determine the time delta since the last tick, as this class is called from the main draw method in GraphicsEngine.

Due to the fluctuating nature of FPS, the time delta is used to scale the forces when they are applied to objects, so that higher FPS does not result in larger forces.

The engine can be sped up, slowed down, and paused.
*/
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
    void applyForce(Body *b1, Body *b2); ///< Applies forces to both bodies, using Newton's 3rd Law for efficiency.

    std::vector<Body*> bodies;
};

#endif // PHYSICSENGINE_H
