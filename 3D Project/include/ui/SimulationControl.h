#ifndef SIMULATIONCONTROL_H
#define SIMULATIONCONTROL_H

#include "GuiBase.h"

class TextButton;
class TextBox;
class GraphicsEngine;
class Button;
class TexturedBox;

/**
\class SimulationControl

\brief UI element which contains the controls for the simulation speed and play/pause/
*/

class SimulationControl : public GuiBase
{
    public:
        SimulationControl(UI *ui, glm::vec2 pos);
        virtual ~SimulationControl();

        void draw(GraphicsEngine *ge) override;

    protected:
    private:
        UI *ui;
        TextButton *m1, *m01, *p01, *p1;
        Button *pause;
        TextBox *text;

        TexturedBox *playIcon, *pauseIcon;

        void addSpeed(double amt);

        static constexpr int h = 95;
        static constexpr int spacing = 8;
};

#endif // SIMULATIONCONTROL_H
