#include "BodyModel.h"
#include "../GraphicsEngine.h"

BodyModel::BodyModel(Models *m, glm::dvec3 pos, double mass) : BodyDrawable(m->getMaterial(), pos, mass), model(m)
{
    model->load();
}

BodyModel::~BodyModel() {}

void BodyModel::draw(GraphicsEngine *ge)
{
    ge->updateModelMat(getModelMat());
    model->draw(ge);
    BodyDrawable::draw(ge);
}
