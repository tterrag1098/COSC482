#ifndef THICKNESSSLIDER_H
#define THICKNESSSLIDER_H

#include "Listeners.h"
#include "Drawable.h"
#include "TextRendererTTF.h"

class GraphicsEngine;
class StateButton;
class Box;

class FillButton : public Listener, public Drawable
{
public:
    FillButton(GraphicsEngine *ge);
    virtual ~FillButton();

    void resized(sf::Vector2u size) override;
    void draw() override;

    virtual bool contains(glm::vec2 point) override { return false; };

    bool mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;
    bool mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;

    bool fill();

protected:
private:
    GraphicsEngine *ge;
    StateButton *but;
    Box *bg;
    TextRendererTTF text;

    glm::vec2 pos;
    const int width, height;
};
#endif // THICKNESSSLIDER_H
