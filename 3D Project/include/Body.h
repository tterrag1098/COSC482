#ifndef BODY_H
#define BODY_H

#include <glm/glm.hpp>

class Body
{
    public:
        Body(glm::dvec3 pos, float radius, double mass);
        virtual ~Body();

        void updatePosition(glm::dvec3 pos);

        float getRadius();
        glm::vec3 getPosF();
        glm::dvec3 getPos();
        glm::dvec3& getVelocity();
        glm::dvec3& getForce();

        void updateForce(glm::vec3 f);
        virtual void applyForce(double tickDiff);

        double getMass();

    protected:
        glm::dvec3 pos, vel, force;
        float radius;
        double mass;

    private:
};

#endif // BODY_H
