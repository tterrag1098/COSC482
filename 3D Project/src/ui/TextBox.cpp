#include "TextBox.h"
#include "Box.h"
#include "GraphicsEngine.h"
#include "UI.h"
#ifdef COMPAT_WIN
#include <Windows.h>
#endif // COMPAT_WIN

TextBox::TextBox(TextRendererTTF *t, glm::vec2 p, int w, int f, glm::vec4 bgc, glm::vec4 tc) : tr(t), pos(p), width(w), fontsize(f), textcolor(tc)
{
    Drawable::children.push_back(bg = new Box(p, w, fontsize + (padY * 2), bgc));

    tr->setColor(tc);
    tr->setFontSize(fontsize);

    cursorPos = 0;
    text = "text";
    focused = false;
    clearSelection();
    clock.restart();

    filter = [](char){ return true; };
}

TextBox::~TextBox()
{
    delete bg;
}

void TextBox::setFilter(std::function<bool(char)> f)
{
    filter = f;
}

void TextBox::draw(GraphicsEngine *ge)
{
    if (clock.getElapsedTime().asMilliseconds() > 500)
    {
        cursorState = !cursorState;
        clock.restart();
        load();
    }

    Drawable::draw(ge);

    tr->setScreenSize(ge->getSize().x, ge->getSize().y);
    tr->setColor(textcolor);

    int x = pos.x + padX;
    int y = ge->getSize().y - pos.y - fontsize - padY + 1;
    if (selBegin == selEnd)
    {
        tr->draw(text, x, y);
    }
    else
    {
        std::string before = text.substr(0, selBegin);
        std::string after = text.substr(selEnd, text.size() - selEnd);
        std::string selected = getSelected();

        tr->draw(before, x, y);
        tr->draw(after, x + tr->textWidth(before + selected), y);
        tr->setColor(glm::vec4(1.0f - textcolor.xyz(), 1));
        tr->draw(selected, x + tr->textWidth(before), y);
        tr->setColor(textcolor);
    }

    ge->uiShader.use();
}

void TextBox::refresh()
{
    Drawable::refresh();

    if (selBegin != selEnd)
    {
        static const glm::vec4 selcol = {0.2f, 0.6f, 1, 1};

        int x = pos.x + padX;
        std::string before = text.substr(0, selBegin);
        std::string in = getSelected();

        x += tr->textWidth(before);
        int w = tr->textWidth(in);
        int y = pos.y + padY;

        vert({x, y}, selcol);
        vert({x, y + fontsize}, selcol);
        vert({x + w, y + fontsize}, selcol);
        vert({x + w, y}, selcol);

        index_quad(1);
    }

    if (cursorState && focused)
    {
        glm::vec2 p = pos;
        std::string off = text.substr(0, cursorPos);
        p.x += padX + tr->textWidth(off);
        p.y += padY;

        vert(p, textcolor);
        vert({p.x + 1, p.y}, textcolor);
        vert({p.x + 1, p.y + fontsize}, textcolor);
        vert({p.x, p.y + fontsize}, textcolor);

        index_quad(1);
    }
}

int TextBox::getPosFromX(int x)
{
    int i = 0;
    char c;
    int px = pos.x + padX;
    for (; c = i >= text.size() ? 0 : text.at(i), i < text.size() && px + (tr->textWidth(&c, 1) / 2) < x; i++)
    {
        c = text.at(i);
        px += tr->textWidth(&c, 1);
    }
    return i;
}

std::string TextBox::getSelected()
{
    return text.substr(selBegin, selEnd - selBegin);
}

std::string TextBox::getText()
{
    return text;
}

void TextBox::setText(std::string t)
{
    text = t;
    clearSelection();
    cursorPos = 0;
}

void TextBox::erase(bool forward)
{
    if (selBegin != selEnd)
    {
        text = text.erase(selBegin, selEnd - selBegin);
        cursorPos = selBegin;
        clearSelection();
        load();
    }
    else if (forward && cursorPos < text.size())
    {
        text = text.erase(cursorPos, 1);
    }
    else if (cursorPos > 0)
    {
        text = text.erase(cursorPos - 1, 1);
        cursorPos--;
        load();
    }
}

void TextBox::clearSelection()
{
    selBegin = selEnd = 0;
    load();
}

bool TextBox::mousePressed(ButtonContext ctx)
{
    glm::vec2 p(ctx.event.x, ctx.event.y);

    if (bg->contains(p))
    {
        #ifdef COMPAT_WIN
        SetCursor(LoadCursor(NULL, IDC_IBEAM));
        #endif // COMPAT_WIN
        cursorState = true;
        clock.restart();
        cursorPos = getPosFromX(p.x);
        clearSelection();
        focused = true;
        load();
        return true;
    }
    else if (focused)
    {
        focused = false;
        load();
    }

    return false;
}

bool TextBox::mouseMoved(MoveContext ctx)
{
    if (bg->contains({ctx.event.x, ctx.event.y}))
    {
        #ifdef COMPAT_WIN
        SetCursor(LoadCursor(NULL, IDC_IBEAM));
        #endif // COMPAT_WIN
        return true;
    }

    if (focused && ctx.getUI()->isMouseDown())
    {
        int p1 = getPosFromX(ctx.getUI()->getPrevMouseClick().x);
        int p2 = getPosFromX(ctx.event.x);
        cursorPos = p2;
        if (p2 < p1) std::swap(p1, p2);
        if (p1 != selBegin || p2 != selEnd)
        {
            selBegin = p1;
            selEnd = p2;
            load();
        }
        return true;
    }

    return false;
}

bool TextBox::keyPressed(KeyContext ctx)
{
    if (focused)
    {
        bool ctrl = ctx.getUI()->anyDown({sf::Keyboard::RControl, sf::Keyboard::LControl});
        bool shift = ctx.getUI()->anyDown({sf::Keyboard::RShift, sf::Keyboard::LShift});

        int prevpos = cursorPos;
        switch(ctx.event.code)
        {
        case sf::Keyboard::Left:
            cursorPos = std::max(0, cursorPos - 1);
            clearSelection();
            load();
            break;

        case sf::Keyboard::Right:
            cursorPos = std::min((int) text.size(), cursorPos + 1);
            clearSelection();
            load();
            break;

        case sf::Keyboard::Delete:
            erase(true);
            break;

        default: break;
        }
        return true;
    }

    return false;
}

bool TextBox::keyInput(InputContext ctx)
{
    char c = ctx.event.unicode & 0xFF;
    if (!filter(c)) return false;

    std::string in(&c);
    if (focused)
    {
        bool type = false;
        switch(c)
        {
        case '\b':
            erase(false);
            break;

        default:
            type = true;
            break;
        }

        if (type && tr->textWidth(text) + tr->textWidth(in) < width - 3)
        {
            if (selBegin != selEnd)
            {
                text = text.erase(selBegin, selEnd - selBegin);
                cursorPos = selBegin;
                clearSelection();
            }

            if (cursorPos == 0)
            {
                text = in + text;
            }
            else if (cursorPos == text.size())
            {
                text += in;
            }
            else
            {
                text.insert(cursorPos, in);
            }
            cursorPos++;
            load();
        }

        return true;
    }

    return false;
}

