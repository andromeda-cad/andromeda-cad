#ifndef LAYER_DEFINES_H
#define LAYER_DEFINES_H

#include "pcb_layers.h"

#include <stdint.h>

// Layer display modes
enum class LAYER_MODE : int {

    // Show *no* layers
    SHOW_NONE = 0x00,

    // Show the selected layer - all other layers are greyed out
    HIGHLIGHT,

    // Show the selected layer - all other layers are invisible
    HIDDEN,

    // Display *all* layers
    SHOW_ALL = 0xFF,
};

// Layer mask enumerations
enum class LAYER_MASK : uint64_t {

    // Mask for no layers
    NONE = 0x00,

    // Maks for all layers
    ALL = UINT64_MAX
};

// Generic layer enumerations
enum class LAYER_ID : int {


    // Layers 0-63 are available for use
    // Each of these layers can be masked ON or OFF
    // All other layers are always 'ON'
    BOTTOM = 0,
    TOP = 63,

    // The currently selected layer is forced to the top
    SELECTED = 70,

    // User-facing tools draw temporary objects on the TOOLS layer
    TOOLS = 80,

    // Cursor is drawn on top
    CURSOR = 90,

    // Special value to force item to be insisible
    INVISIBLE = 100,

    // Special value corresponding to "no layer"
    NONE = 110,
};

uint64_t LayerIdToMask(int layerId);

#endif // LAYER_DEFINES_H

