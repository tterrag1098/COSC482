#include "BodyInfo.h"
#include "TextRendererTTF.h"
#include "UI.h"
#include <iomanip>
#include "TextButton.h"
#include "Box.h"
#include "BodyProperties.h"

BodyInfo::BodyInfo(UI *ui, glm::vec2 p, std::vector<BodyDrawable*> bodylist) : GuiBase(ui, p, w, h)
{
    bodyPicker = new TypePicker<BodyDrawable>(ui->getTextRenderer(), p + (float) padding, w - (padding * 2), fontsize, bodylist);
    bodyPicker->onPressed([this, ui]{
        ui->getEngine()->setSelected(bodyPicker->getSelected());
    });
    addChild(bodyPicker);

    delBut = new TextButton(p, ui->getTextRenderer(), "Delete", fontsize);
    Drawable::children.push_back(delBut);
    Listener::children.push_back(delBut);
    height += linespace + delBut->getHeight();
    bg->setHeight(height);

    delBut->setCorner(p + glm::vec2((width / 2) - (delBut->getWidth() / 2) - padding, height - delBut->getHeight() - padding));
    delBut->onPressed([this, ui]{
        BodyDrawable* body = ui->getEngine()->getSelectedBody();
        if (body)
        {
            ui->getEngine()->removeBody(body);
            ui->getEngine()->getPhysics()->removeBody(body);
            bodyPicker->remove(body);
            props->onBodyRemoved(body);
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
    if (!visible) return;

    BodyDrawable *sel = ge->getSelectedBody();
    TextRendererTTF *tr = ui->getTextRenderer();

    Drawable::draw(ge);

    tr->setScreenSize(ge->getSize().x, ge->getSize().y);
    tr->setFontSize(fontsize);
    tr->setColor(WHITE);

    if (sel)
    {
        if (sel != bodyPicker->getSelected()) bodyPicker->setSelected(sel);

        bodyPicker->setVisible(true);
        delBut->setVisible(true);

        int x = pos.x + padding;
        int y = ge->getSize().y - pos.y - padding - fontsize - 28;

        std::stringstream mass;
        mass << "Mass:     " << printMass(sel->getMass());

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
        bodyPicker->setVisible(false);
        delBut->setVisible(false);

        std::string s = "No Body Selected";
        tr->draw(s, pos.x - (tr->textWidth(s) / 2) + (width / 2), ge->getSize().y - pos.y - (height / 2) - (fontsize / 2));
    }

    ge->uiShader.use();
}

void BodyInfo::onBodyAdded(BodyDrawable *b)
{
    bodyPicker->add(b);
}

void BodyInfo::setProps(BodyProperties *p)
{
    props = p;
}
