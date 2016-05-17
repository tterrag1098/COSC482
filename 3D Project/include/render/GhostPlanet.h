#ifndef GHOSTPLANET_H
#define GHOSTPLANET_H

#include "BodySphere.h"
#include "BodyProperties.h"
#include "LineSeg.h"

class GraphicsEngine;

class GhostPlanet : public BodySphere
{
    public:
        GhostPlanet();
        virtual ~GhostPlanet();

        void setProps(BodyProperties *props);

        void setVelocity(glm::dvec3 vel) override;

        void draw(GraphicsEngine *ge) override;

    protected:
    private:
        BodyProperties *props;
        LineSeg *velVec;
};

#endif // GHOSTPLANET_H
