#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Drawable.h"
#include "Listeners.h"
#include "TextRendererTTF.h"
#include "SFML/System/Clock.hpp"

class Box;

/**
\class TextBox

\brief A basic text box. Supports typing, selecting, backspacing, deleting, and filtering

*/
class TextBox : public Drawable, public Listener
{
    public:
        TextBox(TextRendererTTF *text, glm::vec2 pos, int width = 200, int fontsize = 16, glm::vec4 bgCol = WHITE, glm::vec4 textCol = BLACK);
        virtual ~TextBox();

        void refresh() override;
        void draw(GraphicsEngine *ge) override;

        bool mousePressed(ButtonContext ctx) override;
        bool mouseMoved(MoveContext ctx) override;
        bool keyPressed(KeyContext ctx) override;
        bool keyInput(InputContext ctx) override;

        std::string getText();
        double getDouble(); ///< Convenience method to get the current text as a double, if possible. Returns 0 if not.
        void setText(std::string text);

        void setFilter(std::function<bool(char)> filter); ///< Register a filter for the text box. Will be called with every character entered.

    protected:
    private:
        Box *bg;
        TextRendererTTF *tr;

        sf::Clock clock;
        bool cursorState;

        glm::vec2 pos;
        int width, fontsize;
        std::string text;
        glm::vec4 textcolor;

        std::function<bool(char)> filter;

        static constexpr int padY = 6;
        static constexpr int padX = 3;

        bool focused;
        int cursorPos;
        int selBegin, selEnd;

        int getPosFromX(int x);

        std::string getSelected();
        void erase(bool forward);
        void clearSelection();
};

#endif // TEXTBOX_H
