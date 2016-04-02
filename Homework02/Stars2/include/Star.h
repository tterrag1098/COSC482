#ifndef STAR_H
#define STAR_H

#include "Shape.h"

/**
\file Star.h
\brief Header file for Star.cpp.

\author    
\version   1.0
\date      Written: 2/16/2015 <BR> Revised: 2/16/2015
*/

namespace lib
{

/**
\class Star

\brief Defines a star shape to be drawn.
*/
class Star : public Shape
{
public:
    Star(const ColorRGB* color, int points, float radius);
    virtual ~Star();
private:
    int points;
    ColorRGB* color;
};

}
#endif // STAR_H
