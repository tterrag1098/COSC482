#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include "Button.h"
class TextRendererTTF;

class TextButton : public Button
{
    public:
        TextButton(glm::vec2 pos, TextRendererTTF *tr, std::string text, int fontsize = 14);
        virtual ~TextButton();

        void draw(GraphicsEngine *ge);
    protected:
    private:
        TextRendererTTF *tr;
        std::string text;
        int fontsize;

        static constexpr int padding = 6;
};

#endif // TEXTBUTTON_H
