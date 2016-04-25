#ifndef FREEFORMLINE_H
#define FREEFORMLINE_H

#include "Drawable.h"
#include "util/utils.h"
#include <vector>

class FreeformLine : public Drawable
{
    public:
        FreeformLine(glm::vec4 c);
        virtual ~FreeformLine();

        virtual bool contains(glm::vec2 point) override;

        void newSegment(glm::vec2 point);
        glm::vec2 currentPos();

        void refresh() override;
        GLuint getDrawMode() const override;

    protected:
    private:
        glm::vec4 color;
        std::vector<glm::vec2> points;
};

#endif // FREEFORMLINE_H