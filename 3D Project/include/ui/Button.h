#ifndef BUTTON_H
#define BUTTON_H

#include "Drawable.h"
#include "Listeners.h"
#include "glm/glm.hpp"

class Button : public Drawable, public Listener
{
public:
    Button(int x, int y, int size) : Button({x, y}, size) {};
    Button(glm::vec2 pos, int size) : Button(pos, size, size) {};
    Button(glm::vec2 pos, int width, int height) : Drawable(true), pos(pos), width(width), height(height) {};
    virtual ~Button() {};

    bool mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;
    bool mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;
    bool mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx) override;

    void setCorner(glm::vec2 pos);
    void setPressed(bool pressed);

    glm::vec2 getCorner();
    int getWidth();
    int getHeight();

    bool contains(glm::vec2 pos);

    void onPressed(std::function<void()>&& callback);

protected:
    int width, height;
    glm::vec2 pos;

    bool pressed = false;

    void refresh() override;

private:
    std::vector<std::function<void()>> callbacks;
    void fireCallbacks();
};

#endif // BUTTON_H
