#ifndef GUIBASE_H
#define GUIBASE_H

#include "Drawable.h"
#include "Listeners.h"

class UI;
class Box;

class GuiBase : public Drawable, public Listener
{
    public:
        GuiBase(UI *ui, glm::vec2 pos, int width, int height);
        virtual ~GuiBase();

        bool mousePressed(ButtonContext ctx) override;
        bool mouseReleased(ButtonContext ctx) override;

        template <typename T>
        void addChild(T* t)
        {
            Drawable::children.push_back(t);
            Listener::children.push_back(t);
        }

        template <typename T>
        void addChildren(std::initializer_list<T*> ts)
        {
            for (T* t : ts) addChild(t);
        }

    protected:
        UI *ui;
        Box *bg;

        glm::vec2 pos;
        int width, height;

        static constexpr int w = 225;
        static constexpr int fontsize = 12;
        static constexpr int padding = 6;

    private:
};

#endif // GUIBASE_H
