#ifndef POINTBLOB_H
#define POINTBLOB_H

#include <algorithm>

#include "Drawable.h"

class PointBlob : public Drawable
{
public:
    PointBlob(glm::vec4 c, std::vector<glm::vec2> points = {});
    virtual ~PointBlob();

    void refresh() override;
    bool contains(glm::vec2 point) override;

    void addPoint(glm::vec2 p);
    void addPoints(std::vector<glm::vec2> p);

protected:
    GLuint getDrawMode() const override;

private:
    std::vector<glm::vec2> points;
    glm::vec4 color;
};

#endif // POINTBLOB_H
