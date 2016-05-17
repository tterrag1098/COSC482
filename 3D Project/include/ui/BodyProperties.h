#ifndef BODYPROPERTIES_H
#define BODYPROPERTIES_H

#include "GuiBase.h"
#include "TypePicker.h"
#include "SphericalCamera.h"

class BodyInfo;
class TextBox;
class GhostPlanet;

/**
\class BodyProperties

\brief UI element containing all the options for editing and creating bodies.
*/

class BodyProperties : public GuiBase
{
    friend class GhostPlanet;

    public:
        BodyProperties(UI *ui, BodyInfo *info, glm::vec2 pos);
        virtual ~BodyProperties();

        void draw(GraphicsEngine *ge) override;

        void onBodyRemoved(BodyDrawable *b); ///< Callback from BodyInfo to be notified when a body is removed.

    protected:
    private:
        SphericalCamera cam;

        BodyInfo *info;

        TextBox *tName;
        TypePicker<BodyType> *tPickerBody;
        TextBox *tMass, *tRadius;

        TypePicker<BodyDrawable> *tPickerCenter;
        TextBox *tOrbitRadius, *tOrbitLat, *tOrbitLong;
        TextBox *tVelX, *tVelY, *tVelZ;

        TextButton *apply, *create;

        BodyDrawable *prevSel;

        static constexpr int hshort     = 180;
        static constexpr int htall      = 400;
        static constexpr int linesize   = fontsize + 16;
};

#endif // BODYPROPERTIES_H
