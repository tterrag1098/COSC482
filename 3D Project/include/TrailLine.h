#ifndef TRAILLINE_H
#define TRAILLINE_H

#include <deque>
#include <glm/glm.hpp>
#include "../Drawable.h"
#include <SFML/System/Clock.hpp>
#include "../MaterialPresets.h"

struct PathPoint {
    glm::dvec3 pos;
    long timestamp;
};

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
    static constexpr float PATH_TIMEOUT = 40000;

    sf::Clock clock;
    std::deque<PathPoint> path;
};

#endif // TRAILLINE_H
