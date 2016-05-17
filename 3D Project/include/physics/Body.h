#ifndef BODY_H
#define BODY_H

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "Material.h"

/**
\struct BodyType

\brief Basic information about the type of the body. Contains a name and a Material.
*/
struct BodyType
{
    std::string name;
    Material mat;
};

inline std::ostream& operator<<(std::ostream &strm, const BodyType &type)
{
    return strm << type.name;
}

inline bool operator==(const BodyType& lhs, const BodyType& rhs)
{
    return lhs.name == rhs.name;
}

extern BodyType *STAR;
extern BodyType *EARTH;
extern BodyType *ALIEN1, *ALIEN2;
extern BodyType *BARREN1, *BARREN2, *BARREN3;
extern BodyType *MOON;

extern const std::vector<BodyType*> ALL_BODY_TYPES;

/**
\class Body

\brief Base class for all physics objects. Contains all the necessary methods to apply forces to an object, and accessors/mutators for the body's data.
*/
class Body
{
    public:
        Body(std::string name, glm::dvec3 pos, float radius, double mass);
        virtual ~Body();

        std::string getName() const;
        void setName(std::string name);

        float getRadius() const;
        virtual void setRadius(float r);

        double getMass() const;
        void setMass(double m);

        glm::vec3 getPosF() const;
        glm::dvec3 getPos() const;
        void setPosition(glm::dvec3 pos);

        glm::dvec3 getVelocity() const;
        virtual void setVelocity(glm::dvec3 vel);

        glm::dvec3 getForce() const;

        void updateForce(glm::vec3 f);              ///< Updates the current forces accumulated on the body.
        virtual void applyForce(double tickDiff);   ///< Updates the position based on the current forces, and clears the applied forces.

    protected:
        std::string name;
        glm::dvec3 pos, vel, force;
        float radius;
        double mass;

    private:
};

inline std::ostream& operator<<(std::ostream &strm, const Body &body)
{
    return strm << body.getName();
}

#endif // BODY_H
