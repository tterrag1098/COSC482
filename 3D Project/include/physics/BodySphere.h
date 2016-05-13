#ifndef BODYMODEL_H
#define BODYMODEL_H

#include "BodyDrawable.h"
#include "Models.h"

class BodySphere : public BodyDrawable
{
    public:
        BodySphere(Material m, glm::dvec3 pos, float radius, double mass);
        virtual ~BodySphere();

        void draw(GraphicsEngine *ge) override;

    protected:
    private:
        Models *model;
};

#endif // BODYMODEL_H
