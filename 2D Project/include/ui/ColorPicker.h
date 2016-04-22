#ifndef COLORPICKER_H
#define COLORPICKER_H

#include "Box.h"

class ColorPicker
{
    public:
        ColorPicker(int x, int y, int width, int height);
        virtual ~ColorPicker();
    protected:
    private:
        Box *bg;

};

#endif // COLORPICKER_H
