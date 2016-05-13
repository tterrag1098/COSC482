#ifndef LINESEG_H
#define LINESEG_H

#include "Drawable.h"

class LineSeg : public Drawable
{
    public:
        LineSeg(glm::vec3 start, glm::vec3 endl);
        virtual ~LineSeg();

        void refresh() override;
        GLuint getDrawMode() const override;

    protected:
    private:
        glm::vec3 start, end;
};

#endif // LINESEG_H
