#ifndef STAR_H
#define STAR_H

#include "Shape.h"

/**
\file Arrow.h
\brief Header file for Arrow.cpp.

\author    
\version   1.0
\date      Written: 2/16/2015 <BR> Revised: 2/16/2015
*/

namespace lib
{

/**
\class Arrow

\brief Defines an arrow shape to be drawn.
*/
class Arrow : public Shape
{
public:
    Arrow(int points = 0, float radius = 0.95f);
    virtual ~Arrow();
private:
    int points;
};

}
#endif // STAR_H
