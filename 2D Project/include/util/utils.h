#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "GL/gl.h"
#include <random>

#include <glm/detail/type_vec3.hpp>

using namespace glm;

static const vec3 RED = {1.0f, 0.0f, 0.0f};
static const vec3 GREEN = {0.0f, 1.0f, 0.0f};
static const vec3 BLUE = {0.0f, 0.0f, 1.0f};
static const vec3 BLACK = {0.0f, 0.0f, 0.0f};
static const vec3 WHITE = {1.0f, 1.0f, 1.0f};

static const vec3 YELLOW = {1.0f, 1.0f, 0.0f};
static const vec3 CYAN = {0.0f, 1.0f, 1.0f};
static const vec3 MAGENTA = {1.0f, 0.0f, 1.0f};

/** \brief Converts a color in RGB format into HSV format */
vec3 to_hsv(vec3 in);

/** \brief Converts a color in HSV format into RGB format */
vec3 to_rgb(vec3 in);

/* Misc Utils */

/** \return returns a random float value between 0 and 1. Does *not* call srand. */
float rand_float();

#endif // STRUCTS_H_INCLUDED
