#ifndef BODYDRAWABLE_H
#define BODYDRAWABLE_H

#include "Body.h"
#include "../Drawable.h"
#include "TrailLine.h"

class BodyDrawable : public Body, public Drawable
{
    public:
        BodyDrawable(Material mat, glm::dvec3 pos, double mass);
        virtual ~BodyDrawable();

        void applyForce(double tickDiff) override;

    protected:

        glm::mat4 getModelMat() override;
        GLuint getDrawMode() const override;

    private:
        TrailLine trail;
};

#endif // BODYDRAWABLE_H
