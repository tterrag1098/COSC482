#include "Button.h"

using namespace glm;

void Button::refresh()
{
    vec4 col_center = {0.15f, 0.15f, 0.15f, 1};
    vec4 col_light =  {0.3f, 0.3f, 0.3f, 1};
    vec4 col_dark = BLACK;

    int in = size / 10;

    vert(pos, col_light);
    vert(pos + vec2(in, in), col_light);
    vert(pos + vec2(size - in, in), col_light);
    vert(pos + vec2(size, 0), col_light);

    vert(pos + vec2(size, 0), col_light);
    vert(pos + vec2(size - in, in), col_light);
    vert(pos + vec2(size - in, size - in), col_light);
    vert(pos + vec2(size, size), col_light);

    vert(pos + vec2(size, size), col_dark);
    vert(pos + vec2(size - in, size - in), col_dark);
    vert(pos + vec2(in, size - in), col_dark);
    vert(pos + vec2(0, size), col_dark);

    vert(pos + vec2(0, size), col_dark);
    vert(pos + vec2(in, size - in), col_dark);
    vert(pos + vec2(in, in), col_dark);
    vert(pos, col_dark);

    vert(pos + vec2(in, in), col_center);
    vert(pos + vec2(size - in, in), col_center);
    vert(pos + vec2(size - in, size - in), col_center);
    vert(pos + vec2(in, size - in), col_center);

    indices = {0, 3, 2, 0, 2, 1, 4, 7, 6, 4, 6, 5, 8, 11, 10, 8, 10, 9, 12, 15, 14, 12, 14, 13, 16, 19, 18, 16, 18, 17};
}
