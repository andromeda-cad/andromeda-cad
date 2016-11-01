#ifndef PCB_LAYERS_H
#define PCB_LAYERS_H

#include <stdint.h>
#include <QString>

// PCB layer enumeration
enum class PCB_LAYER_ID : int8_t {
    // Layers that sit behind the copper layer
    BOARD_OUTLINE       =  1,    //!< Outline layer defines the shape of the PCB
    BOARD_MARGINS       =  2,    //!< Defines global margins

    // Back Layers
    BACK_FABRICATION    =  8,
    BACK_MECHANICAL     =  9,
    BACK_COURTYARD      = 10,
    BACK_SILKSCREEN     = 11,
    BACK_ADHESIVE       = 12,
    BACK_PASTE          = 13,
    BACK_MASK           = 14,
    BACK_COPPER         = 15,

    // Internal copper layers
    INTERNAL_COPPER_1	= 16,
    INTERNAL_COPPER_2,
    INTERNAL_COPPER_3,
    INTERNAL_COPPER_4,
    INTERNAL_COPPER_5,
    INTERNAL_COPPER_6,
    INTERNAL_COPPER_7,
    INTERNAL_COPPER_8,
    INTERNAL_COPPER_9,
    INTERNAL_COPPER_10,
    INTERNAL_COPPER_11,
    INTERNAL_COPPER_12,
    INTERNAL_COPPER_13,
    INTERNAL_COPPER_14,
    INTERNAL_COPPER_15,
    INTERNAL_COPPER_16,
    INTERNAL_COPPER_17,
    INTERNAL_COPPER_18,
    INTERNAL_COPPER_19,
    INTERNAL_COPPER_20,
    INTERNAL_COPPER_21,
    INTERNAL_COPPER_22,
    INTERNAL_COPPER_23,
    INTERNAL_COPPER_24,
    INTERNAL_COPPER_25,
    INTERNAL_COPPER_26,
    INTERNAL_COPPER_27,
    INTERNAL_COPPER_28,
    INTERNAL_COPPER_29,
    INTERNAL_COPPER_30,
    INTERNAL_COPPER_31,
    INTERNAL_COPPER_32,

    // Front Layers
    FRONT_COPPER        = 48,
    FRONT_MASK          = 49,
    FRONT_PASTE         = 50,
    FRONT_SILKSCREEN    = 51,
    FRONT_ADHESIVE      = 52,
    FRONT_COURTYARD     = 53,
    FRONT_MECHANICAL    = 54,
    FRONT_FABRICATION   = 55,  //!< Component outline and placement markers

    DRAWINGS            = 56,  //!< Reserved for user drawings
    COMMENTS            = 57,  //!< Reserved for user comments

    USER_A              = 58,
    USER_B              = 59,
    USER_C              = 60,

    // Do not extend layer IDs beyond 63!
    // A 64-bit mask is used to determine which layes are visible in a scene
};

/* Layer Masks */
const uint64_t PCB_LAYER_MASK_BACK   = ((uint64_t) 0xFF) << (int) PCB_LAYER_ID::BACK_FABRICATION;
const uint64_t PCB_LAYER_MASK_FRONT  = ((uint64_t) 0xFF) << (int) PCB_LAYER_ID::FRONT_COPPER;
const uint64_t PCB_LAYER_MASK_INTERNAL_COPPER = (uint64_t) 0xFFFFFFFF << (int) PCB_LAYER_ID::INTERNAL_COPPER_1;
const uint64_t PCB_LAYER_MASK_ALL_COPPER = ((uint64_t) PCB_LAYER_MASK_INTERNAL_COPPER) | ((uint64_t) 1 << (int) PCB_LAYER_ID::BACK_COPPER) | ((uint64_t) 1 << (int) PCB_LAYER_ID::FRONT_COPPER);

/* Layer Names */
const QString PCB_LAYER_OUTLINE     = "Outline";
const QString PCB_LAYER_MARGINS     = "Margins";
const QString PCB_LAYER_DRAWINGS    = "Drawings";
const QString PCB_LAYER_COMMENTS    = "Comments";
const QString PCB_LAYER_USER_A      = "User A";
const QString PCB_LAYER_USER_B      = "User B";
const QString PCB_LAYER_USER_C      = "User C";

const QString PCB_LAYER_FABRICATION = "Fabrication";
const QString PCB_LAYER_MECHANICAL  = "Mechanical";
const QString PCB_LAYER_COURTYARD   = "Courtyard";
const QString PCB_LAYER_SILKSCREEN  = "Silkscreen";
const QString PCB_LAYER_ADHESIVE    = "Adhesive";
const QString PCB_LAYER_PASTE       = "Paste";
const QString PCB_LAYER_MASK        = "Mask";
const QString PCB_LAYER_COPPER      = "Copper";

const QString PCB_LAYER_INTERNAL    = "Internal Copper";

// Back Layer Names
const QString PCB_PREFIX_BACK = "Back.";
const QString PCB_LAYER_BACK_FABRICATION   = PCB_PREFIX_BACK + PCB_LAYER_FABRICATION;
const QString PCB_LAYER_BACK_MECHANICAL    = PCB_PREFIX_BACK + PCB_LAYER_MECHANICAL;
const QString PCB_LAYER_BACK_COURTYARD     = PCB_PREFIX_BACK + PCB_LAYER_COURTYARD;
const QString PCB_LAYER_BACK_SILKSCREEN    = PCB_PREFIX_BACK + PCB_LAYER_SILKSCREEN;
const QString PCB_LAYER_BACK_ADHESIVE      = PCB_PREFIX_BACK + PCB_LAYER_ADHESIVE;
const QString PCB_LAYER_BACK_PASTE         = PCB_PREFIX_BACK + PCB_LAYER_PASTE;
const QString PCB_LAYER_BACK_MASK          = PCB_PREFIX_BACK + PCB_LAYER_MASK;
const QString PCB_LAYER_BACK_COPPER        = PCB_PREFIX_BACK + PCB_LAYER_COPPER;

// Front Layer Names
const QString PCB_PREFIX_FRONT = "Front.";
const QString PCB_LAYER_FRONT_FABRICATION   = PCB_PREFIX_FRONT + PCB_LAYER_FABRICATION;
const QString PCB_LAYER_FRONT_MECHANICAL    = PCB_PREFIX_FRONT + PCB_LAYER_MECHANICAL;
const QString PCB_LAYER_FRONT_COURTYARD     = PCB_PREFIX_FRONT + PCB_LAYER_COURTYARD;
const QString PCB_LAYER_FRONT_SILKSCREEN    = PCB_PREFIX_FRONT + PCB_LAYER_SILKSCREEN;
const QString PCB_LAYER_FRONT_ADHESIVE      = PCB_PREFIX_FRONT + PCB_LAYER_ADHESIVE;
const QString PCB_LAYER_FRONT_PASTE         = PCB_PREFIX_FRONT + PCB_LAYER_PASTE;
const QString PCB_LAYER_FRONT_MASK          = PCB_PREFIX_FRONT + PCB_LAYER_MASK;
const QString PCB_LAYER_FRONT_COPPER        = PCB_PREFIX_FRONT + PCB_LAYER_COPPER;

QString PCBLayerName(int8_t layerId);

#endif // PCB_LAYERS_H

