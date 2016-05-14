#ifndef BODYDRAWABLE_H
#define BODYDRAWABLE_H

#include "Body.h"
#include "Drawable.h"
#include "TrailLine.h"

class BodyDrawable : public Body, public Drawable
{
public:
    BodyDrawable(Material mat, glm::dvec3 pos, float radius, double mass);
    virtual ~BodyDrawable();

    void applyForce(double tickDiff) override;
    int getLight() const;
    void assignLight(GLuint lightID);
protected:

    glm::mat4 getModelMat() const override;
    GLuint getDrawMode() const override;

private:
    TrailLine trail;
    int light;
};

#endif // BODYDRAWABLE_H
