#ifndef BODY_H
#define BODY_H

#include <glm/glm.hpp>

class Body
{
    public:
        Body(glm::dvec3 pos, float radius, double mass);
        virtual ~Body();

        void updatePosition(glm::dvec3 pos);

        float getRadius() const;
        void setRadius(float r);

        double getMass() const;
        void setMass(double m);

        glm::vec3 getPosF() const;
        glm::dvec3 getPos() const;

        glm::dvec3 getVelocity() const;
        void setVelocity(glm::dvec3 vel);

        glm::dvec3 getForce() const;

        void updateForce(glm::vec3 f);
        virtual void applyForce(double tickDiff);

    protected:
        glm::dvec3 pos, vel, force;
        float radius;
        double mass;

    private:
};

#endif // BODY_H
