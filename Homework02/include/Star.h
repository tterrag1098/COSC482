#ifndef STAR_H
#define STAR_H

#include "Shape.h"

namespace lib
{

class Star : public Shape
{
public:
    Star(ColorRGB* color, int points);
    virtual ~Star();
private:
    int points;
    ColorRGB* color;
};

}
#endif // STAR_H
