#include "pcb_layers.h"

QString PCBLayerName(int8_t layerId)
{
    // Internal layers
    if ((layerId >= (int) PCB_LAYER_ID::INTERNAL_COPPER_1) &&
        (layerId <= (int) PCB_LAYER_ID::INTERNAL_COPPER_32))
    {
        return PCB_LAYER_INTERNAL + "_" + QString::number(layerId - (int) PCB_LAYER_ID::INTERNAL_COPPER_1 + 1);
    }

    // Other layers
    switch (layerId)
    {
    /*
    case PCB_LAYER_ID::BOARD_OUTLINE:
        return PCB_LAYER_OUTLINE;
    */
        //TODO - The rest of the cases
    }

    return "Unknown";
}
