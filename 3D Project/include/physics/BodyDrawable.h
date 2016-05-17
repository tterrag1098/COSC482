#ifndef BODYDRAWABLE_H
#define BODYDRAWABLE_H

#include "Body.h"
#include "Drawable.h"
#include "TrailLine.h"

class BodyDrawable : public Body, public Drawable
{
public:
    BodyDrawable(std::string name, BodyType *type, glm::dvec3 pos, float radius, double mass);
    virtual ~BodyDrawable();

    void applyForce(double tickDiff) override;
    int getLight() const;
    void assignLight(GLuint lightID);

    BodyType* getType() const;
    void setType(BodyType *t);

protected:

    glm::mat4 getModelMat() const override;

private:
    TrailLine trail;
    int light;
    BodyType* type;
};

#endif // BODYDRAWABLE_H
