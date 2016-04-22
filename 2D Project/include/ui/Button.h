#ifndef BUTTON_H
#define BUTTON_H

#include "Drawable.h"
#include "util/utils.h"
#include "ui/Listeners.h"

class Button : public Drawable, public Listener
{
public:
    Button(int x, int y, int size) : Button({x, y}, size) {};
    Button(glm::vec2 pos, int size) : Drawable(true), pos(pos), size(size) {};
    virtual ~Button() {};

    bool mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;
    bool mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;

protected:
    bool pressed = false;

    void refresh() override;

private:
    glm::vec2 pos;
    int size;
};

#endif // BUTTON_H
