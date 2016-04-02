#include "utils.h"

namespace lib
{

float rand_float()
{
    return rand() / ((float) (RAND_MAX));
}

ColorHSV to_hsv(ColorRGB in)
{
    ColorHSV ret;

    float r = in.r, g = in.g, b = in.b;

    float max = r;
    if (max < g) max = g;
    if (max < b) max = b;
    float min = r;
    if (min > g) min = g;
    if (min > b) min = b;

    ret.h = 0;
    if (max == min) ret.h = 0;
    else if (max == r)
    {
        ret.h = 60 * (g - b)/(max - min);
        if (ret.h < 0) ret.h += 360;
        if (ret.h >= 360) ret.h -= 360;
    }
    else if (max == g)
    {
        ret.h = 60 * (b - r) / (max - min) + 120;
    }
    else if (max == b)
    {
        ret.h = 60 * (r - g) / (max - min) + 240;
    }

    if (max == 0) ret.s = 0;
    else ret.s = 1 - (min / max);

    ret.v = max;

    ret.h /= 360;

    return ret;
}

ColorRGB to_rgb(ColorHSV in)
{
    ColorRGB ret;

    float h = in.h * 360, s = in.s, v = in.v;

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

    return ret;
}

}
