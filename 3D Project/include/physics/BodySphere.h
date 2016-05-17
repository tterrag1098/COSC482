#ifndef BODYMODEL_H
#define BODYMODEL_H

#include "BodyDrawable.h"
#include "Models.h"

class BodySphere : public BodyDrawable
{
    public:
        BodySphere(std::string name, BodyType *t, glm::dvec3 pos, float radius, double mass);
        virtual ~BodySphere();

        void draw(GraphicsEngine *ge) override;

        void setRadius(float r) override;

    protected:
        Models *model;
    private:
};

#endif // BODYMODEL_H
