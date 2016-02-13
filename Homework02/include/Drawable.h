#ifndef DRAWABLE_H_INCLUDED
#define DRAWABLE_H_INCLUDED

#define PI 3.1415927f
#include "structs.h"
#include <vector>

namespace lib
{
class Drawable
{
public:
    std::vector<Vertex2D> verts;
};
}


#endif // DRAWABLE_H_INCLUDED
