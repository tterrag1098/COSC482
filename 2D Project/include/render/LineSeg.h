#ifndef LINESEG_H
#define LINESEG_H

#include "Drawable.h"
#include "util/utils.h"

class LineSeg : public Drawable
{
    public:
        LineSeg(int size, glm::vec2 p1 = {0, 0}, glm::vec2 p2 = {0, 0}, glm::vec4 col = BLACK) : Drawable(false), size(size/2.0f), pos1(p1), pos2(p2), color(col) {};
        virtual ~LineSeg(){};

        virtual bool contains(glm::vec2 point) override;

        void setPos2(glm::vec2 pos);
        void draw() override;

    protected:
        float size;
        glm::vec2 pos1, pos2;
        glm::vec4 color;

        virtual void refresh() override;
        virtual GLuint getDrawMode() const override;

    private:

};

#endif // LINESEG_H
