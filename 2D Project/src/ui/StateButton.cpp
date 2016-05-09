#include "StateButton.h"

StateButton::StateButton(int x, int y, int size) : Button({x, y}, size) {};

bool StateButton::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    if (Button::mousePressed(ctx))
    {
        state = !state;
        return true;
    }
    return false;
}

bool StateButton::getState()
{
    return state;
}
