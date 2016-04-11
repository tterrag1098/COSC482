#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "GL/gl.h"
#include <random>

#include <glm/detail/type_vec4.hpp>

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

#endif // STRUCTS_H_INCLUDED
