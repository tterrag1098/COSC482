#ifndef LINESEG_H
#define LINESEG_H

#include "Drawable.h"
#include "util/utils.h"

class LineSeg : public Drawable
{
    public:
        LineSeg(glm::vec2 p1 = {0, 0}, glm::vec2 p2 = {0, 0}, glm::vec4 col = BLACK) : Drawable(false), pos1(p1), pos2(p2), color(col) {};
        virtual ~LineSeg(){};

        void setPos2(glm::vec2 pos);
        void draw() const override;

    protected:
        glm::vec2 pos1, pos2;
        glm::vec4 color;

        virtual void refresh() override;
        virtual GLuint getDrawMode() const override;

    private:

};

#endif // LINESEG_H
