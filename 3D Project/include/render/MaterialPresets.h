#ifndef MATERIALPRESETS_H_INCLUDED
#define MATERIALPRESETS_H_INCLUDED

#include "Material.h"

/**
\file MaterialPresets.h
\brief Basic material properties for standard types of surfaces.

\author    Don Spickler
\version   1.1
\date      Written: 2/28/2016  <BR> Revised: 2/28/2016

*/

/**
\namespace Materials

\brief The Materials namespace is simply a collection of statically
defined material attributes.

- Material::redPlastic --- Red Plastic
- Material::greenPlastic --- Green Plastic
- Material::bluePlastic --- Blue Plastic
- Material::brass --- Brass
- Material::bronze --- Bronze
- Material::polishedBronze --- Polished Bronze
- Material::chrome --- Chrome
- Material::copper --- Copper
- Material::polishedCopper --- Polished Copper
- Material::gold --- Gold
- Material::polishedGold --- Polished Gold
- Material::pewter --- Pewter
- Material::silver --- Silver
- Material::polishedSilver --- Polished Silver
- Material::emerald --- Emerald
- Material::jade --- Jade
- Material::obsidian --- Obsidian
- Material::pearl --- Pearl
- Material::ruby --- Ruby
- Material::turquoise --- Turquoise

*/

namespace Materials
{

static Material white(
    0.3, 0.3, 0.3, 1.0,
    0.0, 0.0, 0.0, 1.0,
    32.0
);

static Material fullbright(
    0.0, 0.0, 0.0, 1.0,
    1.0, 1.0, 1.0, 1.0,
    32.0
);

}


#endif // MATERIALPRESETS_H_INCLUDED
