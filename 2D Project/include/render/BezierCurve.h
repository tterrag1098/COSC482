#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include "FreeformLine.h"
#include <glm/glm.hpp>

class BezierCurve : public FreeformLine
{
    public:
        BezierCurve(int thickness, glm::vec2 start, glm::vec4 color);
        virtual ~BezierCurve();

        void refresh() override;

        void setControl(glm::vec2 c);
        void setEnd(glm::vec2 e);

    protected:
    private:
        glm::vec2 start, end;
        glm::vec2 control;
};

#endif // BEZIERCURVE_H
