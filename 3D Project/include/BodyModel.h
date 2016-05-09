#ifndef BODYMODEL_H
#define BODYMODEL_H

#include "BodyDrawable.h"
#include "../Models.h"

class BodyModel : public BodyDrawable
{
    public:
        BodyModel(Models *m, glm::dvec3 pos, double mass);
        virtual ~BodyModel();

        void draw(GraphicsEngine *ge) override;

    protected:
    private:
        Models *model;
};

#endif // BODYMODEL_H
