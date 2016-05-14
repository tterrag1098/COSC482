#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#define GLM_SWIZZLE
#include "GL/glew.h"
#include <random>
#include <sstream>
#include <iomanip>

#include <SFML/System/Vector2.hpp>
#include <glm/glm.hpp>
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

inline bool onLine(glm::vec2 pos1, glm::vec2 pos2, glm::vec2 point, float tolerance = 0.5f)
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

inline void getPerpendicularEdge(vec2 p1, vec2 p2, float size, glm::vec2* vecs, bool front = false)
{
    glm::vec2 diff = glm::normalize(p2 - p1) * size;
    glm::vec2 lOff = glm::mat2(0, -1, 1, 0) * diff;
    glm::vec2 rOff = glm::mat2(0, 1, -1, 0) * diff;

    if (front)
    {
        vecs[0] = p1 + lOff;
        vecs[1] = p1 + rOff;
    }
    else
    {
        vecs[0] = p2 + lOff;
        vecs[1] = p2 + rOff;
    }
}

inline std::string printMass(double mass)
{
    std::stringstream ret;
    ret << std::setprecision(3);

    if (mass < 1000)
    {
        ret << mass << " Thousand";
    }
    else if (mass < 1000000)
    {
        ret << mass/1000 << " Million";
    }
    else if (mass < 1e9)
    {
        ret << mass/1e6 << " Billion";
    }
    else if (mass < 1e12)
    {
        ret << mass/1e9 << " Trillion";
    }
    else if (mass < 1e15)
    {
        ret << mass/1e12 << " Quadrillion";
    }
    else
    {
        ret << mass/1e15 << " Quintillion";
    }

    ret << " kg";
    return ret.str();
}

#endif // STRUCTS_H_INCLUDED
