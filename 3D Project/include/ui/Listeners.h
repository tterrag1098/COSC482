#ifndef LISTENERS_H_INCLUDED
#define LISTENERS_H_INCLUDED

#include <SFML/Window/Event.hpp>

class UI;

/**\brief Base class for listener contexts. Contains the event and the UI instance */
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

/**\brief Convenience to construct a context with type inference */
template<typename T>
inline ListenerContext<T> create_ctx(UI *ui, T event)
{
    return ListenerContext<T>(ui, event);
}

typedef ListenerContext<sf::Event::MouseButtonEvent> ButtonContext;
typedef ListenerContext<sf::Event::MouseMoveEvent> MoveContext;
typedef ListenerContext<sf::Event::KeyEvent> KeyContext;
typedef ListenerContext<sf::Event::TextEvent> InputContext;

/**\brief Base class for listener objects. Methods are provided for all major UI events.*/
class Listener
{
public:
    virtual ~Listener();

    virtual bool mousePressed(ButtonContext ctx);
    virtual bool mouseReleased(ButtonContext ctx);
    virtual bool mouseMoved(MoveContext ctx);

    virtual bool keyPressed(KeyContext ctx);
    virtual bool keyInput(InputContext ctx);

protected:
    std::vector<Listener*> children;
};

#endif // LISTENERS_H_INCLUDED
