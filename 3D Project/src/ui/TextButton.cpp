#include "TextButton.h"
#include "TextRendererTTF.h"
#include "GraphicsEngine.h"

TextButton::TextButton(glm::vec2 pos, TextRendererTTF *t, std::string tx, int fs) : Button(pos, -1),
    tr(t), text(tx), fontsize(fs)
{
    tr->setFontSize(fs);
    width = tr->textWidth(text) + (padding * 2);
    height = fs + (padding * 2);
}

TextButton::~TextButton()
{
    //dtor
}

void TextButton::draw(GraphicsEngine *ge)
{
    Drawable::draw(ge);

    if (visible)
    {
        tr->setFontSize(fontsize);
        tr->setScreenSize(ge->getSize());
        tr->setColor(WHITE);
        tr->draw(text, pos.x + padding, ge->getSize().y - pos.y - padding - fontsize + 1);
        ge->uiShader.use();
    }
}
