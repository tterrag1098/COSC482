#include "Listeners.h"

Listener::~Listener()
{
    for (Listener *l : children) delete l;
}

bool Listener::mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    for (Listener *l : children)
    {
        if (l->mousePressed(ctx))
        {
            return true;
        }
    }
    return false;
}

bool Listener::mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx)
{
    for (Listener *l : children)
    {
        if (l->mouseReleased(ctx))
        {
            return true;
        }
    }
    return false;
}

bool Listener::mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx)
{
    for (Listener *l : children)
    {
        if (l->mouseMoved(ctx))
        {
            return true;
        }
    }
    return false;
}
