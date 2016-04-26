#ifndef SLIDER_H
#define SLIDER_H

#include "Drawable.h"
#include "Listeners.h"
#include "Box.h"
#include "Button.h"
#include "UI.h"

class Slider : public Drawable, public Listener
{
public:
    Slider(int x, int y, int width, int min, int max);
    virtual ~Slider();

    virtual bool contains(glm::vec2 point) override { return false; }

    int getValue();
    void setValue(int value);

    void setX(int x);
    void setY(int y);

    bool mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;
    bool mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;
    bool mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx) override;

protected:
private:
    int pos;
    int width, min, max;
    bool dragging;
    glm::vec2 pressPos;

    void calculateValue();

    Box *bar;
    Button *thumb;
};

#endif // SLIDER_H
