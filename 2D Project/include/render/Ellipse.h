#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "FreeformLine.h"
#include "glm/glm.hpp"

class Ellipse : public FreeformLine
{
    public:
        Ellipse(glm::vec2 center, int size, glm::vec4 color, bool fill = true);
        virtual ~Ellipse();

        void refresh() override;
        GLuint getDrawMode() const override;

        void setCenter(glm::vec2);
        void setRadii(float x, float y);

    protected:
    private:
        glm::vec2 center;
        int xRad, yRad;
        bool fill;
};

#endif // ELLIPSE_H
