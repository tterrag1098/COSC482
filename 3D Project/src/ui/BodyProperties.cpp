#include "BodyProperties.h"
#include "Body.h"
#include "UI.h"
#include "TextBox.h"
#include "BodyInfo.h"
#include "SphericalCamera.h"
#include "GhostPlanet.h"

BodyProperties::BodyProperties(UI *ui, BodyInfo *i, glm::vec2 p) : GuiBase(ui, p, w, htall), info(i)
{
    TextRendererTTF *tr = ui->getTextRenderer();

    glm::vec2 pos = p + (float) padding;
    pos.y += linesize;
    pos.x += 60;

    tName = new TextBox(tr, pos, 150, fontsize);

    pos.y += linesize;
    tPickerBody = new TypePicker<BodyType>(tr, pos, 150, fontsize, ALL_BODY_TYPES);

    pos.y += linesize;
    tMass = new TextBox(tr, pos, 150, fontsize);
    tMass->setFilter([](char c){ return isdigit(c) || c == '.'; });

    pos.y += linesize;
    tRadius = new TextBox(tr, pos, 150, fontsize);
    tRadius->setFilter([](char c){ return isdigit(c) || c == '.'; });

    pos.y += linesize*2;
    tPickerCenter = new TypePicker<BodyDrawable>(tr, pos, 150, fontsize, ui->getEngine()->getBodies());

    pos.y += linesize;
    tOrbitRadius = new TextBox(tr, pos, 150, fontsize);
    tOrbitRadius->setText("10");

    std::function<bool(char)> filter = [](char c){ return isdigit(c) || c == '.' || c == '-'; };

    pos.y += linesize;
    tOrbitLat = new TextBox(tr, pos, 150, fontsize);
    tOrbitLat->setText("0");
    tOrbitLat->setFilter(filter);

    pos.y += linesize;
    tOrbitLong = new TextBox(tr, pos, 150, fontsize);
    tOrbitLong->setText("0");
    tOrbitLong->setFilter(filter);

    pos.y += linesize;
    tVelX = new TextBox(tr, pos, 150, fontsize);
    tVelX->setText("0");
    tVelX->setFilter(filter);

    pos.y += linesize;
    tVelY = new TextBox(tr, pos, 150, fontsize);
    tVelY->setText("0");
    tVelY->setFilter(filter);

    pos.y += linesize;
    tVelZ = new TextBox(tr, pos, 150, fontsize);
    tVelZ->setText("0");
    tVelZ->setFilter(filter);

    apply = new TextButton(pos, tr, "Apply", fontsize);
    apply->setCorner({p.x + (width / 2) - (apply->getWidth() / 2), p.y + hshort - padding - apply->getHeight()});
    apply->onPressed([this, ui]{
        prevSel->setName(tName->getText());
        prevSel->setType(tPickerBody->getSelected());
        prevSel->setMass(tMass->getDouble());
        prevSel->setRadius(tRadius->getDouble());
        ui->getEngine()->updateLight(prevSel);
    });

    apply->load();
    apply->setVisible(false);

    create = new TextButton(pos, tr, "Create", fontsize);
    create->setCorner({p.x + (width / 2) - (create->getWidth() / 2), p.y + htall - padding - create->getHeight()});
    create->onPressed([this, ui]{
        SphericalCamera temp;
        GhostPlanet *ghost = ui->getEngine()->getGhost();

        BodyDrawable *b = new BodySphere(ghost->getName(), ghost->getType(), ghost->getPos(), ghost->getRadius(), ghost->getMass());
        b->setVelocity(ghost->getVelocity());

        ui->getEngine()->addBody(b);
        ui->getEngine()->getPhysics()->addBody(b);
        info->onBodyAdded(b);
        tPickerCenter->add(b);
    });

    addChildren({tName, tMass, tRadius, tOrbitRadius, tOrbitLat, tOrbitLong, tVelX, tVelY, tVelZ});
    addChild(tPickerBody);
    addChild(tPickerCenter);
    addChildren({apply, create});
}

BodyProperties::~BodyProperties() {}

void BodyProperties::draw(GraphicsEngine *ge)
{
    if (!visible) return;
    BodyDrawable *sel = ge->getSelectedBody();

    if (sel)
    {
        apply->setVisible(true);
        create->setVisible(false);

        tPickerCenter->setVisible(false);
        tOrbitRadius->setVisible(false);
        tOrbitLat->setVisible(false);
        tOrbitLong->setVisible(false);
        tVelX->setVisible(false);
        tVelY->setVisible(false);
        tVelZ->setVisible(false);
    }
    else
    {
        apply->setVisible(false);
        create->setVisible(true);

        tPickerCenter->setVisible(true);
        tOrbitRadius->setVisible(true);
        tOrbitLat->setVisible(true);
        tOrbitLong->setVisible(true);
        tVelX->setVisible(true);
        tVelY->setVisible(true);
        tVelZ->setVisible(true);
    }

    GuiBase::draw(ge);

    TextRendererTTF *tr = ui->getTextRenderer();
    tr->setScreenSize(ge->getSize());
    tr->setFontSize(fontsize);
    tr->setColor(WHITE);

    glm::vec2 p = pos + (float) padding;
    p.y = ge->getSize().y - p.y - fontsize - 5;

    if (sel != prevSel)
    {
        prevSel = sel;

        if (sel)
        {
            tName->setText(sel->getName());

            tPickerBody->setSelected(sel->getType());

            tMass->setText(dbl2str(sel->getMass()));
            tRadius->setText(dbl2str(sel->getRadius()));

            height = hshort;
        }
        else
        {
            height = htall;
        }

        bg->setHeight(height);
    }

    std::string s = sel ? "Edit " + sel->getName() : "Create Body";
    tr->draw(s, pos.x + (width / 2) - (tr->textWidth(s) / 2), p.y);

    p.y -= linesize;

    s = "Name:";
    tr->draw(s, p.x, p.y);

    p.y -= linesize;
    s = "Type:";
    tr->draw(s, p.x, p.y);

    p.y -= linesize;
    s = "Mass:";
    tr->draw(s, p.x, p.y);

    p.y -= linesize;
    s = "Radius:";
    tr->draw(s, p.x, p.y);

    if (!sel)
    {
        GhostPlanet *ghost = ge->getGhost();
        ghost->setVisible(true);
        if (tName->getText() != "")
        {
            cam.setPosition(tOrbitRadius->getDouble(), tOrbitLong->getDouble(), tOrbitLat->getDouble());
            cam.setCenter(tPickerCenter->getSelected()->getPosF());

            ghost->setName(tName->getText());
            ghost->setType(tPickerBody->getSelected());
            ghost->setPosition(cam.getPosition());
            ghost->setRadius(tRadius->getDouble());
            ghost->setMass(tRadius->getDouble());
            ghost->setVelocity({tVelX->getDouble(), tVelY->getDouble(), tVelZ->getDouble()});
        }
        p.y -= linesize;
        s = "Orbit Configuration";
        tr->draw(s, pos.x + (width / 2) - (tr->textWidth(s) / 2), p.y);

        p.y -= linesize;
        s = "Center:";
        tr->draw(s, p.x, p.y);

        p.y -= linesize;
        s = "Radius:";
        tr->draw(s, p.x, p.y);

        p.y -= linesize;
        s = "Latitude:";
        tr->draw(s, p.x, p.y);

        p.y -= linesize;
        s = "Longitude:";
        tr->draw(s, p.x, p.y);

        p.y -= linesize;
        s = "X Speed:";
        tr->draw(s, p.x, p.y);

        p.y -= linesize;
        s = "Y Speed:";
        tr->draw(s, p.x, p.y);

        p.y -= linesize;
        s = "Z Speed:";
        tr->draw(s, p.x, p.y);
    }
    else
    {
        ge->getGhost()->setVisible(false);
    }

    ge->uiShader.use();
}

void BodyProperties::onBodyRemoved(BodyDrawable *b)
{
    tPickerCenter->remove(b);
}
