#include "util/utils.h"

using namespace glm;

float rand_float()
{
    return rand() / ((float) (RAND_MAX));
}

vec4 to_hsv(vec4 in)
{
    vec4 ret;

    float r = in.r, g = in.g, b = in.b;

    float max = r;
    if (max < g) max = g;
    if (max < b) max = b;
    float min = r;
    if (min > g) min = g;
    if (min > b) min = b;

    ret.r = 0;
    if (max == min) ret.g = 0;
    else if (max == r)
    {
        ret.r = 60 * (g - b)/(max - min);
        if (ret.r < 0) ret.b += 360;
        if (ret.r >= 360) ret.r -= 360;
    }
    else if (max == g)
    {
        ret.r = 60 * (b - r) / (max - min) + 120;
    }
    else if (max == b)
    {
        ret.r = 60 * (r - g) / (max - min) + 240;
    }

    if (max == 0) ret.s = 0;
    else ret.g = 1 - (min / max);

    ret.b = max;

    ret.r /= 360;

    ret.a = in.a;

    return ret;
}

vec4 to_rgb(vec4 in)
{
    vec4 ret;

    float h = in.r * 360, s = in.g, v = in.b;

	if (h < 0) h = 0;
	if (h > 359) h = 359;
	if (s < 0) s = 0;
	if (s > 1) s = 1;
	if (v < 0) v = 0;
	if (v > 1) v = 1;

	float tmp = h/60.0;
	int hi = floor(tmp);
	float f = tmp - hi;
	float p = v * (1 - s);
	float q = v * (1 - f * s);
	float t = v * (1 - (1 - f) * s);

    switch (hi)
    {
    case 0:
        ret.r = v;
        ret.g = t;
        ret.b = p;
        break;
    case 1:
        ret.r = q;
        ret.g = v;
        ret.b = p;
        break;
    case 2:
        ret.r = p;
        ret.g = v;
        ret.b = t;
        break;
    case 3:
        ret.r = p;
        ret.g = q;
        ret.b = v;
        break;
    case 4:
        ret.r = t;
        ret.g = p;
        ret.b = v;
        break;
    case 5:
        ret.r = v;
        ret.g = p;
        ret.b = q;
        break;
    }

    ret.a = in.a;

    return ret;
}
