#ifndef BODYMODEL_H
#define BODYMODEL_H

#include "Body.h"
#include "../GraphicsEngine.h"
#include "../Models.h"
#include "../Drawable.h"

class BodyModel : public Body, public Drawable
{
    public:
        BodyModel(Models *m, glm::dvec3 pos, double mass);
        virtual ~BodyModel();

        void draw(glm::mat4 pvm) override;
        void applyForce(double tickDiff) override;

    protected:
    private:
        Models *model;
};

#endif // BODYMODEL_H
