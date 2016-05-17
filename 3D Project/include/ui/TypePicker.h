#ifndef TYPEPICKER_H
#define TYPEPICKER_H

#include <algorithm>

#include "Listeners.h"
#include "Drawable.h"
#include "TextRendererTTF.h"
#include "TextButton.h"
#include "Box.h"
#include "GraphicsEngine.h"

template <typename T>
class TypePicker : public Listener, public Drawable
{

public:
    TypePicker(TextRendererTTF *tr, glm::vec2 pos, int width, int fontsize, std::initializer_list<T*> typelist) : TypePicker(tr, pos, width, fontsize)
    {
        for (T *t : typelist)
        {
            types.push_back(t);
        }
    }

    TypePicker(TextRendererTTF *tr, glm::vec2 pos, int width, int fontsize, std::vector<T*> typelist = {}) :
        tr(tr), pos(pos), width(width), fontsize(fontsize), types(typelist)
    {
        left = new TextButton(pos, tr, "<", fontsize);
        right = new TextButton(pos + glm::vec2(width - left->getWidth(), 0), tr, ">", fontsize);
        bg = new Box(pos + glm::vec2(left->getWidth(), 0), width - (left->getWidth() * 2), left->getHeight(), BLACK + 0.1f);

        left->onPressed([this]
        {
            selected = ((selected + types.size()) - 1) % types.size();
            this->fireCallbacks();
        });

        right->onPressed([this]
        {
            selected = (selected + 1) % types.size();
            this->fireCallbacks();
        });

        Drawable::children.push_back(bg);
        Drawable::children.push_back(left);
        Drawable::children.push_back(right);

        Listener::children.push_back(left);
        Listener::children.push_back(right);
    }

    void draw(GraphicsEngine *ge) override
    {
        Drawable::draw(ge);

        if (visible)
        {
            T *sel = types[selected];
            std::stringstream ss;
            ss << *sel;
            std::string s = ss.str();

            tr->setScreenSize(ge->getSize());
            tr->setColor(WHITE);
            tr->draw(s, pos.x + (width / 2) - (tr->textWidth(s) / 2), ge->getSize().y - pos.y - fontsize - 3);
            ge->uiShader.use();
        }
    }

    T* getSelected()
    {
        return types[selected];
    }

    void setSelected(T* sel)
    {
        selected = std::distance(types.begin(), std::find(types.begin(), types.end(), sel)) % types.size();
    }

    void remove(T* t)
    {
        types.erase(std::find(types.begin(), types.end(), t));
        if (selected >= types.size())
        {
            selected = 0;
        }
    }

    void add(T* t)
    {
        types.push_back(t);
    }

    void onPressed(std::function<void()>&& callback)
    {
        callbacks.push_back(callback);
    }

protected:
private:
    TextRendererTTF *tr;
    TextButton *left, *right;
    Box *bg;

    glm::vec2 pos;
    int width;
    int fontsize;

    std::vector<T*> types;
    int selected = 0;

    std::vector<std::function<void()>> callbacks;
    void fireCallbacks()
    {
        for (auto f : callbacks)
        {
            f();
        }
    }
};

#endif // TYPEPICKER_H
