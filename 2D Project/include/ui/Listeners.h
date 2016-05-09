#ifndef LISTENERS_H_INCLUDED
#define LISTENERS_H_INCLUDED

#include <SFML/Window/Event.hpp>

class UI;

template <typename T>
class ListenerContext
{
public:
    ListenerContext(UI *ui, T e) : ui(ui), event(e) {};
    virtual ~ListenerContext() {};

    const T event;
    UI* getUI() { return ui; }

protected:

private:
    UI *ui;
};

template<typename T>
inline ListenerContext<T> create_ctx(UI *ui, T event)
{
    return ListenerContext<T>(ui, event);
}

class Listener
{
public:
    virtual ~Listener();

    virtual bool mousePressed(ListenerContext<sf::Event::MouseButtonEvent> ctx);
    virtual bool mouseReleased(ListenerContext<sf::Event::MouseButtonEvent> ctx);
    virtual bool mouseMoved(ListenerContext<sf::Event::MouseMoveEvent> ctx);

protected:
    std::vector<Listener*> children;
};

#endif // LISTENERS_H_INCLUDED
