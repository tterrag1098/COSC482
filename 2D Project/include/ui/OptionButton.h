#ifndef FILLBUTTON_H
#define FILLBUTTON_H

#include "Listeners.h"
#include "Drawable.h"
#include "TextRendererTTF.h"

class UI;
class GraphicsEngine;
class StateButton;
class Box;
class TexturedBox;

class OptionButton : public Listener, public Drawable
{
public:
    OptionButton(UI *ui);
    virtual ~OptionButton();

    void resized(sf::Vector2u size) override;
    void refresh() override;
    void draw() override;

    virtual bool contains(glm::vec2 point) override { return false; };

    bool mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;
    bool mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;

    bool state();

protected:
private:
    UI *ui;
    GraphicsEngine *ge;
    StateButton *but;
    Box *bg;
    GLuint texId;
    TexturedBox *iconOn, *iconOff;
    TextRendererTTF text;

    glm::vec2 pos;
    const int width, height;
};
#endif // FILLBUTTON_H
