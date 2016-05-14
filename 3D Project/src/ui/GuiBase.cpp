#include "GuiBase.h"
#include "Box.h"

GuiBase::GuiBase(UI *ui, glm::vec2 p, int w, int h) : Drawable(Materials::whitePlastic, false, false),
    ui(ui), pos(p), width(w), height(h)
{
    Drawable::children.push_back(bg = new Box(p, w, h, {0, 0, 0, 0.75}));
}

GuiBase::~GuiBase() {}

bool GuiBase::mousePressed(ButtonContext ctx)
{
    return Listener::mousePressed(ctx) || bg->contains({ctx.event.x, ctx.event.y});
}

bool GuiBase::mouseReleased(ButtonContext ctx)
{
    return Listener::mouseReleased(ctx) || bg->contains({ctx.event.x, ctx.event.y});
}
