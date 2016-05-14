#include "SimulationControl.h"
#include "TextRendererTTF.h"
#include "UI.h"
#include "TextButton.h"
#include "TextBox.h"
#include "TexturedBox.h"

#include <ctype.h>
#include <string>

SimulationControl::SimulationControl(UI *ui, glm::vec2 p) : GuiBase(ui, p, w, h),
    ui(ui)
{
    TextRendererTTF *tr = ui->getTextRenderer();

    glm::vec2 pos = p + (float) padding;
    pos.y += 14 + spacing;

    m1 = new TextButton(pos, tr, "-1");
    m1->onPressed([this]{ addSpeed(-1); });
    pos.x += m1->getWidth() + spacing;
    m01  = new TextButton(pos, tr, "-0.1");
    m01->onPressed([this]{ addSpeed(-0.1); });
    pos.x += m01->getWidth() + spacing;

    text = new TextBox(tr, pos + glm::vec2(0, (m1->getHeight() / 2) - 11), 50, 14);
    text->setText("1.0");
    text->setFilter([](char c){
        return isdigit(c) || c == '.' || c == '\b';
    });
    pos.x += 50 + spacing;

    p01 = new TextButton(pos, tr, "+0.1");
    p01->onPressed([this]{ addSpeed(0.1); });
    pos.x += p01->getWidth() + spacing;
    p1 = new TextButton(pos, tr, "+1");
    p1->onPressed([this]{ addSpeed(1); });

    pos.x = p.x + padding;
    pos.y += p1->getHeight() + spacing;
    pause = new Button(pos, width - (padding * 2) - 1, 25);

    addChildren({m1, m01, p01, p1});
    addChild(pause);
    addChild(text);

    TexturedBox *playIcon, *pauseIcon;

    ui->getEngine()->uiShader.use();
    GLuint tex = ui->getEngine()->loadTexture("assets/playpause.png", ui->getEngine()->uiShader);

    Drawable::children.push_back(playIcon = new TexturedBox(ui->getEngine(), pause->getCorner() + glm::vec2(pause->getWidth() / 2 - 7, pause->getHeight() / 2 - 7), 14, 14, tex, {0, 0, 0.5, 1}));
    Drawable::children.push_back(pauseIcon = new TexturedBox(ui->getEngine(), playIcon->getCorner(), playIcon->getWidth(), playIcon->getHeight(), tex, {0.5, 0, 1, 1}));

    pauseIcon->setVisible(false);

    pause->onPressed([this, ui, playIcon, pauseIcon]{
        PhysicsEngine *pe = ui->getEngine()->getPhysics();
        pe->pauseUnpause();
        playIcon->setVisible(pe->isPaused());
        pauseIcon->setVisible(!(pe->isPaused()));
        load();
    });
}

void SimulationControl::addSpeed(double amt)
{
    std::string s = text->getText();
    if (s == "") s = "1";
    double val = std::max(0.0, std::min(10.0, std::stod(s) + amt));
    std::stringstream ss;
    ss << std::setprecision(5) << val;
    text->setText(ss.str());
}

SimulationControl::~SimulationControl()
{
    //dtor
}

void SimulationControl::draw(GraphicsEngine *ge)
{
    Drawable::draw(ge);

    std::string title = "Simulation Control";
    TextRendererTTF *tr = ui->getTextRenderer();
    tr->setScreenSize(ge->getSize());
    tr->setColor(WHITE);
    tr->draw(title, pos.x + (width / 2) - (tr->textWidth(title) / 2), ge->getSize().y - pos.y - 5 - 14 + 1);
    ge->uiShader.use();

    std::string s = text->getText();
    if (s == "")
    {
        s = "1";
    }

    double speed = std::stod(s);
    if (speed > 10)
    {
        text->setText("10");
        speed = 10;
    }

    ge->getPhysics()->setSimulationSpeed(speed);
}
