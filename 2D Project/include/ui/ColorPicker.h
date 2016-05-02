#ifndef COLORPICKER_H
#define COLORPICKER_H

#include <iomanip>
#include <sstream>

#include "Box.h"
#include "Listeners.h"
#include "Drawable.h"
#include "Slider.h"
#include "TextRendererTTF.h"

class Slider;

class ColorPicker : public Listener, public Drawable
{
public:
    ColorPicker(GraphicsEngine *ge);
    virtual ~ColorPicker();

    virtual bool contains(glm::vec2 point) override;

    void resized(sf::Vector2u size) override;
    void draw() override;

    bool mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;
    bool mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;

    glm::vec4 getColor();

protected:
private:
    GraphicsEngine *ge;
    Slider *r, *g, *b, *a;
    Box *bg;
    Box *colorbg, *color;
    glm::ivec4 prevColor;
    TextRendererTTF text;

    glm::vec2 pos;
    const int width, height;
};

#endif // COLORPICKER_H
