#ifndef DRAWABLE_H_INCLUDED
#define DRAWABLE_H_INCLUDED

#define PI 3.1415927f
#include "structs.h"
#include <vector>

/**
\file Drawable.h

\brief Defines an abstract class for all drawable objects
*/

namespace lib
{

/**
\class Drawable

\brief Base class for any object that can be drawn. GraphicsEngine maintains a list of this type of object.
*/
class Drawable
{
public:
    std::vector<Vertex2D> verts; ///< The vertices of the object
};

}

#endif // DRAWABLE_H_INCLUDED
