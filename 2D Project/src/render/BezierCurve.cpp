#include "BezierCurve.h"
#include "util/utils.h"

BezierCurve::BezierCurve(int thickness, glm::vec2 s, glm::vec4 c) : FreeformLine(thickness, c), start(s) {}

BezierCurve::~BezierCurve() {}

void BezierCurve::setControl(glm::vec2 c)
{
    control = c;
    load();
}

void BezierCurve::setEnd(glm::vec2 e)
{
    end = e;
    load();
}

void BezierCurve::refresh()
{
    points.clear();
    for (float t = 0; t <= 1; t += 0.01f)
    {
        float t2 = t * t;
        float mt = 1 - t;
        float mt2 = mt * mt;
        // Quadratic Bezier formula: (1 - t)^2 + 2*(1 - t)*t + t^2
        points.push_back(start * mt2 + control * 2.0f * mt * t + end * t2);
    }
    FreeformLine::refresh();
}
