#ifndef BODYINFO_H
#define BODYINFO_H

#include "GuiBase.h"
#include "TypePicker.h"

class GraphicsEngine;
class TextButton;
class BodyProperties;

/**
\class BodyInfo

\brief The UI element containing basic information about the selected body. Also allows deletion of said object.
*/

class BodyInfo : public GuiBase
{
    public:
        BodyInfo(UI *ui, glm::vec2 pos, std::vector<BodyDrawable*> bodylist);
        virtual ~BodyInfo();

        void draw(GraphicsEngine *ge) override;

        void setProps(BodyProperties *props); ///< Use for hacky callback to properties to update removed objects.
        void onBodyAdded(BodyDrawable *b); ///< Called from BodyProperties to notify of an added body.

    protected:
    private:
        BodyProperties *props;

        TypePicker<BodyDrawable> *bodyPicker;
        TextButton *delBut;

        static constexpr int lines = 3;
        static constexpr int linespace = 3;
        static constexpr int h = 28 + padding*2 + (fontsize+linespace)*lines + linespace;
};

#endif // BODYINFO_H
