#ifndef BODYINFO_H
#define BODYINFO_H

#include "GuiBase.h"

class GraphicsEngine;
class TextButton;

class BodyInfo : public GuiBase
{
    public:
        BodyInfo(UI *ui, glm::vec2 pos);
        virtual ~BodyInfo();

        void draw(GraphicsEngine *ge) override;

    protected:
    private:
        TextButton *delBut;

        static constexpr int lines = 3;
        static constexpr int linespace = 3;
        static constexpr int h = padding*2 + (fontsize+linespace)*lines + linespace;
};

#endif // BODYINFO_H
