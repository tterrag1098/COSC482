#include "BodyInfo.h"
#include "TextRendererTTF.h"
#include "UI.h"
#include <iomanip>
#include "TextButton.h"
#include "Box.h"

BodyInfo::BodyInfo(UI *ui, glm::vec2 p) : GuiBase(ui, p, w, h)
{
    delBut = new TextButton(p, ui->getTextRenderer(), "Delete", fontsize);
    Drawable::children.push_back(delBut);
    Listener::children.push_back(delBut);
    height += linespace + delBut->getHeight();
    bg->setHeight(height);

    delBut->setCorner(p + glm::vec2((width / 2) - (delBut->getWidth() / 2) - padding, height - delBut->getHeight() - padding));
    delBut->onPressed([ui]{
        const BodyDrawable* body = ui->getEngine()->getSelectedBody();
        if (body)
        {
            ui->getEngine()->removeBody(body);
            ui->getEngine()->getPhysics()->removeBody(body);
            ui->getEngine()->setSelected(NULL);
        }
    });
}

BodyInfo::~BodyInfo()
{
    //dtor
}

void BodyInfo::draw(GraphicsEngine *ge)
{
    const BodyDrawable *sel = ge->getSelectedBody();
    TextRendererTTF *tr = ui->getTextRenderer();

    Drawable::draw(ge);

    tr->setScreenSize(ge->getSize().x, ge->getSize().y);
    tr->setFontSize(fontsize);
    tr->setColor(WHITE);

    if (sel)
    {
        delBut->setVisible(true);

        std::stringstream mass;
        mass << "Mass:     " << printMass(sel->getMass());

        int x = pos.x + padding;
        int y = ge->getSize().y - pos.y - padding - fontsize;

        tr->draw(mass.str(), x, y);

        y -= fontsize + linespace;

        std::stringstream radius;
        radius << "Radius:  " << std::setprecision(3) << sel->getRadius() << " km";
        tr->draw(radius.str(), x, y);

        y -= fontsize + linespace;

        double s = glm::length(sel->getVelocity());
        std::stringstream speed;
        speed << "Speed:   " << std::fixed << std::setprecision(3) << s << " km/s";
        tr->draw(speed.str(), x, y);
    }
    else
    {
        delBut->setVisible(false);

        std::string s = "No Body Selected";
        tr->draw(s, pos.x - (tr->textWidth(s) / 2) + (width / 2), ge->getSize().y - pos.y - (height / 2) - (fontsize / 2));
    }

    ge->uiShader.use();
}
