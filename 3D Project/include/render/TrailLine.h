#ifndef TRAILLINE_H
#define TRAILLINE_H

#include "utils.h"
#include <deque>
#include <glm/glm.hpp>
#include "Drawable.h"
#include <SFML/System/Clock.hpp>

class TrailLine : public Drawable
{
public:
    TrailLine();
    virtual ~TrailLine();

    void update(glm::dvec3 pos);

    void refresh() override;
    GLuint getDrawMode() const override;

protected:
private:
    static constexpr int MAX_SEGMENTS = 500;

    glm::vec3 color;
    std::deque<glm::dvec3> path;
};

#endif // TRAILLINE_H
