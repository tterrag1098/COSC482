#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#define GLM_SWIZZLE
#include "GL/glew.h"
#include <random>
#include <sstream>
#include <iomanip>
#include <cstdio>

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

/** \return A random float value between 0 and 1. Does *not* call srand. */
float rand_float();

/** \return A nicely printed mass, using standard number naming. */
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

/** \return A double as a string, with no trailing zeros, using as much precision as necessary */
inline std::string dbl2str(double d)
{
    size_t len = std::snprintf(0, 0, "%.10f", d);
    std::string s(len+1, 0);
    std::snprintf(&s[0], len+1, "%.10f", d);
    // remove nul terminator
    s.pop_back();
    // remove trailing zeros
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);
    // remove trailing point
    if(s.back() == '.') {
        s.pop_back();
    }
    return s;
}

#endif // STRUCTS_H_INCLUDED
