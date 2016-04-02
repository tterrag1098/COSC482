#include "Shape.h"

namespace lib
{

Shape::Shape(){}

Shape::~Shape()
{
    delete verts;
}

std::vector<Vertex2D>* Shape::getVerts()
{
    return verts;
}

}
