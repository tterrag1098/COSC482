#include "Listeners.h"

Listener::~Listener()
{
    for (Listener *l : children) delete l;
}

bool Listener::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    bool res = false;
    for (Listener *l : children)
    {
        if (l->mousePressed(ctx))
        {
            res = true;
        }
    }
    return res;
}

bool Listener::mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    bool res = false;
    for (Listener *l : children)
    {
        if (l->mouseReleased(ctx))
        {
            res = true;
        }
    }
    return false;
}

bool Listener::mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx)
{
    bool res = false;
    for (Listener *l : children)
    {
        if (l->mouseMoved(ctx))
        {
            res = true;
        }
    }
    return false;
}
