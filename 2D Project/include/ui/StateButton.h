#ifndef STATEBUTTON_H_INCLUDED
#define STATEBUTTON_H_INCLUDED

#include "Button.h"

class StateButton : public Button
{
public:
    StateButton(int x, int y, int size);

    bool mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx) override;

    bool getState();

private:
    bool state;
};

#endif // STATEBUTTON_H_INCLUDED
