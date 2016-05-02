#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "GL/glew.h"
#include <random>
#include <sstream>
#include <iomanip>

#include <SFML/System/Vector2.hpp>
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

static const vec4 RED = {1, 0, 0, 1};
static const vec4 GREEN = {0, 1, 0, 1};
static const vec4 BLUE = {0, 0, 1, 1};
static const vec4 BLACK = {0, 0, 0, 1};
static const vec4 WHITE = {1, 1, 1, 1};

static const vec4 YELLOW = {1, 1, 0, 1};
static const vec4 CYAN = {0, 1, 1, 1};
static const vec4 MAGENTA = {1, 0, 1, 1};

/** \brief Converts a color in RGB format into HSV format */
vec4 to_hsv(vec4 in);

/** \brief Converts a color in HSV format into RGB format */
vec4 to_rgb(vec4 in);

/* Misc Utils */

/** \return returns a random float value between 0 and 1. Does *not* call srand. */
float rand_float();

template< typename T >
inline std::string int_to_hex( T i )
{
  std::stringstream stream;
  stream << std::uppercase
         << std::setfill ('0') << std::setw(sizeof(T)*2)
         << std::hex << i;
  return stream.str();
}

inline bool is_between(float x, float bound1, float bound2, float tolerance)
{
   // Handles cases when 'bound1' is greater than 'bound2' and when
   // 'bound2' is greater than 'bound1'.
   return (((x >= (bound1 - tolerance)) && (x <= (bound2 + tolerance))) ||
      ((x >= (bound2 - tolerance)) && (x <= (bound1 + tolerance))));
}

const float tolerance = 0.001f;
inline bool onLine(glm::vec2 pos1, glm::vec2 pos2, glm::vec2 point)
{
    if (is_between(point.x, pos1.x, pos2.x, tolerance) && is_between(point.y, pos1.y, pos2.y, tolerance))
    {
        if ((pos2.x - pos1.x) < tolerance)
        {
            return true;
        }
        const float M = (pos2.y - pos1.y) / (pos2.x - pos1.x); // Slope
        const float C = -(M * pos1.x) + pos1.y; // Y intercept

        // Checking if (x, y) is on the line passing through the end points.
        return (std::fabs (point.y - (M * point.x + C)) <= tolerance);
    }
    return false;
}

inline vec4 readColor(sf::Vector2u size, int x, int y)
{
    vec4 col;
    glReadPixels(x, size.y - y, 1, 1, GL_RGBA, GL_FLOAT, glm::value_ptr(col));
    return col;
}

#endif // STRUCTS_H_INCLUDED
